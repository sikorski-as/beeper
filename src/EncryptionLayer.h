//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_ENCRYPTIONLAYER_H
#define BEEPER_ENCRYPTIONLAYER_H

#include "Encryptor.h"
#include "Decryptor.h"

class EncryptionLayer : public Encryptor, public Decryptor
{
  //TODO this is a work-in-progress version and doesn't actually encrypt anything
public:
  Buffer decrypt(Buffer data) override;

  Buffer encrypt(Buffer data) override;
};


#endif //BEEPER_ENCRYPTIONLAYER_H
