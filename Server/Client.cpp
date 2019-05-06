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
                if(e["username"] == "admin") {
                    username = "admin";
                    std::cout << "admin has logged in" << std::endl;
                }
            }
            else if(e["type"] == "SHUTDOWN"){
                server.stop();
            }
            else{
                std::cout << "unknown request" << std::endl;
                communicationStack->sendEvent(UnknownRequest());
            }
        }
        catch (...){
            std::cout << "request error" << std::endl; // todo: handle errors
        }

    }
    server.clientMonitor.removeClient(this);
}
