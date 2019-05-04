#include "Client.h"

Client::Client(TCPSocket&){

}

TCPSocket Client::getSocket(){
    return TCPSocket{};
}

std::string Client::getUsername(){
    return "";
}

void Client::insertIntoQueue(Event){
    return;
}

void Client::notify(){

}
