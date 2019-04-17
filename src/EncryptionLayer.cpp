//
// Created by hubertborkowski on 17.04.19.
//

#include "EncryptionLayer.h"

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

Buffer EncryptionLayer::recieve()
{
    return decrypt(inCommunicationLayer->recieve());
}
