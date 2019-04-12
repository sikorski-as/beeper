//
// Created by hubertborkowski on 12.04.19.
//

#include "TCPClientSocket.h"

TCPClientSocket::TCPClientSocket(Address address) : TCPSocket(address)
{

}

TCPClientSocket::TCPClientSocket(int newSocketDescriptor, Address address) : TCPSocket(newSocketDescriptor, address)
{

}

void TCPClientSocket::connect()
{
    if(::connect(socketDescriptor, (sockaddr*)&address, sizeof(address)) < 0)
    {
        //TODO throw exception
    }
}
