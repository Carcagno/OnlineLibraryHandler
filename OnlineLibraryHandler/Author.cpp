#include "Author.h"

Author::Author(const std::string& authorName):
	m_authorName{ authorName } {

}

Author::~Author() {
	SetAllAuthorBooksToNone();
	//to be refined - delete author in authorPool
}


void Author::SetAllAuthorBooksToNone() {
	for (std::weak_ptr<Book> book : m_books) {
		std::shared_ptr<Book> bookShared{ book.lock()};

		if (bookShared) {
			bookShared->resetAuthor();
		}
		else {
			// to be refined - exception handling
		}

	}
}

void Author::setAuthorName(const std::string& authorName) {
	if (authorName != "") {
		m_authorName = authorName;
	}
}

std::string Author::getAuthorName() const {
	return m_authorName;
}

void Author::printAuthor() const{
	std::cout << "\t\t\t==================== " << m_authorName << " ====================" << std::endl;
	//If any informations is added into author, can be updated to be prompt.
}

bool Author::deleteBookFromAuthor(const std::string& bookTitle) {

	for (auto it{ m_books.begin() }; it != m_books.end(); ++it) {
		std::shared_ptr<Book> book{ it->lock() };

		if (book) {
			if (book->getTitle() == bookTitle) {
				m_books.erase(it);
				return true;
			}
			else {
				// to be refined - exception handling book not found
			}
		}
		else {
			// to be refined - exception handling
		}
	}
	return false;
}

void Author::addBookToAuthor(std::weak_ptr<Book> book) {
	m_books.push_back(book);
}