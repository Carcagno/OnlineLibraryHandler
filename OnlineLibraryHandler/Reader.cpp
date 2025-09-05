#include "Reader.h"

#include <memory>
#include <iostream>
#include <algorithm>
#include <cctype>

#include "Book.h"
#include "BookStock.h"
#include "AuthorPool.h"
#include "UserPool.h"

#include "Utils.h"

Reader::Reader(const std::string& readerName, std::weak_ptr<BookStock> bookStock) :
	IUser(readerName, IUser::UserType::Reader, bookStock),
	m_borrowedBookCount{0} {
}

void Reader::cleanUserForDelete() {
	for (const std::weak_ptr<Book>& book : m_borrowedBooks) {
		std::shared_ptr<Book> bookSharedPtr{book.lock()};
		if (bookSharedPtr) {
			this->giveBackBook(bookSharedPtr.get()->getTitle());
		}
	}

	m_borrowedBookCount = 0;
}

bool Reader::borrowBook(const std::string& bookName) {
	std::shared_ptr<BookStock> bookStockShared{ m_bookStock.lock() };

	if (bookStockShared) {
		std::weak_ptr<Book> bookWeakPtr{ bookStockShared.get()->borrowBook(bookName)};
		std::shared_ptr<Book> bookSharedPtr{ bookWeakPtr.lock() };
		if (bookSharedPtr) {
			std::cout << "Book: " << bookSharedPtr->getTitle() << " is now borrowed by you " << m_userName << std::endl;
			++m_borrowedBookCount;
			m_borrowedBooks.push_back(bookWeakPtr);
			return true;
		}
		else {
			std::cerr << "Book " << bookName << " couldn't be borrowed. The title you provided may be wrong." << std::endl;
			return false;
		}
	}
	else {
		std::cerr << "Error: Reader couldn't borrow a book because of invalid m_bookStock ptr" << std::endl;
		return false;
	}
}

void Reader::printBorrowedBooks() const {
	//to be refined 
	if (m_borrowedBookCount == 0) {
		std::cout << "You didn't borrow any book." << std::endl;
		return;
	}
	
	std::cout << "You borrowed " << m_borrowedBookCount << " book(s)" << std::endl;

	for (const std::weak_ptr<Book>& book : m_borrowedBooks) {
		std::shared_ptr<Book> bookSharedPtr{book.lock()};
		if (bookSharedPtr) {
			bookSharedPtr->printBook();
		}
	}
}

bool Reader::giveBackBook(const std::string& bookTitle) {
	std::shared_ptr<BookStock> bookStockShared{ m_bookStock.lock() };
	
	if (bookStockShared) {
		for (auto it{ m_borrowedBooks.begin() }; it != m_borrowedBooks.end(); ++it) {
			std::shared_ptr<Book> bookSharedPtr{ it->lock() };
			if (bookSharedPtr) {
				if (bookSharedPtr->getTitle() == bookTitle) {
					bookStockShared.get()->giveBackBook(bookSharedPtr);
					m_borrowedBooks.erase(it);
					--m_borrowedBookCount;
					std::cout << "The book " << bookTitle << " was successfully given back" << std::endl;
					return true;
				}
			}
		}

	}
	else {
		std::cerr << "Error: Reader could'nt give back a book because of invalid m_bookStock ptr" << std::endl;
		return false;
	}

	std::cout << "You didn't borrowed the book " << bookTitle << ". Then, you can't give it back ..." << std::endl;
	return false;
}

void Reader::displayUser() const {
	IUser::displayUser();
	std::cout << "Reader\n" << std::endl;
	
	std::cout << "List of borrowed books: \n";
	for (const std::weak_ptr<Book>& book : m_borrowedBooks) {
		std::shared_ptr<Book> bookSharedPtr{ book.lock() };

		if (bookSharedPtr) {
			bookSharedPtr.get()->printBook();
		}
		else {
			std::cerr << "One of the borrowed book is unvalid or impossible to access. Skipping ..." << std::endl;
		}
	}
}

bool Reader::selfModify(std::shared_ptr<UserPool> userPool, std::shared_ptr<BookStock> bookStock) { // ERROR
	//to be refined - DRY: mayber IUser implem and call for Admin & Reader ?
	std::string newUserName{ "" };
	char newUserType{ '\0' };

	if (!(readNonEmptyLine("Enter new userName: ", newUserName))) {
		return false;
	}

	if (!(readCharOption("Enter new userType, \'A\' or \'R\': ", "AR", newUserType))) {
		return false;
	}

	//to be refined maybe implement a way to have books borrowed modifyed (imply to display, and ask for each if admin wants to change borrow status ?)
	std::cout << "User has been modified. New user informations:\n" << std::endl;
	if (static_cast<IUser::UserType>(newUserType) != m_userType) {
		std::shared_ptr<Administrator> a{ std::make_shared<Administrator>(newUserName, bookStock) };

		if (!(userPool->deleteUser(this->m_userName))) {
			std::cerr << "Aborting modification: Impossible to delete the old user from the UserPool! The old user is kept as it was." << std::endl;
			return false;
		}

		if (!(userPool->addUser(a))) {
			std::cerr << "Aborting modification: Impossible to add the new user to the UserPool! The old user is definitievely lost..." << std::endl;
			return false;
		}
		a->displayUser();
	}
	else {
		m_userName = newUserName;
		this->displayUser();
	}

	return true;
}

bool Reader::selfExecute(std::shared_ptr<AuthorPool> authorPool, std::shared_ptr<BookStock> bookStock, std::shared_ptr<UserPool> userPool) {
	std::string userChoice{ "" };

	std::cout << std::endl << "Welcome to the online library! As Reader, you can use the following command (type the command showed between square brackets [???] to execute it): " << std::endl;
	while (userChoice != "quit") {
		std::cout << "[borrowBook]: To borrow an existing Book in the library. The Book must be available and exists in the Book Stock of the library.\n"
			<< "[giveBackBook]: To give back a Book you borrowed before. The Book must be borrowed by you and exists in the Book Stock\n"
			<< "[searchBook]: To search a book in the library and display the information about it.\n" // to be refined - implement a real search. findIf ?
			<< "[searchAuthor]: To search an author in the library and display the information about it.\n"// to be refined - same as previous
			<< "[quit]: to quit the library.\n"
			<< std::endl; // to be refined - maybe a command to display all books / users / authors ?

		if (!(readNonEmptyLine("", userChoice))) {
			continue;
		}

		if (userChoice == "borrowbook") {
			std::string bookTitle{ "" };

			std::cout << "Available Books in the library: " << std::endl;

			bookStock.get()->printAllBooks();

			std::cout << "Please, Enter the name of the book that you want to borrow: ";

			if (!(std::getline(std::cin, bookTitle)) || clearFailedExtraction()) {
				std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}

			this->borrowBook(bookTitle);
		}
		else if (userChoice == "givebackbook") {
			std::string bookTitle{ "" };

			std::cout << "Book you borrowed: " << std::endl;

			this->printBorrowedBooks();
			
			std::cout << "Please, Enter the name of the book that you want to give back: ";

			if (!(std::getline(std::cin, bookTitle)) || clearFailedExtraction()) {
				std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}
			this->giveBackBook(bookTitle);
		}
		else if (userChoice == "displayme") {
			this->displayUser();
		}
		else if (userChoice == "searchbook") {
			std::string bookTitle{ "" };

			std::cout << "Available books: " << std::endl;

			bookStock.get()->printAllBooks();


			std::cout << "Please, enter the title of the book you want to search about: ";


			
			if (!(std::getline(std::cin, bookTitle)) || clearFailedExtraction()) {
				std::cout << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}


			std::shared_ptr<Book> book{ bookStock.get()->getBookFromStock(bookTitle).lock() };

			if (book) {
				book.get()->printBook();
			}

		}
		else if (userChoice == "searchauthor") {
			std::string authorName{ "" };

			std::cout << "Available Authors: " << std::endl;

			authorPool.get()->printAllAuthors();

			std::cout << "Please, enter the name of the author you want to search about: ";

			if (!(std::getline(std::cin, authorName)) || clearFailedExtraction()) {
				std::cout << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}

			std::shared_ptr<Author> author{ authorPool.get()->getAuthorFromPool(authorName).lock() };

			if (author) {
				author.get()->printAuthor();
			}

		}
		else if (userChoice == "quit") {
			std::cout << "Exiting the library.";
		}
		else {
			std::cout << "Unknown command: " << userChoice << std::endl;
		}

		std::cout << "\n\n" << std::endl;
	}
	
	return true;
}