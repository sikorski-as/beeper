#include "TCPCommunicationStack.h"

TCPCommunicationStack::TCPCommunicationStack(TCPSocket* socket, Serializer *serializer,
                                             Deserializer *deserializer)
{
    this->socket = socket;
    this->serializer = serializer;
    this->deserializer = deserializer;
}

void TCPCommunicationStack::insertIntoQueue(Event event)
{
    client->insertIntoQueue(event);
}

void TCPCommunicationStack::receiveEvent()
{
    insertIntoQueue(deserializer->recieve());
}

void TCPCommunicationStack::sendEvent(Event event)
{
    serializer->send(event);
}
