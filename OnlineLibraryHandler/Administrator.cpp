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
			Administrator tmp{ userName, m_bookStock };
			tmpPtrUser = std::make_shared<Administrator>(tmp);
		}
		else {
			Reader tmp{ userName, m_bookStock };
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