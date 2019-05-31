//
// Created by hubertborkowski on 28.05.19.
//

#ifndef BEEPER_USER_H
#define BEEPER_USER_H

#include <string>

class User
{
public:
  User(int id, std::string username, std::string alias, std::string bio, std::string password)
  {
	  this->id = id;
	  this->username = username;
	  this->alias = alias;
	  this->bio = bio;
	  this->password = password;
  }

  User(const User& other)
  {
	  this->id = other.id;
	  this->username = other.username;
	  this->alias = other.alias;
	  this->bio = other.bio;
	  this->password = other.password;
  }

  User(): username(), alias(), bio(), password()
  {
	  id = 0;
  }

  int getId() const
  {
	  return id;
  }

  void setId(int id)
  {
	  User::id = id;
  }

  const std::string& getUsername() const
  {
	  return username;
  }

  void setUsername(const std::string& username)
  {
	  User::username = username;
  }

  const std::string& getAlias() const
  {
	  return alias;
  }

  void setAlias(const std::string& alias)
  {
	  User::alias = alias;
  }

  const std::string& getBio() const
  {
	  return bio;
  }

  void setBio(const std::string& bio)
  {
	  User::bio = bio;
  }

  const std::string& getPassword() const
  {
	  return password;
  }

  void setPassword(const std::string& password)
  {
	  User::password = password;
  }

  bool isEmpty()
  {
	  return id == 0;
  }

private:
  int id;
  std::string username;
  std::string alias;
  std::string bio;
  std::string password;
};


#endif //BEEPER_USER_H
