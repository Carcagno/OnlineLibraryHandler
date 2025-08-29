#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "Author.h"
#include "AuthorPool.h"
#include "BookStock.h"

class Author;
class AuthorPool;
class BookStock;

class Book: public std::enable_shared_from_this<Book> {
public:
	enum bookCategory
	{
		SciFi,
		Classic,
		Autobiography,
		Roman,
		Fantasy,
		Thriller,
		Essay,
		defaultValue
	};

private:
	std::string m_title;
	std::weak_ptr<Author> m_author;
	bookCategory m_category;
	int m_publicationDate;
	bool m_isBorrowed;
	std::weak_ptr<BookStock> m_bookStock;


	//CTOR - private
	Book(const std::string& title, std::weak_ptr<Author> author, bookCategory category, int publicationDate, std::shared_ptr<BookStock> bookStock);

	//SETTERS - private
	void setTitle(const std::string& title);
	void setCategory(const bookCategory category);
	void setPublicationDate(const int publicationDate);

	//MISC - private
	void printCategory() const;


public:
	static std::shared_ptr<Book> create(const std::string& title, std::shared_ptr<Author>& author, bookCategory category, int publicationDate, std::shared_ptr<BookStock> bookStock);

	//DTOR
	~Book();

	//SETTERS
	void setAuthor(std::weak_ptr<Author> author);
	void setIsBorrowed(const bool isBorrowed);

	//GETTERS
	std::string getTitle() const;
	std::weak_ptr<Author> getAuthor() const;
	Book::bookCategory getCategory() const;
	int getPublicationDate() const;
	bool getIsBorrowed() const;

	//MISC
		//PRINTERS
	void printBook() const;
	static void printAllAvailableCategory();
		
		//Book handling
	void modifyBook(AuthorPool& authorPool);
	void resetAuthor();
	void deleteThisBookInAuthor();

};