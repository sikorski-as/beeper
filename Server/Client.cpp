#include "Client.h"

Client::Client(CommunicationStack* communicationStack)
{
    commStack = communicationStack;
    commStack->setClient(this);
}

Client::~Client()
{
    delete commStack;
}
