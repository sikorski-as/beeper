//
// Created by hubertborkowski on 12.04.19.
//

#ifndef BEEPER_CLIENTSOCKET_H
#define BEEPER_CLIENTSOCKET_H

#include "../src/Socket.h"

class TCPSocket : public Socket
{
public:
  explicit TCPSocket(Address address);
  TCPSocket(int socketDescriptor, Address address);

  virtual ssize_t readn(std::size_t n, char* buffer);
  virtual ssize_t writen(std::size_t n, const char* buffer);
};


#endif //BEEPER_CLIENTSOCKET_H
