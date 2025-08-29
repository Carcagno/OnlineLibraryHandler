#pragma once

#include <iostream>

#include "IUser.h"
#include "Reader.h"
#include "UserPool.h"
#include "AuthorPool.h"
#include "Author.h"
#include "Utils.h"

class UserPool;

class Administrator : public IUser {
protected:

public:
	//CTOR
	Administrator(const std::string& AdministratorName, std::weak_ptr<BookStock> bookStock);

	//DTOR
	~Administrator() override = default;

	//SETTERS

	//GETTERS
	
	//MISC
	void cleanUserForDelete() override;
	
		//user handling
	void addUser(std::weak_ptr<UserPool> userPool);
	void deleteUser(std::weak_ptr<UserPool> userPool);
	void modifyUser(std::weak_ptr<UserPool> userPool);
	void displayUser() override;
	void showOtherUser(std::weak_ptr<UserPool> userPool, const std::string& userName);

		//author handling
	void modifyAuthor(std::weak_ptr<AuthorPool> authorPool);

		//book handling
	void modifyBook(std::weak_ptr<BookStock> bookStock, std::weak_ptr<AuthorPool> authorPool);

		//Self handling
	void selfModify() override;
 };