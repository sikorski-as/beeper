//
// Created by hubertborkowski on 12.04.19.
//

#ifndef BEEPER_TCPCLIENTSOCKET_H
#define BEEPER_TCPCLIENTSOCKET_H


#include "TCPSocket.h"

class TCPClientSocket : public TCPSocket
{
  explicit TCPClientSocket(Address address);
  TCPClientSocket(int newSocketDescriptor, Address address);

  void connect();
};


#endif //BEEPER_TCPCLIENTSOCKET_H
