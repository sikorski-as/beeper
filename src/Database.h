//
// Created by hubertborkowski on 28.05.19.
//

#ifndef BEEPER_DATABASE_H
#define BEEPER_DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class Database
{
public:
  Database()  = default;

  ~Database()
  {
	  sqlite3_close(database);
  }

  void openDB(std::string fileName);

  void addUser(std::string userName, std::string alias, std::string bio);

  void deleteUser(int id);

  void changeUserAlias(std::string alias);

  void changeUserBio(std::string bio);

  void addPost(int userId, std::string content);
private:
  sqlite3* database;


};


#endif //BEEPER_DATABASE_H
