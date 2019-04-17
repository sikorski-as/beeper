#ifndef BEEPER_COMMUNICATIONLAYER_H
#define BEEPER_COMMUNICATIONLAYER_H

#include "Buffer.h"

class InCommunicationLayer
{
public:
  virtual void send(Buffer buffer) = 0;
};


#endif //BEEPER_COMMUNICATIONLAYER_H
