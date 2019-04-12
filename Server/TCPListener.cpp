//
// Created by hubertborkowski on 12.04.19.
//

#include "TCPListener.h"

TCPListener::TCPListener(Address address, int backlogLength): Socket(address)
{
    this->listening = false;
    this->backlogLength = backlogLength;
}

void TCPListener::start()
{
    if(!listening)
    {
        if(::bind(socketDescriptor, (sockaddr*)&address, sizeof(address)) < 0)
        {
            //TODO throw exception
        }

        if(::listen(socketDescriptor, backlogLength) < 0)
        {
            //TODO throw exception
        }

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
