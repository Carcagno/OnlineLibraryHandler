#include "Reader.h"

Reader::Reader(const std::string& readerName, std::weak_ptr<BookStock> bookStock) :
	IUser(readerName, 'R', bookStock),
	m_borrowedBookCount{0} {
}

void Reader::cleanUserForDelete() {
	for (std::weak_ptr<Book> book : m_borrowedBooks) {
		std::shared_ptr<Book> bookSharedPtr{book.lock()};
		if (bookSharedPtr) {
			this->giveBackBook(bookSharedPtr.get()->getTitle());
		}
	}

	m_borrowedBookCount = 0;
}

void Reader::borrowBook(const std::string& bookName) {
	std::shared_ptr<BookStock> bookStockShared{ m_bookStock.lock() };

	if (bookStockShared) {
		std::weak_ptr<Book> bookWeakPtr{ bookStockShared.get()->borrowBook(bookName)};
		std::shared_ptr<Book> bookSharedPtr{ bookWeakPtr.lock() };
		if (bookSharedPtr) {
			std::cout << "Book: " << bookSharedPtr->getTitle() << " is now borrowed by you " << m_userName << std::endl;
			++m_borrowedBookCount;
			m_borrowedBooks.push_back(bookWeakPtr);
		}
		else {
			std::cout << "Book " << bookName << " could'nt be borrowed. The title you provided may be wrong." << std::endl;
		}
	}
	else {
		throw std::runtime_error("Error: Reader could'nt borrow a book because of invalid m_bookStock ptr");
	}
}

void Reader::printBorrowedBooks() const {
	//to be refined 
	if (m_borrowedBookCount == 0) {
		std::cout << "You did'nt borrow any book." << std::endl;
		return;
	}
	
	std::cout << "You borrowed " << m_borrowedBookCount << " book(s)" << std::endl;

	for (std::weak_ptr<Book> book : m_borrowedBooks) {
		std::shared_ptr<Book> bookSharedPtr{book.lock()};
		if (bookSharedPtr) {
			bookSharedPtr->printBook();
		}
	}
}

void Reader::giveBackBook(const std::string& book) {
	std::shared_ptr<BookStock> bookStockShared{ m_bookStock.lock() };
	
	if (bookStockShared) {
		for (auto it{ m_borrowedBooks.begin() }; it != m_borrowedBooks.end(); ++it) {
			std::shared_ptr<Book> bookSharedPtr{ it->lock() };
			if (bookSharedPtr) {
				if (bookSharedPtr->getTitle() == book) {
					bookStockShared.get()->giveBackBook(bookSharedPtr);
					m_borrowedBooks.erase(it);
					--m_borrowedBookCount;
					std::cout << "The book " << book << " was successfully given back" << std::endl;
					return;
				}
			}
		}

	}
	else {
		throw std::runtime_error("Error: Reader could'nt give back a book because of invalid m_bookStock ptr");
	}

	std::cout << "You didn't borrowed the book " << book << ". Then, you can't give it back ..." << std::endl;
}

void Reader::displayUser() {
	IUser::displayUser();
	std::cout << "Reader\n" << std::endl;
	
	std::cout << "List of borrowed books: \n";
	for (std::weak_ptr<Book> book : m_borrowedBooks) {
		std::shared_ptr<Book> bookSharedPtr{ book.lock() };

		if (bookSharedPtr) {
			bookSharedPtr.get()->printBook();
		}
		else {
			std::cerr << "One of the borrowed book is unvalid or impossible to access. Skipping ..." << std::endl;
		}
	}
}

bool Reader::selfModify() {
	//to be refined - DRY: mayber IUser implem and call for Admin & Reader ?
	std::string newUserName{ "" };
	char newUserType{ '\0' };

	std::cout << "Enter new userName (leave empty to keep old name): ";
	std::cin >> newUserName;
	if (!clearFailedExtraction()) {
		ignoreLine();
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	std::cout << "Enter new userType (leave empty to keep old type), \'A\' or \'R\': ";
	std::cin >> newUserType;
	if (!clearFailedExtraction()) {
		ignoreLine();
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	if (newUserName != "" && newUserName != "\n" && !(newUserName.empty())) {
		m_userName = newUserName;
	}
	else {
		std::cerr << "Cannot use an empty name" << std::endl;
		return false;
	}

	if (newUserType != '\0' && newUserType != '\n') {
		m_userType = newUserType;
	}
	else {
		std::cerr << "Cannot use an empty type" << std::endl;
		return false;
	}

	//to be refined maybe implement a way to have books borrowed modifyed (imply to display, and ask for each if admin wants to change borrow status ?)

	std::cout << "User has been modifyed. New user informations:\n" << std::endl;
	this->displayUser();

	return true;
}