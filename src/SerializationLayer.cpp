#include "SerializationLayer.h"
#include <string>
#include <iostream>

Event SerializationLayer::deserialize() {
    Event e;

    while(true){
        try{
            Buffer b = packetQueue.get();
            e = Event::parse(b.getData());

            //if(e["type"].is_string())
            return e;
        }
        catch(...){
            // malformed json
            // std::cout << "bad data, deserialization failed\n\n";
        }
    }
}

void SerializationLayer::serialize(Event e) {
    Buffer packet;
    packet.append(e.dump());
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
