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

	void SetAllAuthorBooksToNone();

public:
	Author(const std::string& authorName);
	~Author();


	void setAuthorName(const std::string& authorName);

	std::string getAuthorName() const;

	void printAuthor();

	bool SetAuthorBookToNone(const std::string& book);

	void addBookToAuthor(const Book& book);
};