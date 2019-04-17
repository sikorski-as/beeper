#ifndef BEEPER_SERIALIZER_H
#define BEEPER_SERIALIZER_H

#include "../Server/Event.h"

class Serializer
{
public:
  virtual  encrypt(Event event) = 0;
};


#endif //BEEPER_SERIALIZER_H
