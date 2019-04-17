#ifndef BEEPER_OUTCOMMUNICATIONLAYER_H
#define BEEPER_OUTCOMMUNICATIONLAYER_H

#include "Buffer.h"

class OutCommunicationLayer
{
public:
  virtual Buffer recieve() = 0;
};


#endif //BEEPER_OUTCOMMUNICATIONLAYER_H
