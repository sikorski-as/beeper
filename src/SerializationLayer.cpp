//
// Created by hubertborkowski on 17.04.19.
//

#include "SerializationLayer.h"

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

