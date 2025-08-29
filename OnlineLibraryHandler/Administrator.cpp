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
void Administrator::addUser(std::weak_ptr<UserPool> userPool) {
	std::string userName{};
	char userType{};
	std::shared_ptr<IUser> tmpPtrUser;
	bool isUserAdded{ false };
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };


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
			Administrator tmp{ userName, m_bookStock };
			tmpPtrUser = std::make_shared<Administrator>(tmp);
		}
		else {
			Reader tmp{ userName, m_bookStock };
			tmpPtrUser = std::make_shared<Reader>(tmp);
		}


		if (userPoolShared) {
			isUserAdded = userPoolShared.get()->addUser(tmpPtrUser);
		}
		else {
			throw std::invalid_argument("Cannot add an user to an inaccessible Pool.");
		}

	} while (!isUserAdded);
}

void Administrator::deleteUser(std::weak_ptr<UserPool> userPool) {
	bool isUserDeleted{ false };
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };

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

		if (userPoolShared) {
			isUserDeleted = userPoolShared.get()->deleteUser(userName);
		}
		else {
			throw std::invalid_argument("Cannot delete an user from an inaccessible Pool.");
		}

	} while (!isUserDeleted);
}

void Administrator::modifyUser(std::weak_ptr<UserPool> userPool) {
	std::string userName{};
	bool isModifyed{ false };
	std::shared_ptr<UserPool> userPoolShared{ userPool.lock() };

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


		if (userPoolShared) {
			std::weak_ptr<IUser> userWeak{ userPoolShared.get()->getUserFromPool(userName)};
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
		}
		else {
			throw std::invalid_argument("Cannot modify an user from an inaccessible Pool.");
		}


	} while (!isModifyed);
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
void Administrator::modifyAuthor(std::weak_ptr<AuthorPool> authorPool) {
	std::string authorName{};
	bool isAuthorModifyed{ false };
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };

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
		if (authorPoolShared) {
			isAuthorModifyed = authorPoolShared.get()->modifyAuthor(authorName);
		}
		else {
			throw std::invalid_argument("Cannot modify an author from an empty Pool.");
		}
	} while (!isAuthorModifyed);
}

	//book handling
void Administrator::modifyBook(std::weak_ptr<BookStock> bookStock, std::weak_ptr<AuthorPool> authorPool) {
	std::string bookTitle;
	bool isBookModifyed{ false };
	std::shared_ptr<BookStock> bookStockShared{ bookStock.lock() };
	std::shared_ptr<AuthorPool> authorPoolShared{ authorPool.lock() };

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