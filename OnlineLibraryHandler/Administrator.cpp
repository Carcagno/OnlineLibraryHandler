#include "Administrator.h"

//CTOR
Administrator::Administrator(const std::string& AdministratorName, std::weak_ptr<BookStock> bookStock):
IUser{AdministratorName, 'A', bookStock} {

}

//MISC
void Administrator::cleanUserForDelete() {
	//No specific clean to do for Administrator at this time. Maybe in future evolutions
	return;
}

	//user handling
bool Administrator::addUser(std::weak_ptr<UserPool> userPool) {
	std::string userName{};
	char userType{};
	std::shared_ptr<IUser> tmpPtrUser;
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };


	std::cout << "Please, enter the informations of the new user:\n" << "UserName: ";
	std::getline(std::cin, userName);
	if (!clearFailedExtraction()){
	}
	else {
		std::cerr << "Failed extraction ... this message should never be prompted" << std::endl;
		return false;
	}

	std::cout << "\n userType ( A || R ): ";
	std::cin >> userType;
	if (!clearFailedExtraction()) {
		ignoreLine();
		if (userType != 'A' && userType != 'R') {
			std::cout << "Bad user type. Available types: \'A\' for \"Administrator\" or \'B\' for \"Reader\"." << std::endl;
			return false;
		}
	}
	else {
		std::cerr << "Failed extraction ... this message should never be prompted" << std::endl;
		return false;
	}

	if (userType == 'A') {
		Administrator tmp{ userName, m_bookStock };
		tmpPtrUser = std::make_shared<Administrator>(tmp);
	}
	else {
		Reader tmp{ userName, m_bookStock };
		tmpPtrUser = std::make_shared<Reader>(tmp);
	}


	if (userPoolShared) {
		return userPoolShared.get()->addUser(tmpPtrUser);
	}
	else {
		throw std::invalid_argument("Cannot add an user to an inaccessible Pool.");
	}
	return false;
}

bool Administrator::deleteUser(std::weak_ptr<UserPool> userPool) {
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };

	if (!(userPoolShared.get()->isEmpty())) {
		std::string userName{};

		std::cout << "Please, enter the name of the user to delete";
		std::getline(std::cin, userName);

		if (!clearFailedExtraction()) {
		}
		else {
			std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
			return false;
		}

		if (userPoolShared) {
			return userPoolShared.get()->deleteUser(userName);
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

bool Administrator::modifyUser(std::weak_ptr<UserPool> userPool) {
	std::string userName{};
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };

	std::cout << "Please, enter the name of the user to modify" << std::endl;
	std::getline(std::cin, userName);

	if (!clearFailedExtraction()) {
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}


	if (userPoolShared) {
		std::weak_ptr<IUser> userWeak{ userPoolShared.get()->getUserFromPool(userName) };
		std::shared_ptr<IUser> userShared{ userWeak.lock() };

		if (userShared) {
			std::cout << "Current user information: " << std::endl;

			if (userShared.get()->getUserType() == 'A') {
				std::shared_ptr<Administrator> tmpA{ std::dynamic_pointer_cast<Administrator>(userShared) };

				tmpA.get()->displayUser();
				return tmpA.get()->selfModify();
			}
			else {
				std::shared_ptr<Reader> tmpR{ std::dynamic_pointer_cast<Reader>(userShared) };

				tmpR.get()->displayUser();
				return tmpR.get()->selfModify();
			}
			return true;
		}
	}
	else {
		throw std::invalid_argument("Cannot modify an user from an inaccessible Pool.");
	}


	return false;
}

void Administrator::displayUser() {
	IUser::displayUser();
	 
	std::cout << "Administrator" << std::endl;
}

void Administrator::showOtherUser(std::weak_ptr<UserPool> userPool) {
	std::string userName{ "" };
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };

	if (userPoolShared) {

		std::cout << "availableUsers: " << std::endl;

		userPoolShared.get()->displayAllUsers();

		std::cout << "Please, enter the name of the user you want to show: ";

		std::getline(std::cin, userName);
		if (!clearFailedExtraction()) {
		}
		else {
			std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
			return;
		}

		std::weak_ptr<IUser> userWeak{ userPoolShared.get()->getUserFromPool(userName) };
		std::shared_ptr<IUser> userShared{ userWeak.lock() };

		if (userShared) {
			if (userShared.get()->getUserType() == 'A') {
				std::shared_ptr<Administrator> tmpA{ std::dynamic_pointer_cast<Administrator>(userShared) };
				tmpA.get()->displayUser();
			}
			else {
				std::shared_ptr<Reader> tmpR{ std::dynamic_pointer_cast<Reader>(userShared) };
				tmpR.get()->displayUser();
			}
		}
	}
	else {
		std::cerr << "Cannot show an user from an inaccessible Pool.";
		return;
	}
}
	//author handling
bool Administrator::addAuthor(std::weak_ptr<AuthorPool> authorPool) {
	std::string authorName{};
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };

	std::cout << "Please, enter the name of the author to add";
	std::getline(std::cin, authorName);

	if (!clearFailedExtraction()) {
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	if (authorPoolShared) {
		std::shared_ptr<Author> author{ Author::create(authorName, authorPoolShared) };
		return true;
	}
	else {
		throw std::invalid_argument("Cannot add an author from an empty Pool.");
	}
	return false;
}

bool Administrator::deleteAuthor(std::weak_ptr<AuthorPool> authorPool) {
	std::string authorName{};
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };

	std::cout << "Please, enter the name of the author to delete";
	std::getline(std::cin, authorName);

	if (!clearFailedExtraction()) {
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	if (authorPoolShared) {
		return authorPoolShared.get()->deleteAuthor(authorName);
	}
	else {
		throw std::invalid_argument("Cannot delete an author from an empty Pool.");
	}
	return false;
}


bool Administrator::modifyAuthor(std::weak_ptr<AuthorPool> authorPool) {
	std::string authorName{};
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };

	std::cout << "Please, enter the name of the author to modify";
	std::getline(std::cin, authorName);
	if (!clearFailedExtraction()) {
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}
	if (authorPoolShared) {
		return authorPoolShared.get()->modifyAuthor(authorName);
	}
	else {
		throw std::invalid_argument("Cannot modify an author from an empty Pool.");
	}
}

	//book handling

bool Administrator::addBook(std::weak_ptr<BookStock> bookStock, std::weak_ptr<AuthorPool> authorPool) {
	std::string bookTitle{""};
	std::string authorName{ "" };
	int category{ -1 };
	int publicationDate{ -9999 };
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };
	std::shared_ptr<BookStock> bookStockShared{ bookStock.lock() };
	std::shared_ptr<Author> authorShared{};

	std::cout << "Please, enter the title of the book to add";
	std::getline(std::cin, bookTitle);
	if (!clearFailedExtraction()) {
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}
	if (bookTitle == "" || bookTitle == "\n") {
		std::cerr << "Impossible to create a book with an empty name" << std::endl;
		return false;
	}


	std::cout << "Please, enter the author name of the book to add";
	std::getline(std::cin, authorName);
	if (!clearFailedExtraction()) {
		authorPoolShared = authorPool.lock();
		if (authorPoolShared) {
			authorShared = (authorPoolShared.get()->getAuthorFromPool(authorName)).lock();
			if (!authorShared) {
				std::cerr << "Could'nt find the author " << authorName << "! Impossible to add a non-existent author." << std::endl;
				return false;
			}
		}
		else {
			std::cerr << "impossible to create an author from an empty author pool" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	std::cout << "Please, choose a category among folllowing ones: " << std::endl;
	Book::printAllAvailableCategory();
	
	std::cin >> category;
	if (!clearFailedExtraction()) {

		if (category < 0 || category > Book::bookCategory::defaultValue) {
			std::cerr << "Invalid category. Old category left untouched. Please, retry to modifyBook again if you want to change the category" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	std::cin >> publicationDate;
	if (!clearFailedExtraction()) {
		if (publicationDate == -9999) {
			std::cerr << "Invalid date." << std::endl;
			return false;
		} 
	}

	if (bookStockShared) {
		auto bookEnd{ Book::create(bookTitle, authorShared, static_cast<Book::bookCategory>(category), publicationDate, bookStockShared) };
		if (bookEnd) {
			std::cout << "Created book: " << std::endl;
			bookEnd.get()->printBook();
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

bool Administrator::deleteBook(std::weak_ptr<BookStock> bookStock) {
	std::string bookTitle;
	std::shared_ptr<BookStock> bookStockShared{ bookStock.lock() };

	std::cout << "Please, enter the title of the book to modify";
	std::getline(std::cin, bookTitle);
	if (!clearFailedExtraction()) {
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	if (bookStockShared) {
		return bookStockShared.get()->deleteBook(bookTitle);
	}
	else {
		throw std::invalid_argument("Cannot modify a book from an empty Pool");
	}
}

bool Administrator::modifyBook(std::weak_ptr<BookStock> bookStock, std::weak_ptr<AuthorPool> authorPool) {
	std::string bookTitle;
	std::shared_ptr<BookStock> bookStockShared{ bookStock.lock() };

	std::cout << "Please, enter the title of the book to modify";
	std::getline(std::cin, bookTitle);
	if (!clearFailedExtraction()) {
	}
	else {
		std::cout << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	if (bookStockShared) {
		return bookStockShared.get()->modifyBook(bookTitle, authorPool);
	}
	else {
		throw std::invalid_argument("Cannot modify a book from an empty Pool");
	}
}

bool Administrator::selfModify() {
	std::string newUserName{ "" };
	char newUserType{ '\0' };

	std::cout << "Enter new userName (leave empty to keep old name): ";
	std::getline(std::cin, newUserName);

	if (!clearFailedExtraction()) {
	}
	else {
		std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	std::cout << "Enter new userType (leave empty to keep old type), \'A\' or \'R\': ";
	std::cin >> newUserType;
	if (!clearFailedExtraction()) {

		//to be refined - DRY Create a type validate to avoid code repetition and improve evolutivity
		if (newUserType != 'A' && newUserType != 'R') {
			std::cout << "Invalid user type." << std::endl;
			return false;
		}
	}
	else {
		std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
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

	std::cout << "User has been modifyed. New user informations:\n" << std::endl;
	this->displayUser();
	
	return true;
}

bool Administrator::selfExecute(std::shared_ptr<AuthorPool> authorPool, std::shared_ptr<BookStock> bookStock, std::shared_ptr<UserPool> userPool) {
	std::string userChoice{ "" };

	std::cout << std::endl << "Welcome to the online library! As Administrator, you can use the following command (type the command showed between square brackets [???] to execute it): " << std::endl;
	while (userChoice != "quit") {
		std::cout << "[createUser]: To created a new user (Administrator or Reader)\n"
			<< "[deleteUser]: To delete an existing user. The user must exists in the system prior to the execution of this command.\n"
			<< "[modifyUser]: To modify an existing user. The user must exists in the system prior to the execution of this command.\n"
			<< "[showUser]: To show the information about a specific user. The user must exists in the system prior to the execution of this command.\n"
			<< "[createAuthor]: To create an author. An author must be created before adding a book written by the author.\n"
			<< "[deleteAuthor]: To delete an author. If there are remaining books written by this author, the author will be set as \"Unknown\" in those books.\n"
			<< "[modifyAuthor]: To modify an author. The books written by this author will have the informations about the author updated.\n"
			<< "[displayMe]: To display your account informations.\n"
			<< "[searchBook]: To search a book in the library and display the information about it.\n" // to be refined - implement a real search. findIf ?
			<< "[searchAuthor]: To search an author in the library and display the information about it.\n"// to be refined - same as previous
			<< "[quit]: to quit the library.\n"
			<< std::endl; // to be refined - maybe a command to display all books / users / authors ?

		std::getline(std::cin, userChoice);
		if (!clearFailedExtraction()) {
			std::transform(userChoice.begin(), userChoice.end(), userChoice.begin(), ::tolower);
		}
		else {
			std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
			return false;
		}

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
		else if (userChoice == "displayme") {
			this->displayUser();
		}
		else if (userChoice == "searchbook") {
			std::string bookTitle{ "" };

			std::cout << "Available books: " << std::endl;

			bookStock.get()->printAllBooks();


			std::cout << "Please, enter the title of the book you want to search about: ";


			std::getline(std::cin, bookTitle);
			if (!clearFailedExtraction()) {
			}
			else {
				std::cout << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}


			std::shared_ptr<Book> book{ bookStock.get()->getBookFromStock(bookTitle).lock()};

			if (book) {
				book.get()->printBook();
			}

		}
		else if (userChoice == "searchauthor") {
			std::string authorName{ "" };
			
			std::cout << "Available Authors: " << std::endl;

			authorPool.get()->printAllAuthors();

			std::cout << "Please, enter the name of the author you want to search about: ";

			std::getline(std::cin, authorName);
			if (!clearFailedExtraction()) {
			}
			else {
				std::cout << "Failed extraction... this message should never be prompted" << std::endl;
				return false;
			}

			std::shared_ptr<Author> author{ authorPool.get()->getAuthorFromPool(authorName).lock()};
			
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
}