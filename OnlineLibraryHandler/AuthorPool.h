#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "Author.h"

class Author;

class AuthorPool {
	//to be refined - implement class
private:
	std::vector<std::shared_ptr<Author>> m_authors;
	std::string m_authorsFilePath;

public:	
	AuthorPool(const std::string& authorFilePath);
	~AuthorPool();

	void addAuthor(std::shared_ptr<Author> authorName);
	void deleteAuthor(const std::string& authorName);
	void modifyAuthor(const std::string& authorName);

	void printAllAuthors() const;
	std::weak_ptr<Author> getAuthorFromPool(const std::string& authorName);

};