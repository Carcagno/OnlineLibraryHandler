#include "Author.h"

Author::Author(const std::string& authorName):
	m_authorName{ authorName } {

}

Author::~Author() {
	SetAllAuthorBooksToNone();
}


void Author::SetAllAuthorBooksToNone() {
	for (std::weak_ptr<Book> book : m_books) {
		std::shared_ptr<Book> bookShared{ book.lock()};

		if (bookShared) {
			bookShared->resetAuthor();
		}

	}
}

void Author::setAuthorName(const std::string& authorName) {

}

std::string Author::getAuthorName() const {
	return "placeholder";
}

void Author::printAuthor() {

}

bool Author::SetAuthorBookToNone(const std::string& book) {
	return false;
}

void Author::addBookToAuthor(const Book& book) {

}