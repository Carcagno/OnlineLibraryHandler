#include "BookStock.h"

//CTOR 
BookStock::BookStock(const std::string& bookFilePath):
	m_bookFilePath{bookFilePath} {

}

//DTOR
BookStock::~BookStock() {

}

//GETTERS
std::weak_ptr<Book> BookStock::getBookFromStock(const std::string& bookName) const {
	for (auto it{ m_books.begin() }; it != m_books.end(); ++it) {
		if (it->get()->getTitle() == bookName) {
			return (*it);
		}
	}

	return std::weak_ptr<Book>{};
}

//MISC
	//Book basic handling
bool BookStock::addBook(std::shared_ptr<Book> book) {
	if (book) {
		m_books.push_back(book);
		return true;
	}
	std::cerr << "Cannot add empty Book. BookStock was left untouched." << std::endl;
	return false;
}

bool BookStock::deleteBook(const std::string& bookName) { 
	for (auto it{ m_books.begin() }; it != m_books.end(); ++it) {
		if (it->get()->getTitle() == bookName) {
			it->get()->deleteThisBookInAuthor();
			m_books.erase(it);
			return true;
		}
	}
	std::cerr << "Could'nt find any Book \"" << bookName << "\" to delete. BookStock was left untouched." << std::endl;
	return false;
}

bool BookStock::modifyBook(const std::string& bookName, std::weak_ptr<AuthorPool> authorPool) {
	for (auto it{ m_books.begin() }; it != m_books.end(); ++it) {
		if (it->get()->getTitle() == bookName) {
				it->get()->modifyBook(authorPool);
				return true;			
		}
	}
	std::cerr << "Could'nt find any Book \"" << bookName << "\" to modify. BookStock was left untouched." << std::endl;
	return false;
}

//Book borrowing handling
std::weak_ptr<Book> BookStock::borrowBook(const std::string& bookName) {
	for (auto it{ m_books.begin() }; it != m_books.end(); ++it) {
		if (it->get()->getTitle() == bookName) {
			if (it->get()->getIsBorrowed()) {
				std::cout << "The book is already borrowed and cannot be borrowed twice" << std::endl;
			}
			else {
				it->get()->setIsBorrowed(true);
				std::cout << "The book " << bookName << " is now borrowed by you!" << std::endl;
			}
			return *it;
		}
	}

	return std::weak_ptr<Book>{};
}

bool BookStock::giveBackBook(std::weak_ptr<Book> bookWeak) {
	std::shared_ptr<Book> book{ bookWeak.lock() };

	if (!book) {
		std::cerr << "Invalid book. Cannot give back an invalid book" << std::endl;
		return false;
	}

	for (auto it{ m_books.begin() }; it != m_books.end(); ++it) {
		if (it->get()->getTitle() == book->getTitle()) {
			if (it->get()->getIsBorrowed()) {
				it->get()->setIsBorrowed(false);
				std::cout << "The book was given back to the library and is now available to be borrowed" << std::endl;
				return true;
			}
			else {
				std::cerr << "The book \"" << book << "\" is not borrowed. This mean that you can't give it back..." << std::endl;
				return false;
			}
		}
	}
	std::cerr << "Could'nt find any Book \"" << book->getTitle() << "\" in the BookStock to give back. BookStock was left untouched." << std::endl;
	return false;
}

//PRINTERS
void BookStock::printAllBooks() const {
	if (m_books.empty()) {
		std::cout << "No books in the library!" << std::endl;
		return;
	}
	
	for (std::shared_ptr<Book> book : m_books) {
		book->printBook();
	}
}
bool BookStock::isStockEmpty() const {
	if (m_books.empty())
		return true;
	return false;
}
