#include "Book.h"

Book::Book(const std::string& title, std::weak_ptr<Author> author, bookCategory category, int publicationDate) :
	m_title{ title },
	m_author{ author },
	m_category{ category},
	m_publicationDate{ publicationDate },
	m_isBorrowed{ false } {
	std::shared_ptr<Author> authorShared{ m_author.lock() };

	// The book should add himself into the bookstock to tighten his presence in the stock with is creation / destruction, to ensure that, while he exists, he can be found in the stock.
	//to be refined - add book to the bookStock ?!
	
	// the book, once created, and given the fact that the author is already created, must add himself to the author.
	if (authorShared) {
		std::weak_ptr<Book> bookWeak{}; // To be refined - get the weakptr from the BookStock ?!

		authorShared->addBookToAuthor(bookWeak);
	}
}

Book::~Book() {
	deleteThisBookInAuthor();
	// to be refined - delete book in bookstock
}


void Book::setTitle(const std::string& title) {
	if (title != "") {
		m_title = title;
	}
}

void Book::setAuthor(std::weak_ptr<Author> author) {
	if (author.lock()) {
		m_author = author;
	}
	else {
		//to be refined - handle exception
	}
}

void Book::setCategory(const bookCategory category) {
	m_category = category;
}

void Book::setPublicationDate(const int publicationDate) {
	m_publicationDate = publicationDate;
}

void Book::setIsBorrowed(const bool isBorrowed) {
	m_isBorrowed = isBorrowed;
}

std::string Book::getTitle() const {
	return m_title;
}

std::weak_ptr<Author> Book::getAuthor() const {
	return m_author;
}

Book::bookCategory Book::getCategory() const {
	return m_category;
}

int Book::getPublicationDate() const {
	return m_publicationDate;
}

bool Book::getIsBorrowed() const {
	return m_isBorrowed;
}

void Book::deleteThisBookInAuthor() {
	std::shared_ptr<Author> author{ m_author.lock() };
	
	if (!author) {
		//Author = None / Unknown. No need to delete the book in any author book
		return;
	}

	if (!(author->deleteBookFromAuthor(m_title))) {
		// to be refined - exception handling
	}
}

void Book::printCategory() const {
	std::cout << "Category: ";

	switch (m_category)
	{
	case Book::bookCategory::Autobiography:
		std::cout << "Autobiography";
		break;
	case Book::bookCategory::Classic:
		std::cout << "Classic";
		break;
	case Book::bookCategory::Essay:
		std::cout << "Essay";
		break;
	case Book::bookCategory::Fantasy:
		std::cout << "Fantasy";
		break;
	case Book::bookCategory::Roman:
		std::cout << "Roman";
		break;
	case Book::bookCategory::SciFi:
		std::cout << "SciFi";
		break;
	case Book::bookCategory::Thriller:
		std::cout << "Thriller";
		break;
	default:
		std::cout << "None";
		break;
	}
	
	std::cout << std::endl;
}


void Book::printBook() const {
	std::shared_ptr<Author> author{ m_author.lock()};


	std::cout << "\n\t\t\t->->->->->->->->->->->-> " << m_title << " <-<-<-<-<-<-<-<-<-<-<-<-\n" 
		<< "Author info: " << std::endl;
	
	if (author) {
		author->printAuthor();
	}
	else {
		std::cout << "Author unknown" << std::endl;
	}
	printCategory();
	
	std::cout << "Publication Date: " << m_publicationDate << std::endl;
	std::cout << "Book borrowing status: ";
	
	if (m_isBorrowed) {
		std::cout << "Borrowed";
	}
	else {
		std::cout << "Available";
	}

	std::cout << std::endl;
}

void Book::printAllAvailableCategory() {
	std::cout << "Available categories: \n1. SciFi\n2. Classic\n3. Autobiography\n4. Roman\n5. Fantasy\n6. Thriller\n7.	Essay" << std::endl;
}

void Book::modifyBook(AuthorPool &authorPool) {
	std::string title{""};
	std::string authorName{""};
	int category{ -1 };
	int publicationDate{ -9999 };

	std::cout << "Actual title: " << m_title << "\nEnter new title (leave empty to keep old title): ";
	std::cin >> title;

	if (title != "" && title != "\n") {
		m_title = title;
	}

	std::shared_ptr<Author> author{ m_author.lock() };
	if (author) {
		std::cout << "Actual author: " << author->getAuthorName() << "\nEnter new author name (leave empty to keep old author): ";
		std::cin >> authorName;

		if (authorName != "" && authorName != "\n") {
			std::shared_ptr<Author> author{ authorPool.getAuthorFromPool(authorName).lock() };
			if (author) {
				m_author = author;
			}
			else {
				std::cout << "Invalid author name. Old author name left untouched. Please, retry to modifyBook again if you want to change the author" << std::endl;
			}
		}
	}
	else {
		std::cout << "Actual author: Unknown" << std::endl;
	}
	
	std::cout << "Actual book category: ";
	printCategory();
	std::cout << "Enter the new category number (leave empty to keep old category):\n ";
	printAllAvailableCategory();

	std::cin >> category;

	if (category >= 0 && category < bookCategory::defaultValue) {
		m_category = static_cast<bookCategory>(category);
	}
	else {
		std::cout << "Invalid category. Old category left untouched. Please, retry to modifyBook again if you want to change the category" << std::endl;
	}

	std::cout << "Actual publication date: " << m_publicationDate << "\nEnter new publication date (leave empty to keep old publication date): ";
	std::cin >> publicationDate;

	if (publicationDate != -1) {
		m_publicationDate = publicationDate;
	}
	
	std::cout << "Book updated. Updated book: " << std::endl;
	printBook();
}

void Book::resetAuthor() {
	this->m_author.reset();
}