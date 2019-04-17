#include <sys/select.h>
#include <sys/time.h>
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

Selector::Selector(bool readSelector, bool writeSelector, bool signalSelector) {
    this->readSelector = readSelector;
    this->writeSelector = writeSelector;
    this->signalSelector = signalSelector;
    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&signal);
}

void Selector::setupSelector(bool readSelector, bool writeSelector, bool signalSelector){
    this->readSelector = readSelector;
    this->writeSelector = writeSelector;
    this->signalSelector = signalSelector;
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

int Selector::wait(int timeoutInSeconds){
    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&signal);
    int max = -1;
    for(auto fd: socketDescriptors){
        if(fd > max){
            max = fd;
        }
        if(readSelector)
            FD_SET(fd, &read);
        if(writeSelector)
            FD_SET(fd, &write);
        if(signalSelector)
            FD_SET(fd, &signal);
    }

    timeval* timeout = nullptr;
    if(timeoutInSeconds > 0){
        timeout = new timeval;
        timeout->tv_sec = timeoutInSeconds;
        timeout->tv_usec = 0;
    }
    int howManyActive = select(max + 1, &read, &write, &signal, timeout); // 0 = no timeout
    if(timeout != nullptr)
        delete timeout;

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