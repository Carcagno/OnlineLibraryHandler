#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "IUser.h"
#include "Administrator.h"
#include "Reader.h"

class UserPool {
private:
	std::vector<std::shared_ptr<IUser>> m_users;
	std::string m_userFilePath;

public:
	UserPool(const std::string& userFilePath);
	~UserPool();

	std::weak_ptr<IUser> getUserFromPool(const std::string& userName);

	void addUser(std::shared_ptr<IUser> user);
	bool deleteUser(const std::string& userName);
	
	void displayUsers(const std::string& userName) const;
	void displayAllUsers() const;
	
};