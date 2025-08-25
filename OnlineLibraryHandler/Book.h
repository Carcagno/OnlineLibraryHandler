#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "Author.h"
#include "AuthorPool.h"

class Author;
class AuthorPool;

//to be refined
class Book {
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

	void setTitle(const std::string& title);
	void setCategory(const bookCategory category);
	void setPublicationDate(const int publicationDate);
	void setIsBorrowed(const bool isBorrowed);

	void deleteThisBookInAuthor();
	void printCategory() const;


public:
	Book(const std::string& title, std::weak_ptr<Author> author, bookCategory category, int publicationDate);
	~Book();

	void setAuthor(std::weak_ptr<Author> author);

	std::string getTitle() const;
	std::weak_ptr<Author> getAuthor() const;
	Book::bookCategory getCategory() const;
	int getPublicationDate() const;
	bool getIsBorrowed() const;

	void printBook() const;
	void printAllAvailableCategory();
	void modifyBook(AuthorPool& authorPool);

	void resetAuthor();


};