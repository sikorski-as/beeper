#ifndef BEEPER_DECRYPTOR_H
#define BEEPER_DECRYPTOR_H

#include "Buffer.h"

class Decryptor
{
public:
  virtual Buffer decrypt(Buffer data) = 0;
};


#endif //BEEPER_DECRYPTOR_H
