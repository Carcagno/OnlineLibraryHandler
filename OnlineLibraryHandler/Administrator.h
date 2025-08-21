#pragma once

#include <iostream>

#include "IUser.h"
#include "Reader.h"
#include "UserPool.h"

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
	void showUser(UserPool& userPool);

		//author handling
	void addAuthor();
	void deleteAuthor();
	void modifyAuthor();

		//book handling
	void addBook();
	void deleteBook();
	void modifyBook();

 };