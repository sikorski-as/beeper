#include "Client.h"

Client::Client(CommunicationStack* communicationStack)
{
    commStack = communicationStack;
    commStack->setClient(this);
}

Client::~Client()
{
    delete commStack;
}

void Client::insertIntoQueue(Event event)
{
    eventQueue.push(event);
}
