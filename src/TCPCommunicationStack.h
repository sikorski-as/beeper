#ifndef BEEPER_TCPCOMMUNICATIONSTACK_H
#define BEEPER_TCPCOMMUNICATIONSTACK_H

#include "../src/CommunicationStack.h"
#include "../src/SerializationLayer.h"
#include "../src/TCPSocket.h"
#include "../src/TCPLayer.h"
#include "../Server/Event.h"

class TCPCommunicationStack : public CommunicationStack{
    SerializationLayer serializationLayer;
    TCPLayer socketLayer;
public:
    explicit TCPCommunicationStack(TCPSocket&);

    Event getEvent() override;
    void sendEvent(Event) override;

    void notifyRead() override;
    void notifyWrite() override;

    virtual ~TCPCommunicationStack();
};


#endif //BEEPER_TCPCOMMUNICATIONSTACK_H
