#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "AuthorPool.h"
#include "Utils.h"

class Book;
class AuthorPool;

class Author {
private:
	std::string m_authorName;
	std::vector<std::weak_ptr<Book>> m_books;
	std::weak_ptr<AuthorPool> m_authorPool;

	//CTOR - Private
	Author(const std::string& authorName, std::shared_ptr<AuthorPool> authorPool);


	//UNINIT
	void SetAllAuthorBooksToNone();

public:

	static std::shared_ptr<Author> create(const std::string& authorName, std::shared_ptr<AuthorPool> authorPool);

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
	bool selfModify();
};