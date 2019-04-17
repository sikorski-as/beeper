
#ifndef BEEPER_TCPCOMMUNICATIONSTACK_H
#define BEEPER_TCPCOMMUNICATIONSTACK_H

#include "CommunicationStack.h"
#include "Client.h"
#include "../src/TCPSocket.h"

class TCPCommunicationStack : public CommunicationStack
{
public:
  TCPCommunicationStack(Serializer*, Deserializer*, Encryptor*, Decryptor*);

  Event getEvent() override;
  void sendEvent(Event event) override;
  void setClient(Client* client) override { this->client = client; }
  void setSocket(Socket *socket) override { this->socket = reinterpret_cast<TCPSocket*>(socket); }

protected:
  void insertIntoQueue(Event event) override;

  Client* client;
  Serializer* serializer;
  Deserializer* deserializer;
  Encryptor* encryptor;
  Decryptor* decryptor;
  TCPSocket* socket;
};


#endif //BEEPER_TCPCOMMUNICATIONSTACK_H
