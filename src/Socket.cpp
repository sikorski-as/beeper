//
// Created by hubertborkowski on 12.04.19.
//

#include "Socket.h"

Socket::Socket(Address address)
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor == 0)
    {
        //TODO throw exception
    }
    this->address = address;
}

Socket::Socket(int newSocketDescriptor, Address address)
{
    this->socketDescriptor = newSocketDescriptor;
    this->address = address;
}

void Socket::close()
{
    if(::close(socketDescriptor) < 0)
    {
        //TODO throw exception
    }
}
