
#ifndef BEEPER_TCPCOMMUNICATIONSTACK_H
#define BEEPER_TCPCOMMUNICATIONSTACK_H

#include "CommunicationStack.h"
#include "Client.h"
#include "../src/TCPSocket.h"

class TCPCommunicationStack : public CommunicationStack
{
public:
  TCPCommunicationStack(TCPSocket* socket, Serializer*, Deserializer*);

  void receiveEvent() override;
  void sendEvent(Event event) override;
  void setClient(Client* client) override { this->client = client; }

protected:
  void insertIntoQueue(Event event) override;

  Client* client;
  Serializer* serializer;
  Deserializer* deserializer;
  TCPSocket* socket;
};


#endif //BEEPER_TCPCOMMUNICATIONSTACK_H
