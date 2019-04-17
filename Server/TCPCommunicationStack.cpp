
#include "TCPCommunicationStack.h"

TCPCommunicationStack::TCPCommunicationStack(Serializer *serializer,
                                             Deserializer *deserializer,
                                             Encryptor *encryptor, Decryptor *decryptor)
{
    this->serializer = serializer;
    this->deserializer = deserializer;
    this->encryptor = encryptor;
    this->decryptor = decryptor;
}

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
