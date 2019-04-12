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

ssize_t Socket::readn(std::size_t n, char *buffer)
{
    std::size_t nleft;
    ssize_t nread;

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

ssize_t Socket::writen(std::size_t n, const char *buffer)
{
    std::size_t  nleft;
    ssize_t nwritten;

    nleft = n;
    while(nleft > 0)
    {
        if((nwritten = ::write(socketDescriptor, buffer, nleft)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        buffer += nwritten;
    }

    return n;
}

void Socket::close()
{
    if(::close(socketDescriptor) < 0)
    {
        //TODO throw exception
    }
}
