//
// Created by hubertborkowski on 28.05.19.
//

#include <vector>
#include "Database.h"
#include "../database-objects/User.h"
#include "../database-objects/Post.h"

User* Database::storedUser = nullptr;
Post* Database::storedPost = nullptr;
std::vector<Post>* Database::storedPostVector = nullptr;
std::vector<User>* Database::storedUserVector = nullptr;

static int make_user_callback(void *data, int nr_cols, char **field, char **colName)
{
	int id = std::stoi(field[0]);
	std::string username(field[1]);
	std::string alias(field[2]);
	std::string bio(field[3]);

	Database::storedUser = new User(id, username, alias, bio);

	return 0;
}

void Database::openDB(std::string fileName)
{
	int success = sqlite3_open(fileName.c_str(), &database);

	if(success)
	{
		std::cout << "Database opened" << std::endl;
	}
	else
	{
		std::cout << "Error while opening database: " + sqlite3_errcode(database) << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Database::addUser(std::string userName, std::string alias, std::string bio)
{
	char* errorMsg = nullptr;
	std::string query = "insert into users (username, alias, bio) values (" +
						userName + "," + alias + "," + bio + ");";

	int success = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(success)
	{
		std::cout << "User added successfully" << std::endl;
	}
	else
	{
		std::cout << "Error while adding user: " + std::string(errorMsg) << std::endl;
		sqlite3_free(errorMsg);
	}
}

void Database::deleteUser(int id)
{
	char* errorMsg = nullptr;
	std::string query = "delete from users where id =" + std::to_string(id) + ";";

	int success = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(success)
	{
		std::cout << "User deleted successfully" << std::endl;
	}
	else
	{
		std::cout << "Error while deleting user: " + std::string(errorMsg) << std::endl;
		sqlite3_free(errorMsg);
	}
}

void Database::changeUserAlias(int id, std::string alias)
{
	char* errorMsg = nullptr;
	std::string query = "update user set alias = " + alias + " where id = " + std::to_string(id) + " ;";

	int success = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(success)
	{
		std::cout << "Alias changed successfully" << std::endl;
	}
	else
	{
		std::cout << "Error while changing alias: " + std::string(errorMsg) << std::endl;
		sqlite3_free(errorMsg);
	}
}

void Database::changeUserBio(int id, std::string bio)
{
	char* errorMsg = nullptr;
	std::string query = "update user set bio = " + bio + " where id = " + std::to_string(id) + " ;";

	int success = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(success)
	{
		std::cout << "Bio changed successfully" << std::endl;
	}
	else
	{
		std::cout << "Error while changing bio: " + std::string(errorMsg) << std::endl;
		sqlite3_free(errorMsg);
	}
}

void Database::addPost(int userId, std::string content)
{
	char* errorMsg = nullptr;
	std::string query = "insert into posts (user_id, content) values (" +
						std::to_string(userId) + "," + content + ");";

	int success = sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errorMsg);

	if(success)
	{
		std::cout << "Post added successfully" << std::endl;
	}
	else
	{
		std::cout << "Error while adding post: " + std::string(errorMsg) << std::endl;
		sqlite3_free(errorMsg);
	}
}

User Database::getUserById(int id)
{
	char* errorMsg = nullptr;
	std::string query = "select * from users where id = " + std::to_string(id) + ";";

	int success = sqlite3_exec(database, query.c_str(), make_user_callback, nullptr, &errorMsg);

	if(success)
	{
		std::cout << "Post added successfully" << std::endl;
		return *Database::storedUser;
	}
	else
	{
		std::cout << "Error while adding post: " + std::string(errorMsg) << std::endl;
		sqlite3_free(errorMsg);
	}
}

User Database::getUserByUsername(std::string username)
{

}

void Database::deletePost(int id)
{

}

Post Database::getPostById(int id)
{

}

std::vector<Post> Database::getPostsByUserId(int userId)
{

}

std::vector<User> Database::getLikesForPost(int postId)
{

}

std::vector<Post> Database::getLikedPostsForUser(int userId)
{

}

//void Database::setStoredUser(User* storedUser)
//{
//	Database::storedUser = storedUser;
//}
//
//void Database::setStoredUserVector(const std::vector<User>& storedUserVector)
//{
//	Database::storedUserVector = storedUserVector;
//}
//
//void Database::setStoredPost(const Post& storedPost)
//{
//	Database::storedPost = storedPost;
//}
//
//void Database::setStoredPostVector(const std::vector<Post>& storedPostVector)
//{
//	Database::storedPostVector = storedPostVector;
//}

