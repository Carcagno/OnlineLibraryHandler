#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "IUser.h"
#include "Book.h"
#include "BookStock.h"

class UserPool;
class BookStock;

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
	bool giveBackBook(const std::string& book);

	void virtual displayUser() override;

	bool selfModify() override;

};