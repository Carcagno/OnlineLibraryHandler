#pragma once

#include <memory>
#include <string>

#include "Author.h"

class Author;

class AuthorPool {
	//to be refined - implement class
private:

public:	
	AuthorPool();


	std::weak_ptr<Author> getAuthorFromPool(const std::string& authorName) const {
		 
		return std::weak_ptr<Author>{};
	}

};