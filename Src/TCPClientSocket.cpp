#include "TCPClientSocket.h"

TCPClientSocket::TCPClientSocket()
: TCPSocket()
{

}

void TCPClientSocket::connect(Address remoteAddress)
{
    /*
    int enable = 1;
    int status = setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    if (status < 0){
        int x = errno;
        throw "Could not setup address reusing for TCPListener";
    }
     */

    if(::connect(socketDescriptor, (sockaddr*)&remoteAddress, sizeof(remoteAddress)) < 0)
    {
        throw "TCPClientSocket error: could not connect!";
    }
    hasRemote = true;
}
