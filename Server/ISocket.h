//
// Created by hubertborkowski on 11.04.19.
//

#ifndef BEEPER_ISOCKET_H
#define BEEPER_ISOCKET_H

#include <iostream>
#include <netinet/in.h>

using Address = sockaddr_in;

class ISocket
{
public:
  virtual void bind(Address) = 0;
  virtual void listen(int) = 0;
  virtual void accept() = 0;

  virtual void connect() = 0;
  virtual void send(char*, std::size_t) = 0;
  virtual std::size_t receive(char*, std::size_t) = 0;
};


#endif //BEEPER_ISOCKET_H
