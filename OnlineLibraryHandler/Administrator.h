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
	void addUser(UserPool& userPool);
	void deleteUser(UserPool& userPool);
	void modifyUser(UserPool& userPool);
	void displayUser() override;
	void showOtherUser(UserPool& userPool, const std::string& userName);

		//author handling
	void modifyAuthor(AuthorPool& authorPool);

		//book handling
	void modifyBook(BookStock& bookStock, AuthorPool& authorPool);

		//Self handling
	void selfModify() override;
 };