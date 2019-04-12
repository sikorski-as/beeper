//
// Created by hubertborkowski on 12.04.19.
//

#include "ServerSocket.h"

ServerSocket::ServerSocket(Address address): Socket(address)
{
    this->listening = false;
}

Socket *ServerSocket::accept()
{
    socklen_t addrlen;
    int newSocketDescriptor = ::accept(socketDescriptor, (sockaddr*)&address, &addrlen);

    if(newSocketDescriptor < 0)
    {
        //TODO throw exception
    }
    else
    {
        return new Socket(newSocketDescriptor, address);
    }
}

void ServerSocket::bind()
{
    if(::bind(socketDescriptor, (sockaddr*)&address, sizeof(address)) < 0)
    {
        //TODO throw exception
    }
}

void ServerSocket::listen(int backlogLength)
{
    if(::listen(socketDescriptor, backlogLength) < 0)
    {
        //TODO throw exception
    }
}
