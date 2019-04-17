//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_ENCRYPTIONLAYER_H
#define BEEPER_ENCRYPTIONLAYER_H

#include "Encryptor.h"
#include "Decryptor.h"
#include "OutCommunicationLayer.h"
#include "InCommunicationLayer.h"

class EncryptionLayer : public Encryptor, public Decryptor, public OutCommunicationLayer, public InCommunicationLayer
{
  //TODO this is a work-in-progress version and doesn't actually encrypt anything
public:
  EncryptionLayer(OutCommunicationLayer* out, InCommunicationLayer* in);

  Buffer decrypt(Buffer data) override;

  Buffer encrypt(Buffer data) override;

  void send(Buffer buffer) override;

  Buffer receive() override;

protected:
  OutCommunicationLayer* outCommunicationLayer;
  InCommunicationLayer* inCommunicationLayer;
};


#endif //BEEPER_ENCRYPTIONLAYER_H
