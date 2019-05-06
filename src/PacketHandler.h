#ifndef BEEPER_PACKETHANDLER_H
#define BEEPER_PACKETHANDLER_H

#include "../src/Buffer.h"

class PacketHandler {
public:
    virtual void handlePacket(Buffer) = 0;
};


#endif //BEEPER_PACKETHANDLER_H
