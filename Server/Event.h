//
// Created by hubertborkowski on 17.04.19.
//

#ifndef BEEPER_EVENT_H
#define BEEPER_EVENT_H

#include <string>

class Event
{
public:
  explicit Event(std::string type);

private:
  std::string type;
};


#endif //BEEPER_EVENT_H
