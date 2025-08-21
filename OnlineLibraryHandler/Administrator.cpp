#include "Administrator.h"

//CTOR
Administrator::Administrator(const std::string& AdministratorName):
IUser{AdministratorName, 'A'} {

}

//MISC
void Administrator::cleanUserForDelete() {
	return;
}

	//user handling
void Administrator::addUser(UserPool& userPool) {
	std::string userName{};
	char userType{};
	std::shared_ptr<IUser> tmpPtrUser;

	// to be refined - cin security valid input
	std::cout << "Please, enter the informations of the new user:\n" << "UserName: ";
	std::cin >> userName;

	// to be refined - cin security valid input
	std::cout << "\n userType ( A || R ): ";
	std::cin >> userType;

	// to be refined - way to DRY ?
	if (userType == 'A') {
		Administrator tmp{ userName};
		tmpPtrUser =  std::make_shared<Administrator>(tmp);
	}
	else {
		Reader tmp{ userName };
		tmpPtrUser = std::make_shared<Reader>(tmp);
	}

	//to be refined - call to UserPool create user

	//userPool.addUser(tmpPtrUser);
}

void Administrator::deleteUser(UserPool& userPool) {
	bool isUserDeleted{ false };

	do {
		std::string userName{};
		std::cout << "Please, enter the name of the user to delete";
		std::cin >> userName;
		
		//to be refined - call to UserPool delete user

		//isUserDeleted = userPool.deleteUser(userName);

	} while (!isUserDeleted);
}

void Administrator::modifyUser(UserPool& userPool) {

}

void Administrator::displayUser() {
	IUser::displayUser();
	 
	std::cout << "Administrator" << std::endl;
}

void Administrator::showUser(UserPool& userPool) {

}

	//author handling
void Administrator::addAuthor() {

}

void Administrator::deleteAuthor() {

}

void Administrator::modifyAuthor() {

}

	//book handling
void Administrator::addBook() {

}

void Administrator::deleteBook() {

}

void Administrator::modifyBook() {

}
