#ifndef BEEPER_SERIALIZATIONLAYER_H
#define BEEPER_SERIALIZATIONLAYER_H

#include "Serializer.h"
#include "Deserializer.h"
#include "OutCommunicationLayer.h"
#include "InCommunicationLayer.h"

class SerializationLayer : public Serializer, public Deserializer
{
  //TODO this is a work-in-progress version and does only a bare-bones serialization
public:
  SerializationLayer(OutCommunicationLayer*, InCommunicationLayer*);

  Event recieve() override;

  void send(Event event) override;

protected:
  Event deserialize(Buffer data) override;

  Buffer serialize(Event event) override;

  OutCommunicationLayer* outCommunicationLayer;
  InCommunicationLayer* inCommunicationLayer;
};


#endif //BEEPER_SERIALIZATIONLAYER_H
