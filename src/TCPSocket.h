#ifndef BEEPER_TCPSOCKET_H
#define BEEPER_TCPSOCKET_H

#include <exception>
#include <string>
#include "Socket.h"
#include "TCPListener.h"
#include "Address.h"
#include "OutCommunicationLayer.h"
#include "InCommunicationLayer.h"

class TCPListener;
class TCPSocket : public Socket, public OutCommunicationLayer, public InCommunicationLayer
{
    friend class TCPListener; // so TCPListener can create TCPSockets for clients providing descriptor
protected:
    bool hasRemote;
    TCPSocket(int socketDescriptor);
    TCPSocket();

public:
  void send(Buffer buffer) override;

  Buffer receive() override;

public:
    Address getRemoteAddress();
    //virtual ssize_t readn(std::size_t n, char* buffer);
    //virtual ssize_t writen(std::size_t n, const char* buffer);

    int send(const char * buffer, int size);
    int receive(char * buffer, int size);

    void sendn(const char * buffer, int size);
    void receiven(char * buffer, int size);

    class TCPSocketError : public std::exception{
    protected:
        std::string reason;
        int code;
    public:
        TCPSocketError(std::string reason, int errorCode = 0) : reason(reason + " (" + std::to_string(code) + ")"), code(errorCode){}
        virtual const char* what() { return reason.c_str();}
    };
    class ConnectionClosed : public TCPSocketError{
    public:
        ConnectionClosed() : TCPSocketError("Connection closed"){}
    };
    class NoRemote : public TCPSocketError{
    public:
        NoRemote() : TCPSocketError("No remote"){}
    };
    class IOError : public TCPSocketError{
    public:
        IOError(std::string reason="", int code=0) : TCPSocketError(std::string("IO exception") + reason, code){}
    };

};

#endif //BEEPER_TCPSOCKET_H
