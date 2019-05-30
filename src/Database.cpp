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
	std::string query = "select * from users;";

	int failure = sqlite3_exec(database, query.c_str(), add_user_callback, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting users: " + error);
	}
	else if(Database::storedUserVector->empty())
	{
		throw DatabaseException("No users found");
	}
	else
	{
		std::cout << "Users got successfully" << std::endl;
		std::vector<User>* temp = Database::storedUserVector;
		Database::storedUserVector->clear();
		return *temp;
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
	std::string query = "select * from users where id = " + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), make_user_callback, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting user by id: " + error);
	}
	else if(Database::storedUser == nullptr)
	{
		throw DatabaseException("User not found");
	}
	else
	{
		std::cout << "User got successfully" << std::endl;
		User* temp = Database::storedUser;
		Database::storedUser = nullptr;
		return *temp;
	}
}

User Database::getUserByUsername(std::string username)
{
	char* errorMsg = nullptr;
	std::string query = "select * from users where username = '" + username + "';";

	int failure = sqlite3_exec(database, query.c_str(), make_user_callback, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting user by username: " + error);
	}
	else if(Database::storedUser == nullptr)
	{
		throw DatabaseException("User not found");
	}
	else
	{
		std::cout << "Got user successfully" << std::endl;
		User* temp = Database::storedUser;
		Database::storedUser = nullptr;
		return *temp;
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
	std::string query = "select * from (select * from posts order by posts.id desc limit " + std::to_string(n)
						+ " ) order by posts.id asc;";

	int failure = sqlite3_exec(database, query.c_str(), add_post_callback, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting n posts: " + error);
	}
	else if(Database::storedPostVector->empty())
	{
		throw DatabaseException("No posts found");
	}
	else
	{
		std::cout << "Posts got successfully" << std::endl;
		std::vector<Post>* temp = Database::storedPostVector;
		Database::storedPostVector = new std::vector<Post>();
		return *temp;
	}
}

Post Database::getPostById(int id)
{
	char* errorMsg = nullptr;
	std::string query = "select * from posts where id = " + std::to_string(id) + ";";

	int failure = sqlite3_exec(database, query.c_str(), make_post_callback, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting post by id: " + error);
	}
	else if(Database::storedPost == nullptr)
	{
		throw DatabaseException("Post not found");
	}
	else
	{
		std::cout << "Post got successfully" << std::endl;
		Post* temp = Database::storedPost;
		Database::storedPost = nullptr;
		return *temp;
	}
}

std::vector<Post> Database::getPostsByUserId(int userId)
{
	char* errorMsg = nullptr;
	std::string query = "select * from posts where user_id = " + std::to_string(userId) + ";";

	int failure = sqlite3_exec(database, query.c_str(), add_post_callback, nullptr, &errorMsg);

	if(failure)
	{
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting post by user_id: " + error);
	}
	else if(Database::storedPostVector->empty())
	{
		throw DatabaseException("Posts not found");
	}
	else
	{
		std::cout << "Posts got successfully" << std::endl;
		std::vector<Post>* temp = Database::storedPostVector;
		Database::storedPostVector = new std::vector<Post>();
		return *temp;
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
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting like for post: " + error);
	}
	else if(Database::storedUserVector->empty())
	{
		throw DatabaseException("Likes not found");
	}
	else
	{
		std::cout << "Likes got successfully" << std::endl;
		std::vector<User>* temp = Database::storedUserVector;
		Database::storedUserVector = new std::vector<User>;
		return *temp;
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
		std::string error(errorMsg);
		sqlite3_free(errorMsg);
		throw DatabaseException("Error while getting liked posts for user: " + error);
	}
	else if(Database::storedPostVector->empty())
	{
		throw DatabaseException("Liked posts not found");
	}
	else
	{
		std::cout << "Liked posts got successfully" << std::endl;
		std::vector<Post>* temp = Database::storedPostVector;
		Database::storedPostVector = new std::vector<Post>();
		return *temp;
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
