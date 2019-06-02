#include "SerializationLayer.h"

#include "Event.h"
#include <string>
#include <iostream>

Event SerializationLayer::deserialize() {
    Event e;

    while(true){
        try{
            Buffer b = packetQueue.get();
            e = Event::parse(b.getData());

            return e;
        }
        catch(...){
            throw EventNotValid("Malformed payload");
        }
    }
}

void SerializationLayer::serialize(Event e) {
    Buffer packet;
    auto s = e.dump(-1, ' ', true);
    packet.append(s);
    lowerLayer->handlePacket(packet);
}

void SerializationLayer::setLowerLayer(PacketHandler * newLowerLayer) {
    lowerLayer = newLowerLayer;
}

void SerializationLayer::handlePacket(Buffer packet) {
    packetQueue.put(packet);
}

SerializationLayer::SerializationLayer() {
    lowerLayer = nullptr;
}
