#pragma once

#include <iostream>
#include <algorithm>

#include "IUser.h"
#include "Reader.h"
#include "Author.h"
#include "Utils.h"

#include "BookStock.h"
#include "UserPool.h"
#include "AuthorPool.h"

class IUser;
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
	bool addUser(std::weak_ptr<UserPool> userPool);
	bool deleteUser(std::weak_ptr<UserPool> userPool);
	bool modifyUser(std::weak_ptr<UserPool> userPool);
	void displayUser() override;
	void showOtherUser(std::weak_ptr<UserPool> userPool);

		//author handling
	bool addAuthor(std::weak_ptr<AuthorPool> authorPool);
	bool deleteAuthor(std::weak_ptr<AuthorPool> authorPool);
	bool modifyAuthor(std::weak_ptr<AuthorPool> authorPool);

		//book handling
	bool addBook(std::weak_ptr<BookStock> bookStock, std::weak_ptr<AuthorPool> authorPool);
	bool deleteBook(std::weak_ptr<BookStock> bookStock);
	bool modifyBook(std::weak_ptr<BookStock> bookStock, std::weak_ptr<AuthorPool> authorPool);

		//Self handling
	bool selfModify() override;
	bool selfExecute(std::shared_ptr<AuthorPool> authorPool, std::shared_ptr<BookStock> bookStock, std::shared_ptr<UserPool> userPool) override;

 };