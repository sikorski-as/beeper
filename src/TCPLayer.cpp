#include <iostream>
#include "TCPLayer.h"

TCPLayer::TCPLayer(TCPSocket socket) : socket(socket) {
    upperLayer = nullptr;
    gotSize = false;
}

void TCPLayer::setUpperLayer(PacketHandler * newUpperLayer) {
    upperLayer = newUpperLayer;
}

void TCPLayer::notifyRead() {
    char incomingData[1024] = {0};


    if(!gotSize){
        int howManyBytesCanBeRead = sizeof(int) - incomingPacket.getSize();

        int readBytes = socket.receive(incomingData, howManyBytesCanBeRead);

        incomingPacket.append(incomingData, readBytes);

        if(incomingPacket.getSize() == sizeof(int)){
            char sizeBytes[sizeof(int)] = {0};
            sizeBytes[0] = incomingPacket.getData()[0];
            sizeBytes[1] = incomingPacket.getData()[1];
            sizeBytes[2] = incomingPacket.getData()[2];
            sizeBytes[3] = incomingPacket.getData()[3];

            int size = *(reinterpret_cast<int*>(sizeBytes));

            incomingPacketSize = ntohl(size);

            incomingPacket.consume(sizeof(int));
            gotSize = true;
        }
    }
    else{
        int howManyBytesCanBeRead = incomingPacketSize - incomingPacket.getSize();
        if(howManyBytesCanBeRead > 1024){
            howManyBytesCanBeRead = 1024;
        }

        int readBytes = socket.receive(incomingData, howManyBytesCanBeRead);

        incomingPacket.append(incomingData, readBytes);
        incomingPacketSize -= readBytes;

        if(incomingPacketSize == 0){
            char c = 0;
            incomingPacket.append(&c, 1);

            incomingPacketSize = 0;
            gotSize = false;

            upperLayer->handlePacket(incomingPacket);
            incomingPacket.consume(incomingPacket.getSize());
        }
    }

}

void TCPLayer::notifyWrite() {
    if(outgoingPacket.getSize() > 0){
        int sentBytes = socket.send(outgoingPacket.getData(), outgoingPacket.getSize());
        outgoingPacket.consume(sentBytes);
    }
    else{
        if(packetsToSend.getSize() > 0){
            auto packet = packetsToSend.get();
            outgoingPacket.append(::htonl(packet.getSize()));
            outgoingPacket.append(packet.getData(), packet.getSize());

            int sentBytes = socket.send(outgoingPacket.getData(), outgoingPacket.getSize());
            outgoingPacket.consume(sentBytes);
        }
    }
}

void TCPLayer::handlePacket(Buffer packet) {
    packetsToSend.put(packet);
}
