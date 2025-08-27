#pragma once

#include <iostream>

#include "IUser.h"
#include "Reader.h"
#include "UserPool.h"
#include "AuthorPool.h"
#include "Author.h"

class UserPool;

class Administrator : public IUser {
protected:

public:
	//CTOR
	Administrator(const std::string& AdministratorName);

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
	void showUser(const UserPool& userPool);

		//author handling
	void addAuthor(AuthorPool& authorPool);
	void deleteAuthor(AuthorPool& authorPool);
	void modifyAuthor(AuthorPool& authorPool);

		//book handling
	void addBook(BookStock& bookStock, AuthorPool& authorPool);
	void deleteBook(BookStock& bookStock);
	void modifyBook(BookStock& bookStock);

		//Self handling
	void selfModify() override;
 };