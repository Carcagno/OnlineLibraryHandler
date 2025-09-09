#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "Author.h"

class Author;

class AuthorPool {
private:
	std::vector<std::shared_ptr<Author>> m_authors;
	std::string m_authorsFilePath;

	//CTOR - Private
	AuthorPool(const std::string& authorFilePath);

public:	

	//CREATOR
	static std::shared_ptr<AuthorPool> create(const std::string& authorFilePath);

	//DTOR
	~AuthorPool();

	//GETTERS
	std::weak_ptr<Author> getAuthorFromPool(const std::string& authorName) const;

	//MISC
		//Author handling
	bool addAuthor(std::shared_ptr<Author> authorName);
	bool deleteAuthor(const std::string& authorName);
	bool modifyAuthor(const std::string& authorName);

	bool isEmpty() const;

	//PRINTERS
	void printAllAuthors() const;
	
	

};