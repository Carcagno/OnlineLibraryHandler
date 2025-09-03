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
	if (!clearFailedExtraction())
		ignoreLine();
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
			ignoreLine();
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
		ignoreLine();
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

void Administrator::showOtherUser(std::weak_ptr<UserPool> userPool, const std::string& userName) {
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };
	
	if (userPoolShared) {
		std::weak_ptr<IUser> userWeak{ userPoolShared.get()->getUserFromPool(userName)};
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
		throw std::invalid_argument("Cannot show an user from an inaccessible Pool.");
	}
}
	//author handling
bool Administrator::addAuthor(std::weak_ptr<AuthorPool> authorPool) {
	std::string authorName{};
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };

	std::cout << "Please, enter the name of the author to add";
	std::getline(std::cin, authorName);

	if (!clearFailedExtraction()) {
		ignoreLine();
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
		throw std::invalid_argument("Cannot modify an author from an empty Pool.");
	}
}


bool Administrator::modifyAuthor(std::weak_ptr<AuthorPool> authorPool) {
	std::string authorName{};
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };

	std::cout << "Please, enter the name of the author to modify";
	std::getline(std::cin, authorName);
	if (!clearFailedExtraction()) {
		ignoreLine();
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
void Administrator::modifyBook(std::weak_ptr<BookStock> bookStock, std::weak_ptr<AuthorPool> authorPool) {
	std::string bookTitle;
	bool isBookModifyed{ false };
	std::shared_ptr<BookStock> bookStockShared{ bookStock.lock() };

	do {
		std::cout << "Please, enter the title of the book to modify";
		std::getline(std::cin, bookTitle);
		if (!clearFailedExtraction()) {
			ignoreLine();
		}
		else {
			std::cout << "Failed extraction... this message should never be prompted" << std::endl;
			continue;
		}

		if (bookStockShared) {
			isBookModifyed = bookStockShared.get()->modifyBook(bookTitle, authorPool);
		}
		else {
			throw std::invalid_argument("Cannot modify a book from an empty Pool");
		}
	} while (!isBookModifyed);
}

bool Administrator::selfModify() {
	std::string newUserName{ "" };
	char newUserType{ '\0' };

	std::cout << "Enter new userName (leave empty to keep old name): ";
	std::getline(std::cin, newUserName);

	if (!clearFailedExtraction()) {
		ignoreLine();
	}
	else {
		std::cerr << "Failed extraction... this message should never be prompted" << std::endl;
		return false;
	}

	std::cout << "Enter new userType (leave empty to keep old type), \'A\' or \'R\': ";
	std::cin >> newUserType;
	if (!clearFailedExtraction()) {
		ignoreLine();
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