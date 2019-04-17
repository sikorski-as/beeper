#ifndef BEEPER_SERIALIZER_H
#define BEEPER_SERIALIZER_H

#include "../Server/Event.h"
#include "Buffer.h"

class Serializer
{
public:
  virtual Buffer serialize(Event event) = 0;
};


#endif //BEEPER_SERIALIZER_H
