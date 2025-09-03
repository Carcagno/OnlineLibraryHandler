#pragma once
#include <string>

#include "bookStock.h"

class BookStock;

class IUser {
protected:
	std::string m_userName;
	char m_userType;
	std::weak_ptr<BookStock> m_bookStock;

	//CTOR
	IUser(const std::string& userName, const char userType, std::weak_ptr<BookStock> bookStock) :
		m_userName{ userName },
		m_userType{ userType },
		m_bookStock{ bookStock } {

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

	virtual bool selfModify() = 0;
	
};