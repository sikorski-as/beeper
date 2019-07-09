#ifndef BEEPER_TCPLAYER_H
#define BEEPER_TCPLAYER_H

#include "IONotifiable.h"
#include "PacketHandler.h"
#include "TCPSocket.h"
#include "SynchronizedQueue.h"
#include "Buffer.h"

class TCPLayer : public IONotifiable, public PacketHandler{
    PacketHandler* upperLayer;
    TCPSocket socket;

    SynchronizedQueue<Buffer> packetsToSend;

    Buffer incomingPacket;
    int incomingPacketSize;
    bool gotSize;

    Buffer outgoingPacket;
public:
    TCPLayer(TCPSocket);

    void setUpperLayer(PacketHandler*);

    void notifyRead() override;
    void notifyWrite() override;

    void handlePacket(Buffer) override;
};


#endif //BEEPER_TCPLAYER_H
