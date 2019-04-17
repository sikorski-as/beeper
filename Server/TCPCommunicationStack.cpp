
#include "TCPCommunicationStack.h"

void TCPCommunicationStack::insertIntoQueue(Event event)
{
    client->insertIntoQueue(event);
}

Event TCPCommunicationStack::getEvent()
{

}

void TCPCommunicationStack::sendEvent(Event event)
{

}
