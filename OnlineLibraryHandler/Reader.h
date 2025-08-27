#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "IUser.h"
#include "Book.h"
#include "BookStock.h"

class UserPool;

class Reader : public IUser {
protected:
	std::vector<std::weak_ptr<Book>> m_borrowedBooks; //To be refined
	int m_borrowedBookCount;

public:
	//CTOR
	Reader(const std::string& readerName);
	
	//DTOR
	~Reader() override = default;
	
	//SETTERS

	//GETTERS

	//MISC
	virtual void cleanUserForDelete() override;

		//book borrowing handle
	void borrowBook(const std::string& bookName, const BookStock& bookStock);
	void printBorrowedBooks() const;
	void giveBackBook(const std::string& book);

	void virtual displayUser() override;

	void selfModify() override;

};