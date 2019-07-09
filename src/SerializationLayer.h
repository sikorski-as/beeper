#ifndef BEEPER_SERIALIZATIONLAYER_H
#define BEEPER_SERIALIZATIONLAYER_H

#include <queue>
#include "Event.h"
#include "SynchronizedQueue.h"
#include "Buffer.h"
#include "PacketHandler.h"
#include "json.hpp"

using json = nlohmann::json;

class SerializationLayer : public PacketHandler{
    SynchronizedQueue<Buffer> packetQueue;

    PacketHandler* lowerLayer;

public:
    SerializationLayer();
    Event deserialize();
    void serialize(Event);

    void setLowerLayer(PacketHandler*); // so we can push serialized events
    void handlePacket(Buffer) override; // so lower layer can give us data to deserialize
};


#endif //BEEPER_SERIALIZATIONLAYER_H
