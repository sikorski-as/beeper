//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_CLIENT_H
#define BEEPER_CLIENT_H


#include <queue>
#include "CommunicationStack.h"

class CommunicationStack;

class Client
{
public:
  Client(CommunicationStack* communicationStack);

  ~Client();

private:
  std::queue<Event> eventQueue;
  CommunicationStack* commStack;
};


#endif //BEEPER_CLIENT_H
