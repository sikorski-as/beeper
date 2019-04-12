//
// Created by hubertborkowski on 12.04.19.
//

#include "ServerSocket.h"

ServerSocket::ServerSocket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor == 0)
    {
        //TODO throw exception
    }
}

ServerSocket::ServerSocket(int socketDescriptor, Address address)
{
    this->socketDescriptor = socketDescriptor;
    this->address = address;
}

ssize_t ServerSocket::readn(std::size_t n, char* buffer)
{
    std::size_t nleft;
    ssize_t nread;
    //char* resultBuffer;

    nleft = n;

    while(nleft > 0)
    {
        if((nread = ::read(socketDescriptor, buffer, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;

        nleft -= nread;
        buffer += nread;
    }

    return n-nleft;
}

void ServerSocket::send(char *buffer)
{
    if(::send(socketDescriptor, buffer, strlen(buffer), 0) < 0)
    {
        //TODO throw exception
    }
}

std::size_t ServerSocket::receive(char *buffer, std::size_t)
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

void ServerSocket::close()
{
    if(::close(socketDescriptor) < 0)
    {
        //TODO throw exception
    }
}
