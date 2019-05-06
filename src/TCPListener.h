#ifndef BEEPER_TCPLISTENER_H
#define BEEPER_TCPLISTENER_H

#include <cstddef>
#include "Socket.h"
#include "Address.h"
#include "TCPSocket.h"

class TCPSocket;
class TCPListener : public Socket
{
public:
    TCPListener();

    TCPSocket accept();
    void start(Address address, int backlogLength); // listening address, length of the incoming connections queue

    class TCPListenerError : public std::exception{
    protected:
        std::string reason;
        int code;
    public:
        TCPListenerError(std::string reason, int errorCode = 0) : reason(reason + " (" + std::to_string(code) + ")"), code(errorCode){}
        virtual const char* what() { return reason.c_str();}
    };
private:
    bool listening;
    int backlogLength;
};

#endif //BEEPER_TCPLISTENER_H
