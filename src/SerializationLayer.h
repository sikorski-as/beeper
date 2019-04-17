//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_SERIALIZATIONLAYER_H
#define BEEPER_SERIALIZATIONLAYER_H

#include "Serializer.h"
#include "Deserializer.h"

class SerializationLayer : public Serializer, public Deserializer
{
public:
  Event deserialize(std::string data) override;
  std::string encrypt(Event event) override;
};


#endif //BEEPER_SERIALIZATIONLAYER_H
