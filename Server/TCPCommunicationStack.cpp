
#include "TCPCommunicationStack.h"

void TCPCommunicationStack::insertIntoQueue(Event event)
{
    client->getQueue()->push(event);
}

Event TCPCommunicationStack::getEvent()
{

}

void TCPCommunicationStack::sendEvent(Event event)
{

}
