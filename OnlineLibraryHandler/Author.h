#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
class Book;

class Author {
private:
	std::string m_authorName;
	std::vector<std::weak_ptr<Book>> m_books;

	//UNINIT
	void SetAllAuthorBooksToNone();

public:
	//CTOR
	Author(const std::string& authorName);
	//DTOR
	~Author();

	//SETTERS
	void setAuthorName(const std::string& authorName);

	//GETTERS
	std::string getAuthorName() const;

	//MISC
		//PRINTERS
	void printAuthor() const;

		//Author's books handler
	bool deleteBookFromAuthor(const std::string& bookTitle);
	void addBookToAuthor(std::weak_ptr<Book> book);
};