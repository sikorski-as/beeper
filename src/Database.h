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

  void changeUserAlias(int id, std::string alias);

  void changeUserBio(int id, std::string bio);

  User getUserById(int id);

  User getUserByUsername(std::string username);

  void addPost(int userId, std::string content);

  void deletePost(int id);

  Post getPostById(int id);

  std::vector<Post> getPostsByUserId(int userId);

  std::vector<User> getLikesForPost(int postId);

  std::vector<Post> getLikedPostsForUser(int userId);

  static void setStoredUser(User* storedUser);

  static void setStoredUserVector(const std::vector<User>& storedUserVector);

  static void setStoredPost(const Post& storedPost);

  static void setStoredPostVector(const std::vector<Post>& storedPostVector);

  static User* storedUser;

  static std::vector<User>* storedUserVector;

  static Post* storedPost;

  static std::vector<Post>* storedPostVector;

private:
  sqlite3* database;


};


#endif //BEEPER_DATABASE_H
