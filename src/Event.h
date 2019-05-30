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

class LogoutRequest
{
public:
  std::string username;

  LogoutRequest(std::string _username){
      username = _username;
  }

  explicit LogoutRequest(Event e){
      if(!checkEventKeys(e, {"type", "username"})) {
          throw EventNotValid("Improper LOGOUT_REQUEST");
      }
      try{
          username = e["username"].get<std::string>();
      }
      catch(...){
          throw EventNotValid("Improper LOGOUT_REQUEST");
      }
  }

  operator Event(){
      Event e;
      e["type"] = "LOGOUT_REQUEST";
      e["username"] = username;
      return e;
  }
};

class LogoutResponse
{
public:
  bool status;

  LogoutResponse(bool _status){
      status = _status;
  }

  explicit LogoutResponse(Event e){
      if(!checkEventKeys(e, {"type", "status"})) {
          throw EventNotValid("Improper LOGOUT_RESPONSE");
      }
      try{
          status = e["status"].get<bool>();
      }
      catch(...){
          throw EventNotValid("Improper LOGOUT_RESPONSE");
      }
  }

  operator Event(){
      Event e;
      e["type"] = "LOGOUT_RESPONSE";
      e["status"] = status;
      return e;
  }
};

class RegisterRequest
{
public:
  std::string username;
  std::string password;
  std::string alias;
  std::string bio;

  RegisterRequest(std::string username, std::string password, std::string alias, std::string bio){
	  this->username = username;
	  this->password = password;
	  this->alias = alias;
	  this->bio = bio;
  }

  explicit RegisterRequest(Event e){
	  if(!checkEventKeys(e, {"type", "username", "password", "alias", "bio"})) {
		  throw EventNotValid("Improper REGISTER_REQUEST");
	  }
	  try{
		  username = e["username"].get<std::string>();
		  password = e["password"].get<std::string>();
		  alias = e["alias"].get<std::string>();
		  bio = e["bio"].get<std::string>();
	  }
	  catch(...){
		  throw EventNotValid("Improper REGISTER_REQUEST");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "REGISTER_REQUEST";
	  e["username"] = username;
	  e["password"] = password;
	  e["alias"] = alias;
	  e["bio"] = bio;
	  return e;
  }
};

class RegisterResponse
{
public:
  bool status;

  RegisterResponse(bool _status){
	  status = _status;
  }

  explicit RegisterResponse(Event e){
	  if(!checkEventKeys(e, {"type", "status"})) {
		  throw EventNotValid("Improper REGISTER_RESPONSE");
	  }
	  try{
		  status = e["status"].get<bool>();
	  }
	  catch(...){
		  throw EventNotValid("Improper REGISTER_RESPONSE");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "REGISTER_RESPONSE";
	  e["status"] = status;
	  return e;
  }
};

class AddPostRequest
{
public:
  std::string content;

  AddPostRequest(std::string content){
	  this->content = content;
  }

  explicit AddPostRequest(Event e){
	  if(!checkEventKeys(e, {"type", "content"})) {
		  throw EventNotValid("Improper ADD_POST_REQUEST");
	  }
	  try{
		  content = e["content"].get<std::string>();

	  }
	  catch(...){
		  throw EventNotValid("Improper ADD_POST_REQUEST");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "ADD_POST_REQUEST";
	  e["content"] = content;
	  return e;
  }
};

class AddPostResponse
{
public:
  bool status;

  AddPostResponse(bool _status){
	  status = _status;
  }

  explicit AddPostResponse(Event e){
	  if(!checkEventKeys(e, {"type", "status"})) {
		  throw EventNotValid("Improper ADD_POST_RESPONSE");
	  }
	  try{
		  status = e["status"].get<bool>();
	  }
	  catch(...){
		  throw EventNotValid("Improper ADD_POST_RESPONSE");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "ADD_POST_RESPONSE";
	  e["status"] = status;
	  return e;
  }
};

class LikePostRequest
{
public:
  int postId;

  LikePostRequest(int postId){
	  this->postId = postId;
  }

  explicit LikePostRequest(Event e){
	  if(!checkEventKeys(e, {"type", "post_id"})) {
		  throw EventNotValid("Improper LIKE_POST_REQUEST");
	  }
	  try{
		  postId = e["post_id"].get<int>();

	  }
	  catch(...){
		  throw EventNotValid("Improper LIKE_POST_REQUEST");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "LIKE_POST_REQUEST";
	  e["post_id"] = postId;
	  return e;
  }
};

class LikePostResponse
{
public:
  bool status;

  LikePostResponse(bool _status){
	  status = _status;
  }

  explicit LikePostResponse(Event e){
	  if(!checkEventKeys(e, {"type", "status"})) {
		  throw EventNotValid("Improper LIKE_POST_RESPONSE");
	  }
	  try{
		  status = e["status"].get<bool>();
	  }
	  catch(...){
		  throw EventNotValid("Improper LIKE_POST_RESPONSE");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "LIKE_POST_RESPONSE";
	  e["status"] = status;
	  return e;
  }
};

class GetNNewPostsRequest
{
public:
  int numberOfPosts;

  GetNNewPostsRequest(int number){
	  this->numberOfPosts = number;
  }

  explicit GetNNewPostsRequest(Event e){
	  if(!checkEventKeys(e, {"type", "post_id"})) {
		  throw EventNotValid("Improper GET_N_NEW_POSTS_REQUEST");
	  }
	  try{
		  numberOfPosts = e["number_of_posts"].get<int>();

	  }
	  catch(...){
		  throw EventNotValid("Improper GET_N_NEW_POSTS_REQUEST");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "GET_N_NEW_POSTS_REQUEST";
	  e["number_of_posts"] = numberOfPosts;
	  return e;
  }
};

class GetNNewPostsResponse
{
public:
  bool status;
  json data;

  GetNNewPostsResponse(bool _status, json data){
	  status = _status;
	  this->data = data;
  }

  explicit GetNNewPostsResponse(Event e){
	  if(!checkEventKeys(e, {"type", "status"})) {
		  throw EventNotValid("Improper GET_N_NEW_POSTS_RESPONSE");
	  }
	  try{
		  status = e["status"].get<bool>();
		  data = e["data"].get<std::string>();
	  }
	  catch(...){
		  throw EventNotValid("Improper GET_N_NEW_POSTS_RESPONSE");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "GET_N_NEW_POSTS_RESPONSE";
	  e["status"] = status;
	  e["data"] = data;
	  return e;
  }
};

class GetAllUsersRequest
{
public:

  GetAllUsersRequest(){
  }

  explicit GetAllUsersRequest(Event e){
	  if(!checkEventKeys(e, {"type", "post_id"})) {
		  throw EventNotValid("Improper GET_ALL_USERS_REQUEST");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "GET_ALL_USERS_REQUEST";
	  return e;
  }
};

class GetAllUsersResponse
{
public:
  bool status;
  json data;

  GetAllUsersResponse(bool _status, json data){
	  status = _status;
	  this->data = data;
  }

  explicit GetAllUsersResponse(Event e){
	  if(!checkEventKeys(e, {"type", "status"})) {
		  throw EventNotValid("Improper GET_ALL_USERS_RESPONSE");
	  }
	  try{
		  status = e["status"].get<bool>();
		  data = e["data"].get<std::string>();
	  }
	  catch(...){
		  throw EventNotValid("Improper GET_ALL_USERS_RESPONSE");
	  }
  }

  operator Event(){
	  Event e;
	  e["type"] = "GET_ALL_USERS_RESPONSE";
	  e["status"] = status;
	  e["data"] = data;
	  return e;
  }
};

#endif //BEEPER_EVENT_H
