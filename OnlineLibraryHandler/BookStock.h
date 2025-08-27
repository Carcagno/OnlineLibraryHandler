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

	//GETTERS
	std::weak_ptr<Book> getBookFromStock(const std::string& bookName) const;

	//MISC
		//Book basic handling
	bool addBook(std::shared_ptr<Book> book);
	bool deleteBook(const std::string& bookName);
	bool modifyBook(const std::string& bookName, AuthorPool authorPool);

		//Book borrowing handling
	std::weak_ptr<Book> borrowBook(const std::string& bookName);
	bool giveBackBook(std::weak_ptr<Book> bookWeak);

		//PRINTERS
	void printAllBooks() const;
	bool isStockEmpty() const;

};