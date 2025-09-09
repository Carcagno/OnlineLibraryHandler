#pragma once

#include <string>
#include <memory>

#include "IUser.h"

class Reader;
class Author;
class UserPool;
class AuthorPool;
class BookStock;

class Administrator : public IUser {
public:
	//CTOR
	explicit Administrator(const std::string& AdministratorName, std::weak_ptr<BookStock> bookStock);

	//DTOR
	~Administrator() override = default;

	//SETTERS

	//GETTERS
	
	//MISC
	void cleanUserForDelete() override;
	
		//user handling
	bool addUser(std::shared_ptr<UserPool> userPool);
	bool deleteUser(std::shared_ptr<UserPool> userPool);
	bool modifyUser(std::shared_ptr<UserPool> userPool);
	void displayUser() const override;
	void showOtherUser(std::shared_ptr<UserPool> userPool);

		//author handling
	bool addAuthor(std::shared_ptr<AuthorPool> authorPool);
	bool deleteAuthor(std::shared_ptr<AuthorPool> authorPool);
	bool modifyAuthor(std::shared_ptr<AuthorPool> authorPool);

		//book handling
	bool addBook(std::shared_ptr<BookStock> bookStock, std::shared_ptr<AuthorPool> authorPool);
	bool deleteBook(std::shared_ptr<BookStock> bookStock);
	bool modifyBook(std::shared_ptr<BookStock> bookStock, std::shared_ptr<AuthorPool> authorPool);

		//Self handling
	bool selfModify(std::shared_ptr<UserPool> userPool, std::shared_ptr<BookStock> bookStock) override;
	bool selfExecute(std::shared_ptr<AuthorPool> authorPool, std::shared_ptr<BookStock> bookStock, std::shared_ptr<UserPool> userPool) override;

 };