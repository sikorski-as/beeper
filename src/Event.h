#ifndef BEEPER_EVENT_H
#define BEEPER_EVENT_H

#include <iostream>
#include <exception>
#include <string>
#include <initializer_list>
#include <set>
#include "json.hpp"

//
// UTILS
//

using json = nlohmann::json;
using Event = json;

class EventError : public std::exception{
public:
    std::string reason;

    EventError(std::string reason) :reason(reason){

    }

    virtual const char* what(){
        return reason.c_str();
    }
};

class EventNotValid : public EventError{
public:
    EventNotValid(std::string reason) : EventError(reason){

    }
};

bool checkEventKeys(Event object, std::initializer_list<std::string> keysToBeInEvent);

//
// DTOs
//

class UnknownRequest{
public:
    UnknownRequest() = default;

    UnknownRequest(Event& e){
        if(!checkEventKeys(e, {"type"})) {
            throw EventNotValid("Improper UNKNOWN_REQUEST");
        }
    }

    operator Event(){
        Event e;
        e["type"] = "UNKNOWN_REQUEST";
        return e;
    }
};

class MalformedRequest{
public:
    std::string info;

    MalformedRequest() = default;

    MalformedRequest(std::string _info){
        info = _info;
    }

    MalformedRequest(Event& e){
        if(!checkEventKeys(e, {"type", "info"})) {
            throw EventNotValid("Improper MALFORMED_REQUEST");
        }
    }

    operator Event(){
        Event e;
        e["type"] = "MALFORMED_REQUEST";
        e["info"] = info;
        return e;
    }
};

class LoginRequest{
public:
    std::string username;
    std::string password;

    LoginRequest(std::string _username, std::string _password){
        username = _username;
        password = _password;
    }

    explicit LoginRequest(Event e){
        if(!checkEventKeys(e, {"type", "username", "password"})) {
            throw EventNotValid("Improper LOGIN_REQUEST");
        }
        try{
            username = e["username"].get<std::string>();
            password = e["password"].get<std::string>();
        }
        catch(...){
            throw EventNotValid("Improper LOGIN_REQUEST");
        }
    }

    operator Event(){
        Event e;
        e["type"] = "LOGIN_REQUEST";
        e["username"] = username;
        e["password"] = password;
        return e;
    }
};

class LoginResponse{
public:
    bool status;
    std::string token;

    LoginResponse(bool _status, std::string _token){
        status = _status;
        token = _token;
    }

    explicit LoginResponse(Event e){
        if(!checkEventKeys(e, {"type", "status", "token"})) {
            throw EventNotValid("Improper LOGIN_RESPONSE");
        }
        try{
            status = e["status"].get<bool>();
            token = e["token"].get<std::string>();
        }
        catch(...){
            throw EventNotValid("Improper LOGIN_RESPONSE");
        }
    }

    operator Event(){
        Event e;
        e["type"] = "LOGIN_RESPONSE";
        e["status"] = status;
        e["token"] = token;
        return e;
    }
};

#endif //BEEPER_EVENT_H
