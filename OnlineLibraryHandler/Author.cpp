#include "Author.h"

//CTOR - Private to avoid direct creation because of the shared_ptr & filling of AuthorPool 
Author::Author(const std::string& authorName, std::shared_ptr<AuthorPool> authorPool):
	m_authorName{ authorName },
	m_authorPool{ authorPool } {
}

std::shared_ptr<Author> Author::create(const std::string& authorName, std::shared_ptr<AuthorPool> authorPool) {
	std::shared_ptr<Author> authorShared{ std::shared_ptr<Author>(new Author(authorName, authorPool)) };

	if (authorPool) {
		authorPool.get()->addAuthor(authorShared);
	}
	else {
		throw std::invalid_argument("Invalid authorPool during the creation of the author. Aborting creation of the Author ...");
	}
	return authorShared;
}

Author::~Author() {
	std::shared_ptr<AuthorPool> authorPoolShared{ m_authorPool.lock() };
	
	SetAllAuthorBooksToNone();

	if (authorPoolShared) {
		authorPoolShared.get()->deleteAuthor(m_authorName);
	}
}


void Author::SetAllAuthorBooksToNone() {
	for (std::weak_ptr<Book> book : m_books) {
		std::shared_ptr<Book> bookShared{ book.lock()};

		if (bookShared) {
			bookShared->resetAuthor();
		}
		else {
			//std::cerr << "Warning: An invalid author may remain in a book in the authorPool in an invalid state." << std::endl;
			//The failure of the deletion could be normal, considering the fact that, at the end of the program, everything is destructed in the reverse order of creation. 
			//No needs to show an error message to the user, but could be interesting to have a log file, with those warning displayed.
		}

	}
}

void Author::setAuthorName(const std::string& authorName) {
	if (authorName != "") {
		m_authorName = authorName;
	}
}

std::string Author::getAuthorName() const {
	return m_authorName;
}

void Author::printAuthor() const{
	std::cout << "\t\t\t==================== " << m_authorName << " ====================" << std::endl;
	//If any informations is added into author, can be updated to be prompt.
}

bool Author::deleteBookFromAuthor(const std::string& bookTitle) {

	for (auto it{ m_books.begin() }; it != m_books.end(); ++it) {
		std::shared_ptr<Book> book{ it->lock() };

		if (book) {
			if (book->getTitle() == bookTitle) {
				m_books.erase(it);
				return true;
			}
		}
		else {
			//std::cerr << "Warning: An invalid book is referenced in this author in an invalid state and can't be deleted." << std::endl;
			//The failure of the deletion could be normal, considering the fact that, at the end of the program, everything is destructed in the reverse order of creation. 
			//No needs to show an error message to the user, but could be interesting to have a log file, with those warning displayed.			
		}
	}
	//std::cerr << "Warning: An invalid book is referenced in this author in an invalid state and can't be deleted." << std::endl;
	//The failure of the deletion could be normal, considering the fact that, at the end of the program, everything is destructed in the reverse order of creation. 
	//No needs to show an error message to the user, but could be interesting to have a log file, with those warning displayed.			
	//std::cout << "The book \"" << bookTitle << "\" could'nt be found, and not be deleted." << std::endl;
	
	//to be refined - Maybe there is a solution to detect real issues, without triggering this at the exit of main()?

	return false;
}

void Author::addBookToAuthor(std::weak_ptr<Book> book) {
	m_books.push_back(book);
}

bool Author::selfModify() {
	std::string newAuthorName{};
	bool isAuthorNameChanged{ false };

	do {
		std::cout << "Please, provide a new name for the author \"" << this->m_authorName << "\": ";
		//to be refined - cin error & validation
		std::cin >> newAuthorName;
		if (!clearFailedExtraction()) {
			ignoreLine();
			m_authorName = newAuthorName;
		}
		else {
			std::cout << "Failed extraction ... Retrying to get user input!" << std::endl;
			continue;
		}

	} while (!isAuthorNameChanged);

	return true;
}