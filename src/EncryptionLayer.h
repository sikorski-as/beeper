//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_ENCRYPTIONLAYER_H
#define BEEPER_ENCRYPTIONLAYER_H

#include "Encryptor.h"
#include "Decryptor.h"

class EncryptionLayer : public Encryptor, public Decryptor
{
public:
  std::string decrypt(std::string data) override;

  std::string encrypt(std::string data) override;
};


#endif //BEEPER_ENCRYPTIONLAYER_H
