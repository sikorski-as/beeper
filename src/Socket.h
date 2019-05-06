#ifndef BEEPER_SOCKET_H
#define BEEPER_SOCKET_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <exception>
#include <string>

#include "Address.h"
//#include "Selector.h"

class Selector;
class Socket 
{
public:
    friend class Selector;
    Address getLocalAddress();
    bool operator==(const Socket&);
    int getDescriptor() const;
    void close();
protected:
    int socketDescriptor;
    Socket();
    Socket(int newSocketDescriptor);

    class SocketError : public std::exception{
    protected:
        std::string reason;
        int code;
    public:
        SocketError(std::string reason, int errorCode = 0)
        : reason(reason + " (" + std::to_string(code) + ")"), code(errorCode){

        }
        virtual const char* what() { return reason.c_str();}
    };
};

#endif //BEEPER_SOCKET_H
