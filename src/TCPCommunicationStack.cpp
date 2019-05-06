#include "TCPCommunicationStack.h"

TCPCommunicationStack::TCPCommunicationStack(TCPSocket & socket) : socketLayer(socket)
{
    serializationLayer.setLowerLayer(&socketLayer);
    socketLayer.setUpperLayer(&serializationLayer);
}

Event TCPCommunicationStack::getEvent() {
    return serializationLayer.deserialize();
}

void TCPCommunicationStack::sendEvent(Event e) {
    serializationLayer.serialize(e);
}

void TCPCommunicationStack::notifyRead() {
    socketLayer.notifyRead();
}

void TCPCommunicationStack::notifyWrite() {
    socketLayer.notifyWrite();
}

TCPCommunicationStack::~TCPCommunicationStack() {
    // nothing needs to be cleaned for now
}
