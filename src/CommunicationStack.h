#ifndef BEEPER_COMMUNICATIONSTACK_H
#define BEEPER_COMMUNICATIONSTACK_H

#include "Event.h"
#include "../src/IONotifiable.h"

class CommunicationStack : public IONotifiable{
public:
    virtual Event getEvent() = 0;
    virtual void sendEvent(Event) = 0;
    virtual ~CommunicationStack(){};
};


#endif //BEEPER_COMMUNICATIONSTACK_H
