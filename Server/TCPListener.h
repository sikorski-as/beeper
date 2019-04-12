//
// Created by hubertborkowski on 12.04.19.
//

#ifndef BEEPER_SERVERSOCKET_H
#define BEEPER_SERVERSOCKET_H

#include "../src/Socket.h"
#include "../Client/TCPSocket.h"
#include <cstddef>

class TCPListener : public Socket
{
public:
  TCPListener(Address address, int backlogLength);

  TCPSocket* accept();
  void start();

private:
  void bind();
  void listen(int backlogLength);

  bool listening;
  int backlogLength;
};


#endif //BEEPER_SERVERSOCKET_H
