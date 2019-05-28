//
// Created by hubertborkowski on 28.05.19.
//

#include "Database.h"

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

void Database::addPost(int userId, std::string content)
{

}
