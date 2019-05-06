#include <mutex>
#include <iostream>
#include "ClientMonitor.h"
#include "../src/TCPSocket.h"

ClientMonitor::ClientMonitor(Selector & selector) : selector(selector){

}


// callers of this need to lock clientListAccess first
int ClientMonitor::findClientBy(const TCPSocket &socket) {
    auto socketId = socket.getDescriptor();
    auto client = socketToClientMap[socket];
    for(int i = 0; i < clients.size(); i++){
        if(clients[i] == client){
            return i; // we want index instead of client pointer to easily remove clients (erase)
        }
    }
    throw ClientNotFound();
}

// callers of this need to lock clientListAccess first
int ClientMonitor::findClientBy(const std::string& username) {
    for(int i = 0; i < clients.size(); i++){
        if(clients[i]->getUsername() == username){
            return i; // we want index instead of client pointer to easily remove clients (erase)
        }
    }
    throw ClientNotFound();
}

int ClientMonitor::findClientBy(Client* client) {
    for(int i = 0; i < clients.size(); i++){
        if(clients[i] == client){
            return i; // we want index instead of client pointer to easily remove clients (erase)
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

//
// public
//

void ClientMonitor::insertClient(const TCPSocket& socket, Client * client) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    if(socketToClientMap.find(socket) == socketToClientMap.end()){
        socketToClientMap[socket] = client;
    }

    clients.push_back(client);

    selector.add(socket);
}

void ClientMonitor::removeClient(Client* client) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    try{
        int clientIndex = findClientBy(client);
        clients.erase(clients.begin() + clientIndex);

        for(auto it = socketToClientMap.begin(); it != socketToClientMap.end(); ++it){
            if(it->second == client){
                selector.remove(it->first);
                socketToClientMap.erase(it);
                break;
            }
        }
    }
    catch(ClientMonitor::ClientNotFound& e){}
}

void ClientMonitor::removeClient(const TCPSocket& socket){
    std::lock_guard<std::mutex> lock(clientListAccess);
    try{
        int clientIndex = findClientBy(socket);
        clients.erase(clients.begin() + clientIndex);

        for(auto it = socketToClientMap.begin(); it != socketToClientMap.end(); ++it){
            if(it->first == socket){
                selector.remove(socket);
                socketToClientMap.erase(it);
                break;
            }
        }
    }
    catch(ClientMonitor::ClientNotFound& e){}
}

void ClientMonitor::removeAllClients() {
    std::lock_guard<std::mutex> lock(clientListAccess);
    for(int i = 0; i < clients.size(); i++){
        if(clients[i] != nullptr){
            delete clients[i];
        }
    }

    selector.clear();
    clients.clear();
    socketToClientMap.clear();
}

void ClientMonitor::notifyRead(TCPSocket & socket) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    socketToClientMap[socket]->notifyRead();
}


void ClientMonitor::notifyWrite(TCPSocket & socket) {
    std::lock_guard<std::mutex> lock(clientListAccess);
    socketToClientMap[socket]->notifyWrite();
}

void ClientMonitor::status() {
    std::lock_guard<std::mutex> lock(clientListAccess);
    std::cout << "client monitor status\n";
    std::cout << "\tentries in socketToClient map: " << socketToClientMap.size() << "\n";
    std::cout << "\tentries in clients vector: " << clients.size() << "\n";
}
