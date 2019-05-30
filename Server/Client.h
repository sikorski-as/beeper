#ifndef BEEPER_CLIENT_H
#define BEEPER_CLIENT_H

#include <string>
#include <thread>
#include "../src/IONotifiable.h"
#include "../src/TCPSocket.h"
#include "../src/CommunicationStack.h"
#include "../src/Event.h"
#include "../database-objects/User.h"
#include "../src/Database.h"

class Client : public IONotifiable{
    User* user;
    CommunicationStack * communicationStack;

    std::thread clientThread;
    void clientThreadTask();
public:
    Client(CommunicationStack*);
    ~Client();

    std::string getUsername();
    void notifyRead() override;
    void notifyWrite() override;

    void handleLoginRequest(LoginRequest);
  	void handleLogoutRequest(LogoutRequest);
  	void handleRegisterRequest(RegisterRequest);
  	void handleAddPostRequest(AddPostRequest);
  	void handleLikePostRequest(LikePostRequest);
  	void handleGetNNewPostsRequest(GetNNewPostsRequest);
  	void handleGetAllUsersRequest(GetAllUsersRequest);
  	void handleViewUserRequest(ViewUserRequest);
  	void handleGetUserPostsRequest(GetUserPostsRequest);
  	void handleDeleteUserRequest(DeleteUserRequest);
  	void handleDeletePostRequest(DeletePostRequest);
};


#endif //BEEPER_CLIENT_H
