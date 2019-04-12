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
  explicit ServerSocket(Address address);

  Socket* accept();
  void start();

private:
  void bind();
  void listen(int backlogLength);

  bool listening;
};


#endif //BEEPER_SERVERSOCKET_H
