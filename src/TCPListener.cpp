#include "TCPListener.h"
#include <iostream>

TCPListener::TCPListener(): Socket()
{
    this->listening = false;
    this->backlogLength = -1;
}

void TCPListener::start(Address address, int backlogLength)
{
    if(backlogLength < 1){
        throw TCPListenerError("TCPListener's queue cannot be shorter than 1");
    }
    this->backlogLength = backlogLength;

    if(!listening)
    {
        if(::bind(socketDescriptor, (sockaddr*)&address, sizeof(address)) < 0)
        {
            int x = errno;
            throw TCPListenerError("Could not bind", x);
        }

        int enable = 1;
        int status = setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
        if (status < 0){
            int x = errno;
            throw TCPListenerError("Could not setup address reusing for TCPListener", x);
        }

        if(::listen(socketDescriptor, backlogLength) < 0)
        {
            int x = errno;
            throw TCPListenerError("Could not start listening", x);
        }

        listening = true;
    }
    else
    {
        throw TCPListenerError("TCPListener is already listening");
    }
}

TCPSocket TCPListener::accept()
{
    if(!listening){
        throw TCPListenerError("Could not accept while TCPListener is not listening");
    }

    socklen_t remoteAddressLength;
    Address remoteAddress;
    int newSocketDescriptor = ::accept4(socketDescriptor, (sockaddr*)&remoteAddress, &remoteAddressLength, 0);

    if(newSocketDescriptor < 0)
    {
        int x = errno;
        throw TCPListenerError("Could not accept connection", x);
    }
    else
    {
        return TCPSocket(newSocketDescriptor);
    }
}
