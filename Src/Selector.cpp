#include <sys/select.h>
#include <iostream>
#include "Selector.h"
#include "Socket.h"

int Selector::find(const Socket& socket){
    int pos = -1;
    auto fd = socket.socketDescriptor;
    for(int i = 0; i < socketDescriptors.size(); i++){
        if(socketDescriptors[i] == fd){
            pos = i;
        }
    }
    return pos;
}

bool Selector::isPresent(const Socket& socket){
    return find(socket) != -1;
}

Selector::Selector() {
    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&signal);
}

void Selector::add(const Socket& socket){
    if(!isPresent(socket)){
        auto fd = socket.socketDescriptor;
        socketDescriptors.push_back(fd);
    }
}

void Selector::remove(const Socket& socket){
    int pos = find(socket);
    if(pos != -1){
        socketDescriptors.erase(socketDescriptors.begin() + pos);
    }
}

void Selector::clear(){
    socketDescriptors.clear();
}

int Selector::wait(){
    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&signal);
    int max = -1;
    for(auto fd: socketDescriptors){
        if(fd > max){
            max = fd;
        }
        FD_SET(fd, &read);
        FD_SET(fd, &write);
        FD_SET(fd, &signal);
    }
    int howManyActive = select(max + 1, &read, &write, &signal, 0); // 0 = no timeout
    if(howManyActive == -1){
        throw "Selector::wait() error";
    }
    return howManyActive;
}

bool Selector::isReadReady(const Socket& socket){
    auto fd = socket.socketDescriptor;
    return FD_ISSET(fd, &read);
}

bool Selector::isWriteReady(const Socket& socket){
    auto fd = socket.socketDescriptor;
    return FD_ISSET(fd, &write);
}

bool Selector::isSignalReady(const Socket& socket){
    auto fd = socket.socketDescriptor;
    return FD_ISSET(fd, &signal);
}