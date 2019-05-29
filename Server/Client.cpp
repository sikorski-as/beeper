#include <iostream>
#include "Client.h"
#include "Server.h"

typedef void(Client::*event_handling_function)(Event);

static std::map<std::string, event_handling_function> serviceFunctionsMap = {
		{"LOGIN_REQUEST", &Client::handleLoginRequest},
		{"LOGOUT_REQUEST", &Client::handleLogoutREquest}
};

extern Server server;

Client::Client(CommunicationStack* communicationStack)
: communicationStack(communicationStack), clientThread(&Client::clientThreadTask, this){
    clientThread.detach();
}

Client::~Client() {
    delete communicationStack;
}

std::string Client::getUsername(){
    return user.getUsername();
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

			serviceFunctionsMap[e["type"]](e);

            if()//todo: handle unknown request
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
	User temp = server.database.getUserByUsername(request.username);

    if(temp.getPassword() == request.password){

        user = temp;

        communicationStack->sendEvent(LoginResponse(true, "<session_token>"));
    }
    else{
        communicationStack->sendEvent(LoginResponse(false, ""));
    }
}

void Client::handleLogoutREquest(LogoutRequest request)
{
	if(user.getUsername() == request.username)
	{
		communicationStack->sendEvent(LogoutResponse(true));
		server.clientMonitor.removeClient(this);
	}
	else
	{
		communicationStack->sendEvent(LogoutResponse(false));
	}
}
