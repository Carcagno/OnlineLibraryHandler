#include "UserPool.h"

//to be refined - decide for each pool what method should return & error handling (in case of content not found, etc.)

UserPool::UserPool(const std::string& userFilePath): 
	m_userFilePath{ userFilePath } {

}

UserPool::~UserPool() {
	//to be refined - save intoFile
}

std::weak_ptr<IUser> UserPool::getUserFromPool(const std::string& userName) {
	for (auto it{ m_users.begin() }; it != m_users.end(); ++it) {
		if (it->get()->getUserName() == userName) {
			return *it;
		}
	}
}


void UserPool::addUser(std::shared_ptr<IUser> user) {
	m_users.push_back(user);
}

bool UserPool::deleteUser(const std::string& userName) {
	for (auto it{ m_users.begin() }; it != m_users.end(); ++it) {
		if (it->get()->getUserName() == userName) {
			m_users.erase(it);
			return true;
		}
	}

	std::cout << "Could'nt find user \"" << userName << "\" to delete. UserPool was left untouched." << std::endl;

	return false;
}

void UserPool::displayAllUsers() const {

	if (m_users.empty()) {
		std::cout << "The userPool is empty." << std::endl;
		return;
	}

	for (auto it{ m_users.begin() }; it != m_users.end(); ++it) {
		if (it->get()->getUserType() == 'A') {
			std::shared_ptr<Administrator> tmpA{ std::dynamic_pointer_cast<Administrator>(*it) };

			tmpA->displayUser();
		}
		else {
			std::shared_ptr<Reader> tmpR{ std::dynamic_pointer_cast<Reader>(*it) };

			tmpR->displayUser();
		}
	}
}
