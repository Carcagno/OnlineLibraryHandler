#pragma once
//to be refined

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "AuthorPool.h"

class BookStock {

private:
	std::vector<std::shared_ptr<Book>> m_books;
	std::string m_bookFilePath;

public:
	//CTOR
	BookStock(const std::string bookFilePath);
	
	//DTOR
	~BookStock();

	//MISC
		//Book basic handling
	void addBook(std::shared_ptr<Book> book);
	void deleteBook(const std::string& bookName);
	void modifyBook(const std::string& bookName, AuthorPool authorPool);

		//Book borrowing handling
	std::weak_ptr<Book> borrowBook(const std::string& bookName);
	void giveBackBook(std::weak_ptr<Book> bookWeak);

		//PRINTERS
	void printAllBooks() const;
	
	std::weak_ptr<Book> searchBook(const std::string& bookName) const;

	//to be refined - defined in .cpp
	/*std::weak_ptr<Book> borrowBook(const std::string& book) {
		if (bookSharedPtr->getIsBorrowed()) {
			//To be refined - Error Handling
			std::cerr << "The Book: " << bookSharedPtr->gitTitle() << " is already borrowed!" << std::endl;
			return std::weak_ptr<Book>();
		}
		bookSharedPtr->setIsBorrowed(true);
		return std::weak_ptr<Book>{bookSharedPtr};
	}*/
};