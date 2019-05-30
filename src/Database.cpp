//
// Created by hubertborkowski on 28.05.19.
//

#include <vector>
#include "Database.h"
#include "../database-objects/User.h"
#include "../database-objects/Post.h"

User* Database::storedUser = nullptr;
Post* Database::storedPost = nullptr;
std::vector<Post>* Database::storedPostVector = new std::vector<Post>();
std::vector<User>* Database::storedUserVector = new std::vector<User>();

static int make_user_callback(void *data, int nr_cols, char **field, char **colName)
{
	int id = std::stoi(field[0]);
	std::string username(field[1]);
	std::string alias(field[2]);
	std::string bio(field[3]);
	std::string password(field[4]);

	Database::storedUser = new User(id, username, alias, bio, password);

	return 0;
}

static int add_user_callback(void *data, int nr_cols, char **field, char **colName)
{
	int id = std::stoi(field[0]);
	std::string username(field[1]);
	std::string alias(field[2]);
	std::string bio(field[3]);
	std::string password(field[4]);

	Database::storedUserVector->push_back(User(id, username, alias, bio, password));

	return 0;
}

static int make_post_callback(void* data, int nr_cols, char** field, char** colName)
{
	int id = std::stoi(field[0]);
	int userId = std::stoi(field[1]);
	std::string content(field[2]);

	Database::storedPost = new Post(id, userId, content);

	return 0;
}

static int add_post_callback(void* data, int nr_cols, char** field, char** colName)
{
	int id = std::stoi(field[0]);
	int userId = std::stoi(field[1]);
	std::string content(field[2]);

	Database::storedPostVector->push_back(Post(id, userId, content));

	return 0;
}

void Database::openDB(std::string fileName)
{
	int failure = sqlite3_open(fileName.c_str(), &database);

	if(failure)
	{
		throw DatabaseException("Error while opening database: " + sqlite3_errcode(database));
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
		throw DatabaseException("Error while adding user: " + std::string(errorMsg));
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
		throw DatabaseException("Error while deleting user: " + std::string(errorMsg));
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
		throw DatabaseException("Error while changing alias: " + std::string(errorMsg));
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
		throw DatabaseException("Error while changing bio: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Bio changed successfully" << std::endl;
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
		throw DatabaseException("Error while adding post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
	}
}

User Database::getUserById(int id)
{
	char* errorMsg = nullptr;
	std::string query = "select * from users where id = " + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), make_user_callback, nullptr, &errorMsg);

	if(failure)
	{
		throw DatabaseException("Error while adding post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
		return *Database::storedUser;
	}
}

User Database::getUserByUsername(std::string username)
{
	char* errorMsg = nullptr;
	std::string query = "select * from users where username = '" + username + "';";

	int failure = sqlite3_exec(database, query.c_str(), make_user_callback, nullptr, &errorMsg);

	if(failure)
	{
		throw DatabaseException("Error while adding post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
		return *Database::storedUser;
	}
}

void Database::deletePost(int id)
{
	char* errorMsg = nullptr;
	std::string query = "delete from posts where id =" + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(failure)
	{
		throw DatabaseException("Error while deleting post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post deleted successfully" << std::endl;
	}
}

Post Database::getPostById(int id)
{
	char* errorMsg = nullptr;
	std::string query = "select * from posts where id = " + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), make_post_callback, nullptr, &errorMsg);

	if(failure)
	{
		throw DatabaseException("Error while adding post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
		return *Database::storedPost;
	}
}

std::vector<Post> Database::getPostsByUserId(int userId)
{
	char* errorMsg = nullptr;
	std::string query = "select * from posts where user_id = " + std::to_string(userId) + ";";

	int failure = sqlite3_exec(database, query.c_str(), add_post_callback, nullptr, &errorMsg);

	if(failure)
	{
		throw DatabaseException("Error while adding post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
		return *Database::storedPostVector;
	}
}

std::vector<User> Database::getLikesForPost(int postId)
{
	char* errorMsg = nullptr;
	std::string query = "select * from users inner join likes on likes.user_id = users.id "
			" where likes.post_id = " + std::to_string(postId) + ";";

	int failure = sqlite3_exec(database, query.c_str(), add_user_callback, nullptr, &errorMsg);

	if(failure)
	{
		throw DatabaseException("Error while adding post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
		return *Database::storedUserVector;
	}
}

std::vector<Post> Database::getLikedPostsForUser(int userId)
{
	char* errorMsg = nullptr;
	std::string query = "select * from posts inner join likes on likes.post_id = posts.id "
			"where likes.user_id = " + std::to_string(userId) + ";";

	int failure = sqlite3_exec(database, query.c_str(), add_post_callback, nullptr, &errorMsg);

	if(failure)
	{
		throw DatabaseException("Error while adding post: " + std::string(errorMsg));
	}
	else
	{
		std::cout << "Post added successfully" << std::endl;
		return *Database::storedPostVector;
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
