#ifndef BEEPER_DESERIALIZER_H
#define BEEPER_DESERIALIZER_H

#include "../Server/Event.h"
#include "Buffer.h"

class Deserializer
{
public:
  virtual Event recieve() = 0;
protected:
  virtual Event deserialize(Buffer data) = 0;
};


#endif //BEEPER_DESERIALIZER_H
