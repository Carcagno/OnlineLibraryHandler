#include "Administrator.h"

//CTOR
Administrator::Administrator(const std::string& AdministratorName):
IUser{AdministratorName, 'A'} {

}

//MISC
void Administrator::cleanUserForDelete() {
	//No specific clean to do a this time. Mayberin future evolutions
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

	userPool.addUser(tmpPtrUser);
}

void Administrator::deleteUser(UserPool& userPool) {
	bool isUserDeleted{ false };

	do {
		std::string userName{};

		// to be refined - cin security valid input
		std::cout << "Please, enter the name of the user to delete";
		std::cin >> userName;
		
		//to be refined - call to UserPool delete user

		//isUserDeleted = userPool.deleteUser(userName);

	} while (!isUserDeleted);
}

void Administrator::modifyUser(UserPool& userPool) {
	std::string userName{};

	// to be refined - cin security valid input
	std::cout << "Please, enter the name of the user to modify" << std::endl;
	std::cin >> userName;

	//to be refined - call to UserPool getUserPointer
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
	}
}

void Administrator::displayUser() {
	IUser::displayUser();
	 
	std::cout << "Administrator" << std::endl;
}

void Administrator::showUser(const UserPool& userPool) {
	
	//to be refined - call to UserPool displayUser
	//userPool.displayUser(this->m_userName);
}

	//author handling
void Administrator::addAuthor(AuthorPool& authorPool) {
	std::shared_ptr<Author> tmpAuthorPtr{};
	std::string authorName{};

	// to be refined - cin security valid input
	std::cout << "Please, enter the name of the new author";
	std::cin >> authorName;

	//to be refined - call to AuthorPool addAuthor

	//tmpAuthorPtr = std::make_shared<Author>(Author{ authorName });

	//authorPool.addAuthor(tmpAuthorPtr);
}

void Administrator::deleteAuthor(AuthorPool& authorPool) {
	std::string authorName{};

	// to be refined - cin security valid input
	std::cout << "Please, enter the name of the author to delete";
	std::cin >> authorName;
	
	//to be refined - call to AuthorPool deleteAuthor
	//authorPool.deleteAuthor(authorName);

}

void Administrator::modifyAuthor(AuthorPool& authorPool) {
	std::string authorName{};

	// to be refined - cin security valid input
	std::cout << "Please, enter the name of the author to modify";
	std::cin >> authorName;

	//to be refined - call to AuthorPool modifyAuthor
}

	//book handling
void Administrator::addBook(BookStock& bookStock, AuthorPool& authorPool) {
	std::string bookTitle{};
	std::weak_ptr<Author> author{};
	std::string authorName{};
	//to be refined - creation of the enum
	//bookCategory category
	int publicationDate;
	std::shared_ptr<Book> book{};

	// to be refined - cin security valid input
	std::cout << "Please, enter the title of the book to add";
	std::cin >> bookTitle;

	// to be refined - cin security valid input
	std::cout << "Please, enter the name of the author for this book";
	std::cin >> authorName;

	//to be refined - wrong author name
	// to be refined - searchAuthor authorPool
	//author = authorPool.searchAuthor(authorName)

	//to be refined - enum
	//std::cout << "Please ented the book category number:\n1. Sci-Fi\n2. Classi\n3. Autobiography\n4. Roman\n5. Fantasy\n6. Thriller\n7. Essay\n\nChoice: ";
	//std::cin >> category;

	// to be refined - cin security valid input
	std::cout << "Please, enter the year of publication (YYYY) of the book: ";
	std::cin >> publicationDate;


	//to be refined - implem Book
	//book = std::make_shared<Book>(Book{ bookTitle, author, category, publicationDate });

}

void Administrator::deleteBook(BookStock& bookStock) {
	std::string bookTitle{};

	// to be refined - cin security valid input
	std::cout << "Please, enter the title of the book to delete";
	std::cin >> bookTitle;

	// to be refined - deleteBook bookStock
	//bookStock.deleteBook(bookTitle);
}

void Administrator::modifyBook(BookStock& bookStock) {
	std::string bookTitle;

	// to be refined - cin security valid input
	std::cout << "Please, enter the title of the book to modify";
	std::cin >> bookTitle;

	//to be refined - call to bookStock modifyBook
	//bookStock.modifyBook();
}

void Administrator::selfModify() {
	std::string newUserName{""};
	char newUserType{ '\0' };
	
	std::cout << "Enter new userName (leave empty to keep old name): ";
	std::cin >> newUserName;

	std::cout << "Enter new userType (leave empty to keep old type), \'A\' or \'R\': ";
	std::cin >> newUserType;

	if (newUserName != "" && newUserName != "\n" && !(newUserName.empty())) {
		m_userName = newUserName;
	}

	if (newUserType != '\0' && newUserType != '\n') {
		m_userType = newUserType;
	}

	std::cout << "User has been modifyed. New user informations:\n" << std::endl;
	this->displayUser();
}