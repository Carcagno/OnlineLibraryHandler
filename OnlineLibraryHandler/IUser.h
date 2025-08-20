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
	virtual void setUserName(const std::string& userName);
	virtual void setUserType(const char c);

	//GETTERS
	virtual std::string getUserName() const;
	virtual char getUserType() const;

	//MISC
	virtual void cleanUserForDelete() = 0;

};