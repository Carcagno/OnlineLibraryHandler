#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "IUser.h"
#include "Administrator.h"
#include "Reader.h"

class IUser;

class UserPool {
private:
	std::vector<std::shared_ptr<IUser>> m_users;
	std::string m_userFilePath;

public:
	//CTOR
	UserPool(const std::string& userFilePath);

	//DTOR
	~UserPool();

	//GETTERS
	std::weak_ptr<IUser> getUserFromPool(const std::string& userName);

	//MISC
		//User handling
	bool addUser(std::shared_ptr<IUser> user);
	bool deleteUser(const std::string& userName);

	bool isEmpty() const;
	
	//PRINTERS
	void displayAllUsers() const;
	
};