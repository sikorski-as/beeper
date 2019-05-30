//
// Created by hubertborkowski on 28.05.19.
//

#ifndef BEEPER_DATABASE_H
#define BEEPER_DATABASE_H

#include "sqlite3.h"
#include "../database-objects/User.h"
#include "../database-objects/Post.h"
#include <string>
#include <iostream>
#include <vector>

class DatabaseException: public std::exception
{
public:
  std::string reason;

  explicit DatabaseException(std::string reason): reason(reason) {}

  virtual const char* what()
  {
	  return reason.c_str();
  }
};

class Database
{
public:
  Database()  = default;

  ~Database()
  {
	  sqlite3_close(database);
  }

  void openDB(std::string fileName);

  void closeDB() {sqlite3_close(database);}

  void addUser(std::string userName, std::string alias, std::string bio, std::string password);

  void deleteUser(int id);

  void changeUserAlias(int id, std::string alias);

  void changeUserBio(int id, std::string bio);

  User getUserById(int id);

  User getUserByUsername(std::string username);

  std::vector<User> getAllUsers();

  void addPost(int userId, std::string content);

  void likePost(int userId, int postId);

  void deletePost(int id);

  Post getPostById(int id);

  std::vector<Post> getNNewestPosts(int n);

  std::vector<Post> getPostsByUserId(int userId);

  std::vector<User> getLikesForPost(int postId);

  std::vector<Post> getLikedPostsForUser(int userId);

  static User* storedUser;

  static std::vector<User>* storedUserVector;

  static Post* storedPost;

  static std::vector<Post>* storedPostVector;

  static bool containsForbiddenChars(std::string);

private:
  sqlite3* database;
};


#endif //BEEPER_DATABASE_H
