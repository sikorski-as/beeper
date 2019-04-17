//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_COMMUNICATIONSTACK_H
#define BEEPER_COMMUNICATIONSTACK_H

#include "Event.h"
#include "Client.h"
#include "../src/Encryptor.h"
#include "../src/Decryptor.h"
#include "../src/Deserializer.h"
#include "../src/Serializer.h"
#include "../src/Socket.h"

class Client;

class CommunicationStack
{
public:
  virtual void receiveEvent() = 0;
  virtual void sendEvent(Event event) = 0;
  
  virtual void setClient(Client* client) = 0;
  virtual void setSocket(Socket* socket) = 0;

protected:
  virtual void insertIntoQueue(Event event) = 0;
};


#endif //BEEPER_COMMUNICATIONSTACK_H
