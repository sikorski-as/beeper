#include <iostream>
#include "Client.h"
#include "Server.h"

typedef void(Client::*event_handling_function)(Event);

//static std::map<std::string, event_handling_function> serviceFunctionsMap;
//
//static void initFunctionsMap()
//{
//	serviceFunctionsMap["LOGIN_REQUEST"] = &Client::handleLoginRequest;
//	serviceFunctionsMap["LOGOUT_REQUEST"] = &Client::handleLogoutREquest;
//}

extern Server server;

Client::Client(CommunicationStack* communicationStack)
: communicationStack(communicationStack), clientThread(&Client::clientThreadTask, this){
    clientThread.detach();
	//initFunctionsMap();
}

Client::~Client() {
    delete communicationStack;
}

std::string Client::getUsername(){
    return user->getUsername();
}

void Client::notifyRead() {
    communicationStack->notifyRead();
}

void Client::notifyWrite() {
    communicationStack->notifyWrite();
}

void Client::clientThreadTask() {
    while(server.isRunning()){
        //communicationStack->sendEvent(WelcomeMessage());
        //continue;

        try{
            auto e = communicationStack->getEvent();

			//serviceFunctionsMap[e["type"]](e);
			if(e["type"] == "LOGIN_REQUEST")
			{
				handleLoginRequest(LoginRequest(e));
			}
			else if(e["type"] == "LOGOUT_REQUEST")
			{
				handleLogoutRequest(LogoutRequest(e));
			}
			else if(e["type"] == "REGISTER_REQUEST")
			{
				handleRegisterRequest(RegisterRequest(e));
			}
			else if(e["type"] == "ADD_POST_REQUEST")
			{
				handleAddPostRequest(AddPostRequest(e));
			}
			else if(e["type"] == "LIKE_POST_REQUEST")
			{
				handleLikePostRequest(LikePostRequest(e));
			}
			else if(e["type"] == "GET_N_NEW_POSTS_REQUEST")
			{
				handleGetNNewPostsRequest(GetNNewPostsRequest(e));
			}
			else if(e["type"] == "GET_ALL_USERS_REQUEST")
			{
				handleGetAllUsersRequest(GetAllUsersRequest(e));
			}
			else
			{
                std::cout << "got unknown request:" << std::endl;
                std::cout << "\t" << e.dump() << std::endl;
                communicationStack->sendEvent(UnknownRequest());
            }
        }
        catch (EventNotValid e){
            std::cout << "request not valid" << std::endl;
            communicationStack->sendEvent(MalformedRequest(e.reason));
        }
        catch (...){
            std::cout << "unforeseen service error" << std::endl;
        }

    }
    server.clientMonitor.removeClient(this);
}

void Client::handleLoginRequest(LoginRequest request) {
	User temp;

	if(user != nullptr)
	{
		communicationStack->sendEvent(LoginResponse(false, ""));
		return;
	}

	try
	{
		temp = server.database.getUserByUsername(request.username);
	}
	catch(DatabaseException& exception)
	{
		std::cout << exception.what() << std::endl;
		communicationStack->sendEvent(LoginResponse(false, ""));
		return;
	}

    if(temp.getPassword() == request.password){

        user = &temp;

        communicationStack->sendEvent(LoginResponse(true, "<session_token>"));
    }
    else{
        communicationStack->sendEvent(LoginResponse(false, ""));
    }
}

void Client::handleLogoutRequest(LogoutRequest request)
{
	if(user == nullptr)
	{
		communicationStack->sendEvent(LogoutResponse(false));
		return;
	}

	if(user->getUsername() == request.username)
	{
		delete user;
		user = nullptr;
		communicationStack->sendEvent(LogoutResponse(true));
	}
	else
	{
		communicationStack->sendEvent(LogoutResponse(false));
	}
}

void Client::handleRegisterRequest(RegisterRequest request)
{
	if(Database::containsForbiddenChars(request.username) ||
			Database::containsForbiddenChars(request.password) ||
			Database::containsForbiddenChars(request.alias) ||
			Database::containsForbiddenChars(request.bio))
	{
		communicationStack->sendEvent(RegisterResponse(false));
	}
	else
	{
		server.database.addUser(request.username, request.alias, request.bio, request.password);
		communicationStack->sendEvent(RegisterResponse(true));
	}
}

void Client::handleAddPostRequest(AddPostRequest request)
{
	if(user == nullptr)
	{
		communicationStack->sendEvent(AddPostResponse(false));
		return;
	}

	if(Database::containsForbiddenChars(request.content))
	{
		communicationStack->sendEvent(AddPostResponse(false));
	}
	else
	{
		server.database.addPost(user->getId(), request.content);
		communicationStack->sendEvent(AddPostResponse(true));
	}
}

void Client::handleLikePostRequest(LikePostRequest request)
{
	if(user == nullptr)
	{
		communicationStack->sendEvent(LikePostResponse(false));
		return;
	}

	try
	{
		server.database.getPostById(request.postId);
	}
	catch (DatabaseException& e)
	{
		std::cout << e.what() << std::endl;
		communicationStack->sendEvent(LikePostResponse(false));
		return;
	}

	server.database.likePost(user->getId(), request.postId);
	communicationStack->sendEvent(LikePostResponse(true));
}

void Client::handleGetNNewPostsRequest(GetNNewPostsRequest request)
{
	if(user == nullptr)
	{
		communicationStack->sendEvent(GetNNewPostsResponse(false, ""));
		return;
	}

	std::vector<Post> posts;

	try
	{
		posts = server.database.getNNewsestPosts(request.numberOfPosts);
	}
	catch (DatabaseException& e)
	{
		std::cout << e.what() << std::endl;
		communicationStack->sendEvent(GetNNewPostsResponse(false, ""));
		return;
	}

	json j_array;
	json j_post;

	for(auto post: posts)
	{
		j_post["id"] = std::to_string(post.getId());
		j_post["content"] = post.getContent();
		j_array.push_back(j_post);
	}

	communicationStack->sendEvent(GetNNewPostsResponse(true, j_array));
}

void Client::handleGetAllUsersRequest(GetAllUsersRequest request)
{
	if(user == nullptr)
	{
		communicationStack->sendEvent(GetAllUsersResponse(false, ""));
		return;
	}

	std::vector<User> users;

	try
	{
		users = server.database.getAllUsers();
	}
	catch (DatabaseException& e)
	{
		std::cout << e.what() << std::endl;
	}

	json j_user;
	json j_array;

	for(auto usr: users)
	{
		j_user["id"] = usr.getId();
		j_user["username"] = usr.getUsername();
		j_user["password"] = usr.getPassword();
		j_user["alias"] = usr.getAlias();
		j_user["bio"] = usr.getBio();
		j_array.push_back(j_user);
	}

	communicationStack->sendEvent(GetAllUsersResponse(true, j_array));
}

void Client::handleViewUserRequest(ViewUserRequest request)
{
	if(user == nullptr || Database::containsForbiddenChars(request.username))
	{
		communicationStack->sendEvent(ViewUserResponse(false,""));
		return;
	}

	User temp;

	try
	{
		temp = server.database.getUserByUsername(request.username);
	}
	catch (DatabaseException& e)
	{
		std::cout << e.what() << std::endl;
		communicationStack->sendEvent(ViewUserResponse(false,""));
	}

	json j_user;
	j_user["id"] = temp.getId();
	j_user["username"] = temp.getUsername();
	j_user["alias"] = temp.getAlias();
	j_user["bio"] = temp.getBio();

	communicationStack->sendEvent(ViewUserResponse(true, j_user));
}
