#pragma once
#include <string>

class IUser {
protected:
	std::string m_userName;
	char m_userType;

	//CTOR
	IUser(const std::string& userName, const char userType) :
		m_userName{ userName },
		m_userType{ userType } {

	}

public:
	//CTOR
	IUser() = default;

	//DTOR
	virtual ~IUser() = default;

	//SETTERS
	virtual void setUserName(const std::string& userName) {
		m_userName = userName;
	}
	virtual void setUserType(const char userType) {
		m_userType = userType;
	}

	//GETTERS
	virtual std::string getUserName() const {
		return m_userName;
	}
	virtual char getUserType() const {
		return m_userType;
	}

	//MISC
	virtual void cleanUserForDelete() = 0;

	virtual void displayUser() = 0 {
		std::cout << "UserName: " << m_userName << "\nUserType: ";

	}
	
};