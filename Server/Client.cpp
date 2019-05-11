#include <iostream>
#include "Client.h"
#include "Server.h"

extern Server server;

Client::Client(CommunicationStack* communicationStack)
: communicationStack(communicationStack), clientThread(&Client::clientThreadTask, this){
    clientThread.detach();
}

Client::~Client() {
    delete communicationStack;
}

std::string Client::getUsername(){
    return username;
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

            if(e["type"] == "LOGIN_REQUEST"){
                handleLoginRequest(LoginRequest(e));
            }
            else{
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
    if(request.username == "admin" && request.password == "admin"){
        std::cout << "admin has logged in" << std::endl;

        username = request.username;
        communicationStack->sendEvent(LoginResponse(true, "<session_token>"));
    }
    else{
        communicationStack->sendEvent(LoginResponse(false, ""));
    }
}
