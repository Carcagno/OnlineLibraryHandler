#include "Reader.h"

Reader::Reader(const std::string& readerName, const char readerType) :
	IUser(readerName, readerType),
	m_borrowedBookCount{0} {

}

void Reader::cleanUserForDelete() {
	for (auto book : m_borrowedBooks) {
		//to be refined
		/*std::shared_ptr<Book> bookSharedPtr{book.lock()};
		if (bookSharedPtr) {
			bookSharedPtr->setIsBorrowed(false);
		}*/
	}

	m_borrowedBookCount = 0;
}

void Reader::borrowBook(const std::string& bookName, const BookStock& bookStock) {
	//to be refined
	/*auto bookWeakPtr{bookStock.borrowBook(bookName)};
	std::shared_ptr<Book> bookSharedPtr{ bookWeakPtr.lock() };
	if (bookSharedPtr) {
		std::cout << "Book: " << bookSharedPtr->getTitle() << " is now borrowed by you " << m_userName << std::endl;
		++m_borrowedBookCount;
		m_borrowedBooks.push_back(bookWeakPtr);
	}
	else {
		//to be refined - Error handling
		std::cout << "Book " << bookName << " could'nt be borrowed" << std::endl;
	}*/
}

void Reader::printBorrowedBooks() const {
	//to be refined 
	if (m_borrowedBookCount == 0) {
		std::cout << "You did'nt borrow any book" << std::endl;
		return;
	}
	
	std::cout << "You borrowed " << m_borrowedBookCount << " book(s)" << std::endl;

	/*for (auto book : m_borrowedBooks) {
		std::shared_ptr<Book> bookSharedPtr{book.lock()};
		if (bookSharedPtr) {
			bookSharedPtr->printBook();
		}
	}*/
}

void Reader::giveBackBook(const std::string& book) {
	//to be refined
	/*
	for (auto it{ m_borrowedBooks.begin() }; it != m_borrowedBooks.end(); ++it) {
		std::shared_ptr<Book> bookSharedPtr{ it->lock() };
		if (bookSharedPtr) {
			if (bookSharedPtr->getTitle() == book) {
				bookSharedPtr->setIsBorrowed = false;
				m_borrowedBooks.erase(it);
				--m_borrowedBookCount;
				std::cout << "The book " << book << " was successfully given back" << std::endl;
				return;
			}
		}
	}
	*/
	// to be refined - Error handling
	std::cout << "You didn't borrowed the book " << book << ". Then, you can't give it back ..." << std::endl;
}