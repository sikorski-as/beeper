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
  explicit TCPListener(Address address);

  TCPSocket* accept();
  void start();

private:
  void bind();
  void listen(int backlogLength);

  bool listening;
};


#endif //BEEPER_SERVERSOCKET_H
