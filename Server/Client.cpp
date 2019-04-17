#include <iostream>
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

void Client::insertIntoQueue(Event event)
{
    eventQueue.push(event);
}

void Client::send(Event event)
{
    commStack->sendEvent(event);
}

void Client::receive()
{
    commStack->receiveEvent();
}

void Client::handleEvent()
{
    if(!eventQueue.empty())
    {
        Event event = eventQueue.front();
        eventQueue.pop();
        std::cout << "Typ zdarzenia: " << event.getType() << std::endl;
    }
}
