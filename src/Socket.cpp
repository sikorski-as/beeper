#include "Socket.h"

bool Socket::operator==(const Socket& another){
    return socketDescriptor == another.socketDescriptor;
}

Address Socket::getLocalAddress(){
    Address address;
    socklen_t localAddressLength = sizeof(address);
    if (getsockname(socketDescriptor,(struct sockaddr *) &address, &localAddressLength) == -1) {
        throw "Socket error: could not get address of assigned socket!";
    }
    else{
        return address;
    }
}

Socket::Socket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor == 0)
    {
        throw "Socket error: could not create socket!";
    }
}

Socket::Socket(int newSocketDescriptor)
{
    this->socketDescriptor = newSocketDescriptor;
}

void Socket::close()
{
    if(::close(socketDescriptor) < 0)
    {
        throw "Socket error: could not close socket!";
    }
}
