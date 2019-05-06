#include <sys/select.h>
#include <sys/time.h>
#include <iostream>

#include "Selector.h"
#include "TCPSocket.h"
#include "TCPListener.h"
#include "Socket.h"

//
// protected
//

int Selector::find(const TCPSocket& socket){
    int pos = -1;
    for(int i = 0; i < sockets.size(); i++){
        if(sockets[i] == socket){
            pos = i;
        }
    }
    return pos;
}

bool Selector::isPresent(const TCPSocket& socket){
    return find(socket) != -1;
}

std::vector<int> Selector::getSocketDescriptors() {
    std::vector<int> descriptors;

    for(auto& socket: sockets){
        descriptors.push_back(socket.getDescriptor());
    }

    return descriptors;
}

//
// public
//

Selector::Selector(const TCPListener& listener) {
    this->listener = listener;
    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&signal);
}

void Selector::setListener(const TCPListener& newListener){
    std::lock_guard<std::mutex> lock(access);
    listener = newListener;
}

bool Selector::isListenerReady(){
    return FD_ISSET(listener.getDescriptor(), &read)
    || FD_ISSET(listener.getDescriptor(), &write)
    || FD_ISSET(listener.getDescriptor(), &signal);
}

void Selector::add(const TCPSocket& socket){
    std::lock_guard<std::mutex> lock(access);
    if(!isPresent(socket)){
        sockets.push_back(socket);
    }
    std::cout << "sockets in selector: " << sockets.size() << std::endl;
}

void Selector::remove(const TCPSocket& socket){
    std::lock_guard<std::mutex> lock(access);
    int pos = find(socket);
    if(pos != -1){
        sockets.erase(sockets.begin() + pos);
    }
}

void Selector::clear(){
    std::lock_guard<std::mutex> lock(access);
    sockets.clear();
}

int Selector::wait(int timeoutInSeconds){
    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&signal);

    int max = -1;

    std::vector<int> socketDescriptors;
    {
        std::lock_guard<std::mutex> lock(access);
        socketDescriptors = getSocketDescriptors();
    }
    socketDescriptors.push_back(listener.getDescriptor());

    for(auto fd: socketDescriptors){
        if(fd > max){
            max = fd;
        }

        FD_SET(fd, &read);
        FD_SET(fd, &write);
        FD_SET(fd, &signal);
    }

    timeval* timeout = nullptr;
    if(timeoutInSeconds > 0){
        timeout = new timeval;
        timeout->tv_sec = timeoutInSeconds;
        timeout->tv_usec = 0;
    }
    int howManyActive = select(max + 1, &read, &write, &signal, timeout); // timeout <= 0 means waiting forever
    if(timeout != nullptr)
        delete timeout;

    if(howManyActive == -1){
        throw "Selector::wait() error";
    }
    return howManyActive;
}

std::vector<TCPSocket> Selector::getReadReadySockets(){
    std::vector<TCPSocket> readReadySockets;
    for(const TCPSocket& socket: sockets){
        if(FD_ISSET(socket.getDescriptor(), &read)){
            readReadySockets.push_back(socket);
        }
    }
    return  readReadySockets;
}

std::vector<TCPSocket> Selector::getWriteReadySockets(){
    std::vector<TCPSocket> writeReadySockets;
    for(const TCPSocket& socket: sockets){
        if(FD_ISSET(socket.getDescriptor(), &write)){
            writeReadySockets.push_back(socket);
        }
    }
    return  writeReadySockets;
}
