#ifndef BEEPER_OUTCOMMUNICATIONLAYER_H
#define BEEPER_OUTCOMMUNICATIONLAYER_H

#include "Buffer.h"

class InCommunicationLayer
{
public:
  virtual Buffer receive() = 0;
};


#endif //BEEPER_OUTCOMMUNICATIONLAYER_H
