#pragma once

#include <string>
#include <memory>
#include <vector>

#include "IUser.h"

class Book;
class BookStock;
class UserPool;
class AuthorPool;

class Reader : public IUser {
protected:
	std::vector<std::weak_ptr<Book>> m_borrowedBooks;
	int m_borrowedBookCount;

public:
	//CTOR
	Reader(const std::string& readerName, std::weak_ptr<BookStock> bookStock);
	
	//DTOR
	~Reader() override = default;
	
	//SETTERS

	//GETTERS

	//MISC
	virtual void cleanUserForDelete() override;

		//book borrowing handle
	bool borrowBook(const std::string& bookName);
	void printBorrowedBooks() const;
	bool giveBackBook(const std::string& bookTitle);

	void virtual displayUser() const override;

	bool selfModify(std::shared_ptr<UserPool> userPool, std::shared_ptr<BookStock> bookStock) override;
	bool selfExecute(std::shared_ptr<AuthorPool> authorPool, std::shared_ptr<BookStock> bookStock, std::shared_ptr<UserPool> userPool) override;

};