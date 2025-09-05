#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cctype>

class BookStock;
class UserPool;
class AuthorPool;

//To be refined
//In case of evolution & growing, it could be interesting to cut IUser with other interfaces like IDisplayable, IExecutable, IData, to avoid monolithic architecture.
//It could also be interesting to have a IContext interface, to avoid the concrete dependance to BookStock, UserPool & AuthorPool

class IUser {
public: 
// Using an enum class to avoid to have a char where any userType can be used
	enum class UserType : char {
		Reader = 'R',
		Administrator = 'A'
	};
protected:


	std::string m_userName;
	std::weak_ptr<BookStock> m_bookStock;
	UserType m_userType;

//CTOR & DTOR protected, to allow only inherited classes to invoke

	//CTOR
	IUser(const std::string& userName, const IUser::UserType userType, std::weak_ptr<BookStock> bookStock) :
		m_userName{ userName },
		m_userType{ userType },
		m_bookStock{ bookStock } {

	}

	//DTOR
	virtual ~IUser() = default;

public:

	//CTOR - Delete
	IUser() = delete;

// deleting to avoid object slicing
	//CTOR CPY - delete
	IUser(const IUser&) = delete;
	IUser& operator=(const IUser&) = delete;
	IUser(IUser&&) = delete; //&& rvalue ref, ex: temporary objects.
	IUser& operator=(IUser&&) = delete;

	//SETTERS
	virtual void setUserName(const std::string& userName) {

		if (userName.empty() || std::all_of(userName.begin(), userName.end(), 
			[](char c) {
				return std::isspace(static_cast<unsigned char>(c)); //convert into unsigned char because isspace needs an unsigned char, AFAIK in the doc.
			})) {
			std::cerr << "The username cannot be empty or whitespace only." << std::endl;
			return;
		}

		m_userName = userName;
	}
	virtual void setUserType(const IUser::UserType userType) {
		m_userType = userType;
	}

	//GETTERS
	virtual const std::string& getUserName() const {
		return m_userName;
	}
	virtual UserType getUserType() const {
		return m_userType;
	}

	//MISC
	virtual void cleanUserForDelete() = 0;

	virtual void displayUser() const {
		std::cout << "UserName: " << m_userName << "\nUserType: ";

	}

	virtual bool selfModify(std::shared_ptr<UserPool> userPool, std::shared_ptr<BookStock> bookStock) = 0;

	virtual bool selfExecute(std::shared_ptr<AuthorPool> authorPool, std::shared_ptr<BookStock> bookStock, std::shared_ptr<UserPool> userPool) = 0;
	
};