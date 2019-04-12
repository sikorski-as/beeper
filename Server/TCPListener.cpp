//
// Created by hubertborkowski on 12.04.19.
//

#include "TCPListener.h"

TCPListener::TCPListener(Address address): Socket(address)
{
    this->listening = false;
}

void TCPListener::start()
{
    if(!listening)
    {
        listening = true;

    }
    else
    {
        //TODO throw exception
    }
}

TCPSocket *TCPListener::accept()
{
    socklen_t addrlen;
    int newSocketDescriptor = ::accept(socketDescriptor, (sockaddr*)&address, &addrlen);

    if(newSocketDescriptor < 0)
    {
        //TODO throw exception
    }
    else
    {
        return new TCPSocket(newSocketDescriptor, address);
    }
}

void TCPListener::bind()
{
    if(::bind(socketDescriptor, (sockaddr*)&address, sizeof(address)) < 0)
    {
        //TODO throw exception
    }
}

void TCPListener::listen(int backlogLength)
{
    if(::listen(socketDescriptor, backlogLength) < 0)
    {
        //TODO throw exception
    }
}
