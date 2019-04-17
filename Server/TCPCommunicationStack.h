
#ifndef BEEPER_TCPCOMMUNICATIONSTACK_H
#define BEEPER_TCPCOMMUNICATIONSTACK_H

#include "CommunicationStack.h"
#include "Client.h"
#include "../src/TCPSocket.h"

class TCPCommunicationStack : public CommunicationStack
{
public:
  explicit TCPCommunicationStack() = default;

  Event getEvent() override;
  void sendEvent(Event event) override;
  void setClient(Client* client) { this->client = client; };

protected:
  void insertIntoQueue(Event event) override;

  Client* client;

  TCPSocket socket;
};


#endif //BEEPER_TCPCOMMUNICATIONSTACK_H