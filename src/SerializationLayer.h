//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_SERIALIZATIONLAYER_H
#define BEEPER_SERIALIZATIONLAYER_H

#include "Serializer.h"
#include "Deserializer.h"

class SerializationLayer : public Serializer, public Deserializer
{
  //TODO this is a work-in-progress version and does only a bare-bones serialization
public:
  Event deserialize(Buffer data) override;

  Buffer serialize(Event event) override;
};


#endif //BEEPER_SERIALIZATIONLAYER_H
