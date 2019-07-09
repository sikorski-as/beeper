//
// Created by hubertborkowski on 28.05.19.
//

#ifndef BEEPER_POST_H
#define BEEPER_POST_H

#include <string>

class Post
{
public:
  Post(int id, int userId, const std::string& content) : id(id), userId(userId), content(content)
  {}

  Post(): userId(), content()
  {
	  id = 0;
  }

  int getId() const
  {
	  return id;
  }

  void setId(int id)
  {
	  Post::id = id;
  }

  int getUserId() const
  {
	  return userId;
  }

  void setUserId(int userId)
  {
	  Post::userId = userId;
  }

  const std::string& getContent() const
  {
	  return content;
  }

  void setContent(const std::string& content)
  {
	  Post::content = content;
  }

  bool isEmpty()
  {
	  return id == 0;
  }

private:
  int id;
  int userId;
  std::string content;
};


#endif //BEEPER_POST_H
