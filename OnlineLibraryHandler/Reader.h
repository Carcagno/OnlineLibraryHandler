#pragma once

#include <memory>
#include <vector>

#include "IUser.h"
#include "Book.h"

class Reader : public IUser {
protected:
	std::vector<std::weak_ptr<Book>> m_borrowedBooks; //To be refined
	int m_borrowedBookCount;

public:
	//CTOR
	Reader(const std::string& readerName, const char readerType);
	
	//DTOR
	~Reader() override = default;
	
	//SETTERS

	//GETTERS

	//MISC
	virtual void cleanUserForDelete() override;
	void printBorrowedBooks() const;
	void giveBackBook(const std::string& book);
};