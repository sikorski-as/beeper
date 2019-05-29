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

  User() = default;

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

private:
  int id;
  std::string username;
  std::string alias;
  std::string bio;
  std::string password;
};


#endif //BEEPER_USER_H
