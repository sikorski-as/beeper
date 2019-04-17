#ifndef BEEPER_DESERIALIZER_H
#define BEEPER_DESERIALIZER_H

#include "../Server/Event.h"

class Deserializer
{
public:
  virtual Event deserialize(std::string data) = 0;
};


#endif //BEEPER_DESERIALIZER_H
