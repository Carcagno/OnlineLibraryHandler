#include "Administrator.h"

#include "Utils.h"
#include "Reader.h"
#include "Author.h"
#include "Book.h"
#include "BookStock.h"
#include "UserPool.h"
#include "AuthorPool.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include <cctype>

//CTOR
Administrator::Administrator(const std::string& AdministratorName, std::weak_ptr<BookStock> bookStock):
IUser{AdministratorName, IUser::UserType::Administrator, bookStock} {

}

//MISC
void Administrator::cleanUserForDelete() {
	//No specific clean to do for Administrator at this time. Maybe in future evolutions
	return;
}

	//user handling
bool Administrator::addUser(std::shared_ptr<UserPool> userPool) {
	std::string userName{};
	char userType{};
	std::shared_ptr<IUser> tmpPtrUser;

	if (!(readNonEmptyLine("Please, enter the information of the new user:\nUserName: ", userName))) {
		return false;
	}

	if (!(readCharOption("\nUserType(A || R) : ", "AR", userType))) {
		return false;
	}

	if (userType == 'A') {
		tmpPtrUser = std::make_shared<Administrator>(userName, m_bookStock);
	}
	else {
		tmpPtrUser = std::make_shared<Reader>(userName, m_bookStock);
	}


	if (userPool) {
		return userPool->addUser(tmpPtrUser);
	}
	else {
		throw std::invalid_argument("Cannot add an user to an inaccessible Pool.");
	}
	return false;
}

bool Administrator::deleteUser(std::shared_ptr<UserPool> userPool) {
	if (!(userPool->isEmpty())) {
		std::string userName{};

		if (!(readNonEmptyLine("Please, enter the name of the user to delete: ", userName))) {
			return false;
		}

		if (userPool) {
			return userPool->deleteUser(userName);
		}
		else {
			throw std::invalid_argument("Cannot delete an user from an inaccessible Pool.");
		}
	}
	else {
		std::cout << "The UserPool is empty. Impossible to delete an user from an empty pool..." << std::endl;
		return false;
	}

	return false;
}

bool Administrator::modifyUser(std::shared_ptr<UserPool> userPool) {
	std::string userName{};

	if (!(readNonEmptyLine("Please, enter the name of the user to modify: ", userName))) {
		return false;
	}

	if (userPool) {
		std::weak_ptr<IUser> userWeak{ userPool->getUserFromPool(userName) };
		std::shared_ptr<IUser> userShared{ userWeak.lock() };

		if (userShared) {
			std::cout << "Current user information: " << std::endl;

			userShared->displayUser();

			return userShared->selfModify(userPool, m_bookStock.lock());
		}
	}
	else {
		throw std::invalid_argument("Cannot modify an user from an inaccessible Pool.");
	}
	return false;
}

void Administrator::displayUser() const {
	IUser::displayUser();
	
	std::cout << "Administrator" << std::endl;
}

void Administrator::showOtherUser(std::shared_ptr<UserPool> userPool) {
	std::string userName{ "" };

	if (userPool) {

		if (userPool->isEmpty()) {
			std::cout << "The user pool is empty! No user to show." << std::endl;
			return;
		}

		std::cout << "availableUsers: " << std::endl;

		userPool->displayAllUsers();

		if (!(readNonEmptyLine("Please, enter the name of the user you want to show: ", userName))) {
			return;
		}

		std::weak_ptr<IUser> userWeak{ userPool->getUserFromPool(userName) };
		std::shared_ptr<IUser> userShared{ userWeak.lock() };

		if (userShared) {
				userShared->displayUser();
		}
	}
	else {
		std::cerr << "Cannot show an user from an inaccessible Pool.";
		return;
	}
}
	//author handling
bool Administrator::addAuthor(std::shared_ptr<AuthorPool> authorPool) {
	std::string authorName{};

	if (!(readNonEmptyLine("Please, enter the name of the author to add: ", authorName))) {
		return false;
	}

	if (authorPool) {
		std::shared_ptr<Author> author{ Author::create(authorName, authorPool) };
		std::cout << "The author " << authorName << " was created." << std::endl;
		return true;
	}
	else {
		throw std::invalid_argument("Cannot add an author from an empty Pool.");
	}
	return false;
}

bool Administrator::deleteAuthor(std::shared_ptr<AuthorPool> authorPool) {
	std::string authorName{};

	if (!(readNonEmptyLine("Please, enter the name of the author to delete: ", authorName))) {
		return false;
	}

	if (authorPool) {
		return authorPool->deleteAuthor(authorName);
	}
	else {
		throw std::invalid_argument("Cannot delete an author from an empty Pool.");
	}
	return false;
}


bool Administrator::modifyAuthor(std::shared_ptr<AuthorPool> authorPool) {
	std::string authorName{};

	if (!(readNonEmptyLine("Please, enter the name of the author to modify: ", authorName))) {
		return false;
	}
	if (authorPool) {
		return authorPool->modifyAuthor(authorName);
	}
	else {
		throw std::invalid_argument("Cannot modify an author from an empty Pool.");
	}
}

	//book handling

bool Administrator::addBook(std::shared_ptr<BookStock> bookStock, std::shared_ptr<AuthorPool> authorPool) {
	std::string bookTitle{""};
	std::string authorName{ "" };
	int category{ -1 };
	int publicationDate{ -9999 };
	std::shared_ptr<Author> authorShared{};

	if (!(readNonEmptyLine("Please, enter the title of the book to add: ", bookTitle))) {
		return false;
	}

	if (!(readNonEmptyLine("Please, enter the author name of the book to add: ", authorName))) {
		return false;
	}

	if (authorPool) {
		authorShared = (authorPool->getAuthorFromPool(authorName)).lock();
		if (!authorShared) {
			std::cerr << "Could'nt find the author " << authorName << "! Impossible to add a non-existent author." << std::endl;
			return false;
		}
	}
	else {
		std::cerr << "impossible to create an author from an empty author pool" << std::endl;
		return false;
	}

	std::cout << "Please, choose a category among following ones: " << std::endl;
	Book::printAllAvailableCategory();
	
	

	if (!(readValue("", category))) {
		std::cerr << "Wrong category value." << std::endl;
		return false;
	}


	if (category < 0 || category > static_cast<int>(Book::bookCategory::defaultValue)) {
		std::cerr << "Invalid category." << std::endl;
		return false;
	}

	if (!(readValue("Please, choose a publication date (Year): ", publicationDate))) {
		std::cerr << "Wrong publication date value." << std::endl;
		return false;
	}

	if (publicationDate == -9999) {
		std::cerr << "Invalid date." << std::endl;
		return false;
	}

	if (bookStock) {
		auto bookEnd{ Book::create(bookTitle, authorShared, static_cast<Book::bookCategory>(category), publicationDate, bookStock) };
		if (bookEnd) {
			std::cout << "\nCreated book: " << std::endl;
			bookEnd->printBook();
			ignoreLine();
			return true;
		}
		else {
			std::cerr << "Failed to create the book with the given information" << std::endl;
			return false;
		}
	}
	else {
		throw std::invalid_argument("Cannot add a book from an empty Pool");
		return false;
	}

}

bool Administrator::deleteBook(std::shared_ptr<BookStock> bookStock) {
	std::string bookTitle;

	if (!(readNonEmptyLine("Please, enter the title of the book to delete: ", bookTitle))) {
		return false;
	}

	if (bookStock) {
		return bookStock->deleteBook(bookTitle);
	}
	else {
		throw std::invalid_argument("Cannot modify a book from an empty Pool");
	}
}

bool Administrator::modifyBook(std::shared_ptr<BookStock> bookStock, std::shared_ptr<AuthorPool> authorPool) {
	std::string bookTitle;

	if (!(readNonEmptyLine("Please, enter the title of the book to modify: ", bookTitle))) {
		return false;
	}

	if (bookStock) {
		return bookStock->modifyBook(bookTitle, authorPool);
	}
	else {
		throw std::invalid_argument("Cannot modify a book from an empty Pool");
	}
}

bool Administrator::selfModify(std::shared_ptr<UserPool> userPool, std::shared_ptr<BookStock> bookStock) {
	std::string newUserName{ "" };
	char newUserType{ '\0' };

	if (!(readNonEmptyLine("Enter new userName: ", newUserName))) {
		return false;
	}

	if (!(readCharOption("Enter new userType, \'A\' or \'R\': ", "AR", newUserType))) {
		return false;
	}

	std::cout << "User has been modified. New user informations:\n" << std::endl;
	if (static_cast<IUser::UserType>(newUserType) != m_userType) {
		std::shared_ptr<Reader> r{ std::make_shared<Reader>(newUserName, bookStock)};

		if (!(userPool->deleteUser(this->m_userName))) {
			std::cerr << "Aborting modification: Impossible to delete the old user from the UserPool! The old user is kept as it was." << std::endl;
			return false;
		}

		if (!(userPool->addUser(r))) {
			std::cerr << "Aborting modification: Impossible to add the new user to the UserPool! The old user is definitievely lost..." << std::endl;
			return false;
		}
		r->displayUser();
	}
	else {
		m_userName = newUserName;
		this->displayUser();
	}
	return true;
}

bool Administrator::selfExecute(std::shared_ptr<AuthorPool> authorPool, std::shared_ptr<BookStock> bookStock, std::shared_ptr<UserPool> userPool) {
	std::string userChoice{ "" };

	if (!authorPool || !bookStock || !userPool) {
		throw std::invalid_argument("Error: One of the pool / stock is no valid. Cannot work with one of those entities in an invalid state.");
	}

	std::cout << std::endl << "Welcome to the online library! As Administrator, you can use the following command (type the command showed between square brackets [???] to execute it): " << std::endl;
	while (userChoice != "quit") {
		std::cout << "[createUser]: To created a new user (Administrator or Reader)\n"
			<< "[deleteUser]: To delete an existing user. The user must exists in the system prior to the execution of this command.\n"
			<< "[modifyUser]: To modify an existing user. The user must exists in the system prior to the execution of this command.\n"
			<< "[showUser]: To show the information about a specific user. The user must exists in the system prior to the execution of this command.\n"
			<< "[createAuthor]: To create an author. An author must be created before adding a book written by the author.\n"
			<< "[deleteAuthor]: To delete an author. If there are remaining books written by this author, the author will be set as \"Unknown\" in those books.\n"
			<< "[modifyAuthor]: To modify an author. The books written by this author will have the informations about the author updated.\n"
			<< "[createBook]: To create a book. The author of the book must be created prior to the execution of this command.\n"
			<< "[deleteBook]: To delete an existing book. The book must exists in the book stock of the library. The author of the book will not have this book in his collection anymore.\n"
			<< "[modifyBook]: To modify an existing book. The book to modify must exists in the book stock of the library. If a new author is linked to the book, this new author must also exist.\n"
			<< "[displayMe]: To display your account informations.\n"
			<< "[searchBook]: To search a book in the library and display the information about it.\n" // to be refined - implement a real search. findIf ?
			<< "[searchAuthor]: To search an author in the library and display the information about it.\n"// to be refined - same as previous
			<< "[quit]: to quit the library.\n"
			<< std::endl; // to be refined - maybe a command to display all books / users / authors ?

		if (!(readNonEmptyLine("", userChoice))) {
			continue;
		}

		std::transform(userChoice.begin(), userChoice.end(), userChoice.begin(), ::tolower);
		//to be refined - maybe use a std::map with <string, function<bool()>> for all the commands ?
		if (userChoice == "createuser") {
			this->addUser(userPool);
		}
		else if (userChoice == "deleteuser") {
			this->deleteUser(userPool);
		}
		else if (userChoice == "modifyuser") {
			this->modifyUser(userPool);
		}
		else if (userChoice == "showuser") {
			this->showOtherUser(userPool);
		}
		else if (userChoice == "createauthor") {
			this->addAuthor(authorPool);
		}
		else if (userChoice == "deleteauthor") {
			this->deleteAuthor(authorPool);
		}
		else if (userChoice == "createbook") {
			this->addBook(bookStock, authorPool);
		}
		else if (userChoice == "deletebook") {
			this->deleteBook(bookStock);
		}
		else if (userChoice == "modifybook") {
			this->modifyBook(bookStock,authorPool);
		}
		else if (userChoice == "displayme") {
			this->displayUser();
		}
		else if (userChoice == "searchbook") {
			std::string bookTitle{ "" };

			std::cout << "Available books: " << std::endl;

			bookStock->printAllBooks();

			if (!(readNonEmptyLine("Please, enter the title of the book you want to search about: ", bookTitle))) {
				std::cout << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}


			std::shared_ptr<Book> book{ bookStock->getBookFromStock(bookTitle).lock()};

			if (book) {
				book->printBook();
			}

		}
		else if (userChoice == "searchauthor") {
			std::string authorName{ "" };
			
			std::cout << "Available Authors: " << std::endl;

			authorPool->printAllAuthors();

			std::cout << "";

			if (!(readNonEmptyLine("Please, enter the name of the author you want to search about: ", authorName))) {
				std::cout << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}

			std::shared_ptr<Author> author{ authorPool->getAuthorFromPool(authorName).lock()};
			
			if (author) {
				author->printAuthor();
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