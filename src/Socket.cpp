//
// Created by hubertborkowski on 11.04.19.
//

#include "Socket.h"

Socket::Socket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor == 0)
    {
        //TODO throw exception
    }
}

Socket::Socket(int socketDescriptor, Address address)
{
    this->socketDescriptor = socketDescriptor;
    this->address = address;
}

void Socket::bind()
{
    if(::bind(socketDescriptor, (struct sockaddr*)&address, sizeof(address)) != 0)
    {
        //TODO throw exception
    }
}

void Socket::listen(int backlogLength)
{
    if(::listen(socketDescriptor, backlogLength) != 0)
    {
        //TODO throw exception
    }
}

ISocket *Socket::accept()
{
    socklen_t addrlen = sizeof(address);
    int newSocketDescriptor = ::accept(socketDescriptor, (struct sockaddr*)&address, &addrlen);

    if(newSocketDescriptor == 0)
    {
        //TODO throw exception
    }

    ISocket* result = new Socket(newSocketDescriptor, address);

    return result;
}

void Socket::connect()
{
    if(::connect(socketDescriptor, (struct sockaddr*)&address, sizeof(address)) != 0)
    {
        //TODO throw exception
    }
}

void Socket::send(char *buffer)
{
    if(::send(socketDescriptor, buffer, strlen(buffer), 0) < 0)
    {
        //TODO throw exception
    }
}

std::size_t Socket::receive(char *buffer, std::size_t)
{
    ssize_t bufferSize = recv(socketDescriptor, buffer, strlen(buffer), 0);

    if(bufferSize < 0)
    {
        //TODO throw exception
    }
    else
    {
        return static_cast<std::size_t >(bufferSize);
    }
}

void Socket::close()
{
    if(::close(socketDescriptor) < 0)
    {
        //TODO throw exception
    }
}
