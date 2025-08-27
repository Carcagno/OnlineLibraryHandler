#include "authorPool.h"

AuthorPool::AuthorPool(const std::string& authorFilePath): 
	m_authorsFilePath{} {
	//  to be refined - should create an empty author for books ?
}

AuthorPool::~AuthorPool() {
	//to be refined - saving operation in file
	// to be refined - should exclude empty author in the save file, because default created ?
}

std::weak_ptr<Author> AuthorPool::getAuthorFromPool(const std::string& authorName) {
	for (auto it{ m_authors.begin() }; it != m_authors.end(); ++it) {
		if (it->get()->getAuthorName() == authorName) {
			return std::weak_ptr<Author>{*it };
		}
	}
	return std::weak_ptr<Author>{};
}

bool AuthorPool::addAuthor(std::shared_ptr<Author> authorName) {
	if (authorName) {
		m_authors.push_back(authorName);
		return true;
	}

	std::cerr << "Cannot add empty Author. AuthorPool was left untouched." << std::endl;
	return false;
}

bool AuthorPool::deleteAuthor(const std::string& authorName) {
	for (auto it{ m_authors.begin() }; it != m_authors.end(); ++it) {
		if (it->get()->getAuthorName() == authorName) {
			m_authors.erase(it);
			return true;
		}
	}

	std::cerr << "Could'nt find any author \"" << authorName << "\" to delete. Author pool was left untouched." << std::endl;
	return false;
}

bool AuthorPool::modifyAuthor(const std::string& authorName) { // to be refined - The pool should maybe not be responsible of the modification. SelfModify in AUthor ?
	for (auto it{ m_authors.begin() }; it != m_authors.end(); ++it) {
		if (it->get()->getAuthorName() == authorName) {
			std::string newAuthorName{};

			std::cout << "Please, provide a new name for the author \"" << authorName << "\": ";
			//to be refined - cin error & validation
			std::cin >> newAuthorName;

			it->get()->setAuthorName(newAuthorName);
			return true;
		}
	}

	std::cerr << "Could'nt find any author \"" << authorName << "\" to modify. Author pool was left untouched." << std::endl;
	return false;
}

void AuthorPool::printAllAuthors() const {
	std::cout << "\t\t\t==================== Authors ====================\n" << std::endl;

	for (auto it{ m_authors.begin() }; it != m_authors.end(); ++it) {
		it->get()->printAuthor();
	}
}
