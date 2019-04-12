//
// Created by hubertborkowski on 12.04.19.
//

#ifndef BEEPER_SERVERSOCKET_H
#define BEEPER_SERVERSOCKET_H

#include "../src/Socket.h"
#include <cstddef>

class ServerSocket : Socket
{
public:
  ServerSocket();
  ServerSocket(int socketDescriptor, Address address);

  ssize_t readn(std::size_t n, char* buffer) override ;
  void send(char* buffer) override ;
  std::size_t receive(char* buffer, std::size_t) override ;
  void close() override ;
};


#endif //BEEPER_SERVERSOCKET_H
