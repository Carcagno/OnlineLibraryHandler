#pragma once

#include <vector>
#include <string>
#include <memory>

#include "IUser.h"

class UserPool {
private:
	std::vector<std::shared_ptr<IUser>> m_users;
	std::string m_userFilePath;

public:
	UserPool();
};