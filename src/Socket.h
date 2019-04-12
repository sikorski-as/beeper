//
// Created by hubertborkowski on 11.04.19.
//

#ifndef BEEPER_SOCKET_H
#define BEEPER_SOCKET_H

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

using Address = sockaddr_in;

class Socket 
{
public:
  Socket(Address address);
  Socket(int newSocketDescriptor, Address address);


  virtual void close();

protected:
  int socketDescriptor;
  Address address;
};


#endif //BEEPER_SOCKET_H
