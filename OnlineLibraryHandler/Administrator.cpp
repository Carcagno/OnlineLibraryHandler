#include "Administrator.h"

//CTOR
Administrator::Administrator(const std::string& AdministratorName):
IUser{AdministratorName, 'A'} {

}

//MISC
void Administrator::cleanUserForDelete() {
	//No specific clean to do for Administrator at this time. Maybe in future evolutions
	return;
}

	//user handling
void Administrator::addUser(UserPool& userPool) {
	std::string userName{};
	char userType{};
	std::shared_ptr<IUser> tmpPtrUser;
	bool isUserAdded{ false };

	do {
		std::cout << "Please, enter the informations of the new user:\n" << "UserName: ";
		std::cin >> userName;
		if (!clearFailedExtraction())
			ignoreLine();
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		std::cout << "\n userType ( A || R ): ";
		std::cin >> userType;
		if (!clearFailedExtraction()) {
			ignoreLine();
			if (userType != 'A' && userType != 'R') {
				std::cout << "Bad user type. Available types: \'A\' for \"Administrator\" or \'B\' for \"Reader\"." 
					<< "Resetting the addUser process." << std::endl;
				continue;
			}
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		if (userType == 'A') {
			Administrator tmp{ userName };
			tmpPtrUser = std::make_shared<Administrator>(tmp);
		}
		else {
			Reader tmp{ userName };
			tmpPtrUser = std::make_shared<Reader>(tmp);
		}

		isUserAdded = userPool.addUser(tmpPtrUser);

	} while (!isUserAdded);
}

void Administrator::deleteUser(UserPool& userPool) {
	bool isUserDeleted{ false };

	do {
		std::string userName{};

		std::cout << "Please, enter the name of the user to delete";
		std::cin >> userName;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		isUserDeleted = userPool.deleteUser(userName);

	} while (!isUserDeleted);
}

void Administrator::modifyUser(UserPool& userPool) {
	std::string userName{};
	bool isModifyed{ false };

	do {
		std::cout << "Please, enter the name of the user to modify" << std::endl;
		std::cin >> userName;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		std::weak_ptr<IUser> userWeak{ userPool.getUserFromPool(userName) };
		std::shared_ptr<IUser> userShared{ userWeak.lock() };

		if (userShared) {
			std::cout << "Current user information: " << std::endl;

			if (userShared.get()->getUserType() == 'A') {
				std::shared_ptr<Administrator> tmpA{ std::dynamic_pointer_cast<Administrator>(userShared) };

				tmpA.get()->displayUser();
				tmpA.get()->selfModify();
			}
			else {
				std::shared_ptr<Reader> tmpR{ std::dynamic_pointer_cast<Reader>(userShared) };

				tmpR.get()->displayUser();
				tmpR.get()->selfModify();
			}
			isModifyed = true;
		}
	} while (!isModifyed);
}

void Administrator::displayUser() {
	IUser::displayUser();
	 
	std::cout << "Administrator" << std::endl;
}

void Administrator::showOtherUser(UserPool& userPool, const std::string& userName) {
	std::weak_ptr<IUser> userWeak{ userPool.getUserFromPool(userName) };
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

	//author handling
void Administrator::addAuthor(AuthorPool& authorPool) {
	std::shared_ptr<Author> tmpAuthorPtr{};
	std::string authorName{};
	bool isAuthorAdded{ false };

	do {
		std::cout << "Please, enter the name of the new author";
		std::cin >> authorName;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		tmpAuthorPtr = std::make_shared<Author>(Author{ authorName });
		isAuthorAdded = authorPool.addAuthor(tmpAuthorPtr);

	} while (!isAuthorAdded);
}

void Administrator::deleteAuthor(AuthorPool& authorPool) {
	std::string authorName{};
	bool isAuthorDeleted{ false };
	
	do {
		std::cout << "Please, enter the name of the author to delete";
		std::cin >> authorName;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		isAuthorDeleted = authorPool.deleteAuthor(authorName);

	} while (!isAuthorDeleted);
}

void Administrator::modifyAuthor(AuthorPool& authorPool) {
	std::string authorName{};
	bool isAuthorModifyed{ false };

	do {
		std::cout << "Please, enter the name of the author to modify";
		std::cin >> authorName;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		isAuthorModifyed = authorPool.modifyAuthor(authorName);
	} while (!isAuthorModifyed);
}

	//book handling
void Administrator::addBook(BookStock& bookStock, AuthorPool& authorPool) {
	std::string bookTitle{};
	std::weak_ptr<Author> author{};
	std::string authorName{};
	Book::bookCategory category;
	int integerCategory{};
	int publicationDate;
	std::shared_ptr<Book> book{};
	bool isBookAdded{ false };
	
	do {
		std::cout << "Please, enter the title of the book to add";
		std::cin >> bookTitle;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		std::cout << "Please, enter the name of the author for this book";
		std::cin >> authorName;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		author = authorPool.getAuthorFromPool(authorName);
		
		if (author.expired()) {
			std::cout << "Couldn't find author \"" << authorName << "\". Retrying to get all information of the book to add." << std::endl;
			continue;
		}

		Book::printAllAvailableCategory();
		std::cout << "Please enter the book category number: ";
		std::cin >> integerCategory;
		if (!clearFailedExtraction()) {
			ignoreLine();
			category = static_cast<Book::bookCategory>(integerCategory);
			if (category >= Book::bookCategory::defaultValue) {
				std::cout << "Invalid category. Retrying to get all information of the book to add." << std::endl;
				continue;
			}
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}
	

		std::cout << "Please, enter the year of publication (YYYY) of the book: ";
		std::cin >> publicationDate;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		book = std::make_shared<Book>(bookTitle, author, category, publicationDate);

		isBookAdded = bookStock.addBook(book);

	} while (!isBookAdded);
}

void Administrator::deleteBook(BookStock& bookStock) {
	std::string bookTitle{};
	bool isBookDeleted{ false };

	if (bookStock.isStockEmpty()) {
		std::cout << "Cannot delete any book. The stock is empty." << std::endl;
		return;
	}

	do {
		std::cout << "Please, choose among books in the bookStock." << std::endl;
		bookStock.printAllBooks();

		// to be refined - cin security valid input
		std::cout << "Please, enter the title of the book to delete";
		std::cin >> bookTitle;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}
		
		isBookDeleted = bookStock.deleteBook(bookTitle);
	} while (!isBookDeleted);
}

void Administrator::modifyBook(BookStock& bookStock, AuthorPool& authorPool) {
	std::string bookTitle;
	bool isBookModifyed{ false };

	do {
		std::cout << "Please, enter the title of the book to modify";
		std::cin >> bookTitle;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}
		isBookModifyed = bookStock.modifyBook(bookTitle, authorPool);
	} while (!isBookModifyed);
}

void Administrator::selfModify() {
	std::string newUserName{""};
	char newUserType{ '\0' };
	bool isSelfModifyed{ false };

	do {
		std::cout << "Enter new userName (leave empty to keep old name): ";
		std::cin >> newUserName;
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		std::cout << "Enter new userType (leave empty to keep old type), \'A\' or \'R\': ";
		std::cin >> newUserType;
		if (!clearFailedExtraction()) {
			ignoreLine();
			//to be refined - DRY Create a type validate to avoid code repetition and improve evolutivity
			if (newUserType != 'A' && newUserType != 'R') {
				std::cout << "Invalid user type. Retrying to get all information of the administrator to modify..." << std::endl;
				continue;
			}
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

		if (newUserName != "" && newUserName != "\n" && !(newUserName.empty())) {
			m_userName = newUserName;
		}

		if (newUserType != '\0' && newUserType != '\n') {
			m_userType = newUserType;
		}
	} while (!isSelfModifyed);

	std::cout << "User has been modifyed. New user informations:\n" << std::endl;
	this->displayUser();
}