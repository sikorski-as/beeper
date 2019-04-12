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
  virtual ssize_t readn(std::size_t n, char* buffer) = 0;
  virtual void send(char* buffer) = 0;
  virtual std::size_t receive(char* buffer, std::size_t) = 0;
  virtual void close() = 0;

protected:
  int socketDescriptor;
  Address address;
};


#endif //BEEPER_SOCKET_H
