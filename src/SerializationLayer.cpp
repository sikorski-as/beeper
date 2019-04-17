//
// Created by hubertborkowski on 17.04.19.
//

#include "SerializationLayer.h"

SerializationLayer::SerializationLayer(OutCommunicationLayer * out, InCommunicationLayer * in)
{
    inCommunicationLayer = in;
    outCommunicationLayer = out;
}

Event SerializationLayer::deserialize(Buffer data)
{
    return Event(data.getData());
}

Buffer SerializationLayer::serialize(Event event)
{
    Buffer buffer;
    buffer.append(event.getType());

    return buffer;
}

Event SerializationLayer::recieve()
{
    Buffer buffer = inCommunicationLayer->receive();

    return deserialize(buffer);
}

void SerializationLayer::send(Event event)
{
    outCommunicationLayer->send(serialize(event));
}

