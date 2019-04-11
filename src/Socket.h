//
// Created by hubertborkowski on 11.04.19.
//

#ifndef BEEPER_SOCKET_H
#define BEEPER_SOCKET_H

#include "ISocket.h"
#include <string.h>

class Socket : public ISocket
{
public:
  Socket();
  Socket(int socketDescriptor, Address address);

  void bind() override ;
  void listen(int backlogLength) override ;
  ISocket* accept() override ;

  void connect() override ;
  void send(char* buffer) override ;
  std::size_t receive(char* buffer, std::size_t) override ;
  void close() override ;
};


#endif //BEEPER_SOCKET_H
