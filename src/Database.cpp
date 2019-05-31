//
// Created by hubertborkowski on 28.05.19.
//

#include <vector>
#include "Database.h"
#include "../database-objects/User.h"
#include "../database-objects/Post.h"

static int make_user_callback(void *data, int nr_cols, char **field, char **colName)
{
	User* result = static_cast<User*>(data);
	try
	{
		int id = std::stoi(field[0]);
		std::string username(field[1]);
		std::string alias;
		if (field[2] != nullptr)
			alias = std::string(field[2]);
		std::string bio;
		if (field[3] != nullptr)
			bio = std::string(field[3]);
		std::string password(field[4]);

		result->setId(id);
		result->setUsername(username);
		result->setAlias(alias);
		result->setBio(bio);
		result->setPassword(password);
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}

static int add_user_callback(void *data, int nr_cols, char **field, char **colName)
{
	std::vector<User>* result = static_cast<std::vector<User>*>(data);

	try
	{
		int id = std::stoi(field[0]);
		std::string username(field[1]);
		std::string alias;
		if(field[2] != nullptr)
			alias = std::string(field[2]);
		std::string bio;
		if(field[3] != nullptr)
			bio = std::string(field[3]);
		std::string password(field[4]);

		result->push_back(User(id, username, alias, bio, password));
		std::cout << id << " " << username << std::endl;
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}

static int make_post_callback(void* data, int nr_cols, char** field, char** colName)
{
	Post* result = static_cast<Post*>(data);

	try
	{
		int id = std::stoi(field[0]);
		int userId = std::stoi(field[1]);
		std::string content;
		if (field[2] != nullptr)
			content = std::string(field[2]);

		result->setId(id);
		result->setUserId(userId);
		result->setContent(content);
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}

static int add_post_callback(void* data, int nr_cols, char** field, char** colName)
{
	std::vector<Post>* result = static_cast<std::vector<Post>*>(data);

	int id = std::stoi(field[0]);
	int userId = std::stoi(field[1]);
	std::string content;
	if(field[2] != nullptr)
		content = std::string(field[2]);

	result->push_back(Post(id, userId, content));

	return 0;
}

void Database::openDB(std::string fileName)
{
	int failure = sqlite3_open_v2(fileName.c_str(), &database, SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE, nullptr);

	if(failure)
	{
		throw DatabaseException("SQLite error while opening database: " + std::to_string(sqlite3_errcode(database)));
	}
	else
	{
		std::cout << "Database opened" << std::endl;
	}
}

void Database::addUser(std::string userName, std::string alias, std::string bio, std::string password)
{
	char* errorMsg = nullptr;
	std::string query = "insert into users (username, alias, bio, password) values ('" +
						userName + "','" + alias + "','" + bio + "','" + password + "');";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while adding user: " + error);
	}
	else
	{
		std::cout << "User added successfully" << std::endl;
	}
}

void Database::deleteUser(int id)
{
	char* errorMsg = nullptr;
	std::string query = "delete from users where id =" + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while deleting user: " + error);
	}
	else
	{
		std::cout << "User deleted successfully" << std::endl;
	}
}

void Database::changeUserAlias(int id, std::string alias)
{
	char* errorMsg = nullptr;
	std::string query = "update user set alias = '" + alias + "' where id = " + std::to_string(id) + " ;";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while changing alias: " + error);
	}
	else
	{
		std::cout << "Alias changed successfully" << std::endl;
	}
}

void Database::changeUserBio(int id, std::string bio)
{
	char* errorMsg = nullptr;
	std::string query = "update user set bio = '" + bio + "' where id = " + std::to_string(id) + " ;";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while changing bio: " + error);
	}
	else
	{
		std::cout << "Bio changed successfully" << std::endl;
	}
}

std::vector<User> Database::getAllUsers()
{
	char* errorMsg = nullptr;
	std::vector<User> result;
	std::string query = "select * from users;";

	int retval = sqlite3_exec(database, query.c_str(), add_user_callback, &result, &errorMsg);

	if(retval != SQLITE_OK)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting all users: " + error);
	}
	else
	{
		return result;
	}
}

void Database::addPost(int userId, std::string content)
{
	char* errorMsg = nullptr;
	std::string query = "insert into posts (user_id, content) values (" +
						std::to_string(userId) + ",'" + content + "');";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while adding post: " + error);
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
	}
}

void Database::likePost(int userId, int postId)
{
	char* errorMsg = nullptr;
	std::string query = "insert into likes (user_id, post_id) values (" +
						std::to_string(userId) + ",'" + std::to_string(postId) + "');";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while adding like: " + error);
	}
	else
	{
		std::cout << "Post liked successfully" << std::endl;
	}
}

User Database::getUserById(int id)
{
	char* errorMsg = nullptr;
	User result;
	std::string query = "select * from users where id = " + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), make_user_callback, &result, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting user by id: " + error);
	}
	else if(result.isEmpty())
	{
		throw DatabaseException("User not found");
	}
	else
	{
		std::cout << "User got successfully" << std::endl;
		return result;
	}
}

User Database::getUserByUsername(std::string username)
{
	char* errorMsg = nullptr;
	User result;
	std::string query = "select * from users where username = '" + username + "';";

	int failure = sqlite3_exec(database, query.c_str(), make_user_callback, &result, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting user by username: " + error);
	}
	else if(result.isEmpty())
	{
		throw DatabaseException("User not found");
	}
	else
	{
		std::cout << "Got user successfully" << std::endl;
		return result;
	}
}

void Database::deletePost(int id)
{
	char* errorMsg = nullptr;
	std::string query = "delete from posts where id =" + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while deleting post: " + error);
	}
	else
	{
		std::cout << "Post deleted successfully" << std::endl;
	}
}

std::vector<Post> Database::getNNewestPosts(int n)
{
	char* errorMsg = nullptr;
	std::vector<Post> result;
	std::string query = "select * from (select * from posts order by id desc limit " + std::to_string(n)
						+ " ) order by id asc;";

	int retval = sqlite3_exec(database, query.c_str(), add_post_callback, &result, &errorMsg);

	if(retval != SQLITE_OK)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting n newest posts: " + error);
	}
	else
	{
		return result;
	}
}

Post Database::getPostById(int id)
{
	char* errorMsg = nullptr;
	Post result;
	std::string query = "select * from posts where id = " + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), make_post_callback, &result, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting post by id: " + error);
	}
	else if(result.isEmpty())
	{
		throw DatabaseException("Post not found");
	}
	else
	{
		std::cout << "Post got successfully" << std::endl;
		return result;
	}
}

std::vector<Post> Database::getPostsByUserId(int userId)
{
	char* errorMsg = nullptr;
	std::vector<Post> result;
	std::string query = "select * from posts where user_id = " + std::to_string(userId) + ";";

	int retval = sqlite3_exec(database, query.c_str(), add_post_callback, &result, &errorMsg);

	if(retval != SQLITE_OK)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting posts by user id: " + error);
	}
	else
	{
		return result;
	}
}

std::vector<User> Database::getLikesForPost(int postId)
{
	char* errorMsg = nullptr;
	std::vector<User> result;
	std::string query = "select * from users inner join likes on likes.user_id = users.id "
			" where likes.post_id = " + std::to_string(postId) + ";";

	int retval = sqlite3_exec(database, query.c_str(), add_user_callback, &result, &errorMsg);

	if(retval != SQLITE_OK)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting likes for post: " + error);
	}
	else
	{
		return result;
	}
}

std::vector<Post> Database::getLikedPostsForUser(int userId)
{
	char* errorMsg = nullptr;
	std::vector<Post> result;
	std::string query = "select * from posts inner join likes on likes.post_id = posts.id "
			"where likes.user_id = " + std::to_string(userId) + ";";

	int retval = sqlite3_exec(database, query.c_str(), add_post_callback, &result, &errorMsg);

	if(retval != SQLITE_OK)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting liked posts for user: " + error);
	}
	else
	{
		return result;
	}
}

bool Database::containsForbiddenChars(std::string text)
{
	if(text.find('\'') == std::string::npos && text.find(';') == std::string::npos && text.find('-') == std::string::npos)
	{
		return false;
	}
	else
	{
		return true;
	}
}
