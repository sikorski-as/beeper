//
// Created by hubertborkowski on 12.04.19.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket(Address address) : Socket(address)
{

}

TCPSocket::TCPSocket(int socketDescriptor, Address address) : Socket(socketDescriptor, address)
{

}


ssize_t TCPSocket::readn(std::size_t n, char *buffer)
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

ssize_t TCPSocket::writen(std::size_t n, const char *buffer)
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
