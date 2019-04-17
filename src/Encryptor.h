#ifndef BEEPER_ENCRYPTOR_H
#define BEEPER_ENCRYPTOR_H

#include "Buffer.h"

class Encryptor
{
public:
  virtual Buffer encrypt(Buffer data) = 0;
};


#endif //BEEPER_ENCRYPTOR_H
