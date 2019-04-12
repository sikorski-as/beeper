//
// Created by hubertborkowski on 12.04.19.
//

#include "ClientSocket.h"

ClientSocket::ClientSocket(Address address) : Socket(address)
{

}

ssize_t ClientSocket::readn(std::size_t n, char *buffer)
{
    return 0;
}

void ClientSocket::send(char *buffer)
{

}

std::size_t ClientSocket::receive(char *buffer, std::size_t)
{
    return 0;
}

void ClientSocket::close()
{

}
