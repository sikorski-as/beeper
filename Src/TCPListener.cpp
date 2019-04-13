#include "TCPListener.h"
#include <iostream>

TCPListener::TCPListener(Address address): Socket()
{
    this->listening = false;
    this->backlogLength = -1;

    if(::bind(socketDescriptor, (sockaddr*)&address, sizeof(address)) < 0)
    {
        throw "TCPListener error: could not bind!";
    }
}

void TCPListener::start(int backlogLength)
{
    if(backlogLength < 1){
        throw "TCPListener error: queue cannot be shorter than 1!";
    }
    this->backlogLength = backlogLength;

    if(!listening)
    {
        if(::listen(socketDescriptor, backlogLength) < 0)
        {
            throw "TCPListener error: could not listen!";
        }

        listening = true;
    }
    else
    {
        throw "TCPListener error: already listening!";
    }
}

TCPSocket TCPListener::accept()
{
    if(!listening){
        throw "TCPListener error: accept(): not listening!";
    }

    socklen_t remoteAddressLength;
    Address remoteAddress;
    int newSocketDescriptor = ::accept(socketDescriptor, (sockaddr*)&remoteAddress, &remoteAddressLength);

    if(newSocketDescriptor < 0)
    {
        int x = errno;
        std::cout << "errno: " << x << std::endl;
        throw "TCPListener error: could not accept connection!";
    }
    else
    {
        return TCPSocket(newSocketDescriptor);
    }

}
