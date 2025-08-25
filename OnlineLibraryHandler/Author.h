#pragma once

class Author {
public:
	
	std::string getAuthorName();
	void printAuthor();
	bool deleteAuthorBook(const std::string& book);
};