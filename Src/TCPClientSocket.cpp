#include "TCPClientSocket.h"

TCPClientSocket::TCPClientSocket()
: TCPSocket()
{

}

void TCPClientSocket::connect(Address remoteAddress)
{
    if(::connect(socketDescriptor, (sockaddr*)&remoteAddress, sizeof(remoteAddress)) < 0)
    {
        throw "TCPClientSocket error: could not connect!";
    }
    hasRemote = true;
}
