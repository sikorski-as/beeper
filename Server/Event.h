#ifndef BEEPER_EVENT_H
#define BEEPER_EVENT_H

#include <exception>
#include <string>
#include "../src/json.hpp"

using json = nlohmann::json;
using Event = json;

class EventError : public std::exception{
protected:
    std::string reason;
public:
    EventError(std::string reason) :reason(reason){

    }
    virtual const char* what(){
        return reason.c_str();
    }
};

class UnknownRequest{
public:
    operator Event(){
        Event e;
        e["type"] = "UNKNOWN_REQUEST";
        return e;
    }
};

class WelcomeMessage{
public:
    operator Event(){
        Event e;
        e["type"] = "WELCOME";
        return e;
    }
};

class RemovingMessage{
public:
    operator Event(){
        Event e;
        e["type"] = "BYE";
        return e;
    }
};

#endif //BEEPER_EVENT_H
