#include "TCPSocket.h"

TCPSocket::TCPSocket()
: Socket()
{
    this->hasRemote = false;
}

TCPSocket::TCPSocket(int socketDescriptor)
{
    this->socketDescriptor = socketDescriptor;
    this->hasRemote = true;
}

Address TCPSocket::getRemoteAddress(){
    if(hasRemote){
        Address  remoteAddress;
        socklen_t len = sizeof(remoteAddress);
        if(getpeername(socketDescriptor, (struct sockaddr*)&remoteAddress, &len) == 0){
            return remoteAddress;
        }
        else{
            throw "TCPSocket error: getRemote(): could not get the remote address";
        }
    }
    else{
        throw "TCPSocket error: getRemote(): no remote";
    }
}

int TCPSocket::receive(int size, char *buffer)
{
    if(!hasRemote)
    {
        throw "TCPSocket error: no remote to read from!";
    }

    int received = ::read(socketDescriptor, buffer, size);
    if(received < 0){
        throw "TCPSocket: send(): error!";
    }
    else if(received == 0){
        throw "TCPSocket: connection ended!";
    }

    return received;
}

int TCPSocket::send(int size, const char *buffer)
{
    if(!hasRemote)
    {
        throw "TCPSocket error: no remote to send to!";
    }

    int sent = ::write(socketDescriptor, buffer, size);
    if(sent < 0){
        throw "TCPSocket: send(): error!";
    }
    else if(sent == 0){
        throw "TCPSocket: connection ended!";
    }

    return sent;
}
