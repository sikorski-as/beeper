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

    int enable = 1;
    int status = setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    if (status < 0){
        throw TCPSocketError("Could not setup address reusing", errno);
    }
}

Address TCPSocket::getRemoteAddress(){
    if(hasRemote){
        Address  remoteAddress;
        socklen_t len = sizeof(remoteAddress);
        if(getpeername(socketDescriptor, (struct sockaddr*)&remoteAddress, &len) == 0){
            return remoteAddress;
        }
        else{
            int x = errno;
            throw TCPSocketError("Could not get remote peer's address", x);
        }
    }
    else{
        throw NoRemote();
    }
}

int TCPSocket::receive(char * buffer, int size)
{
    if(!hasRemote)
    {
        throw NoRemote();
    }

    int received = ::read(socketDescriptor, buffer, size);
    if(received < 0){
        int x = errno;
        throw IOError(" - could not receive", x);
    }
    else if(received == 0){
        throw ConnectionClosed();
    }

    return received;
}

int TCPSocket::send(const char *buffer, int size)
{
    if(!hasRemote)
    {
        throw NoRemote();
    }

    int sent = ::write(socketDescriptor, buffer, size);
    if(sent < 0){
        int x = errno;
        throw IOError(" - could not send", x);
    }
    else if(sent == 0){
        throw ConnectionClosed();
    }

    return sent;
}

void TCPSocket::sendn(const char *buffer, int size) {
    int left = size;
    do{
        int sent = send(buffer, left);
        left -= sent;
        buffer += sent;
    }while(left != 0);
}

void TCPSocket::receiven(char *buffer, int size) {
    int left = size;
    do{
        int recvd = receive(buffer, left);
        left -= recvd;
        buffer += recvd;
    }while(left != 0);
}

void TCPSocket::send(Buffer buffer)
{
    //TODO
}

Buffer TCPSocket::receive()
{
    //TODO
}
