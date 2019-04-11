//
// Created by hubertborkowski on 11.04.19.
//

#ifndef BEEPER_ISOCKET_H
#define BEEPER_ISOCKET_H

#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

using Address = sockaddr_in;

class ISocket
{
public:
  virtual void bind() = 0;
  virtual void listen(int backlogLenght) = 0;
  virtual ISocket* accept() = 0;

  virtual void connect() = 0;
  virtual void send(char* buffer) = 0;
  virtual std::size_t receive(char* buffer, std::size_t) = 0;
  virtual void close() = 0;

protected:
  int socketDescriptor;
  Address address;
};


#endif //BEEPER_ISOCKET_H
