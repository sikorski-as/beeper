#include <mutex>
#include "ClientMonitor.h"
#include "../src/TCPSocket.h"

// callers of this need to lock clientListAccess first
int ClientMonitor::findClientBy(TCPSocket &socket) {
    for(int i = 0; i < clients.size(); i++){
        if(clients[i]->getSocket() == socket){
            return i;
        }
    }
    throw ClientNotFound();
}

// callers of this need to lock clientListAccess first
int ClientMonitor::findClientBy(const std::string& username) {
    for(int i = 0; i < clients.size(); i++){
        if(clients[i]->getUsername() == username){
            return i;
        }
    }
    throw ClientNotFound();
}

// callers of this need to lock clientListAccess first
bool ClientMonitor::clientExists(TCPSocket &socket) {
    try{
        findClientBy(socket);
    }
    catch (ClientNotFound&){
        return false;
    }
    return true;
}

// callers of this need to lock clientListAccess first
bool ClientMonitor::clientExists(const std::string& username) {
    try{
        findClientBy(username);
    }
    catch (ClientNotFound&){
        return false;
    }
    return true;
}

void ClientMonitor::insertClient(TCPSocket &socket) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    clients.push_back(new Client(socket));
}

void ClientMonitor::removeClient(TCPSocket &socket) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    int clientIndex = findClientBy(socket);
    clients.erase(clients.begin() + clientIndex);
}

void ClientMonitor::removeClient(const std::string& username) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    int clientIndex = findClientBy(username);
    clients.erase(clients.begin() + clientIndex);
}

void ClientMonitor::removeAllClients() {
    std::lock_guard<std::mutex> lock(clientListAccess);
    for(int i = 0; i < clients.size(); i++){
        if(clients[i] != nullptr){
            delete clients[i];
        }
    }
    clients.clear();
}

void ClientMonitor::insertIntoUsersIncomingQueue(TCPSocket& socket, Event e) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    int clientIndex = findClientBy(socket);
    clients[clientIndex]->insertIntoQueue(e);
}

void ClientMonitor::insertIntoUsersIncomingQueue(const std::string& username, Event e) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    int clientIndex = findClientBy(username);
    clients[clientIndex]->insertIntoQueue(e);
    clients[clientIndex]->notify();
}

//void ClientMonitor::notify(const std::string& username) {
//    std::lock_guard<std::mutex> lock(clientListAccess);
//    int clientIndex = findClientBy(username);
//    clients[clientIndex]->notify();
//}

void ClientMonitor::notifyRead(TCPSocket &) {
    // todo
}


void ClientMonitor::notifyWrite(TCPSocket &) {
    // todo
}
