//
// Created by hubertborkowski on 17.04.19.
//

#include "EncryptionLayer.h"

EncryptionLayer::EncryptionLayer(OutCommunicationLayer *out, InCommunicationLayer *in)
{
    outCommunicationLayer = out;
    inCommunicationLayer = in;
}

Buffer EncryptionLayer::decrypt(Buffer data)
{
    return data;
}

Buffer EncryptionLayer::encrypt(Buffer data)
{
    return data;
}

void EncryptionLayer::send(Buffer buffer)
{
    outCommunicationLayer->send(encrypt(buffer));
}

Buffer EncryptionLayer::receive()
{
    return decrypt(inCommunicationLayer->receive());
}
