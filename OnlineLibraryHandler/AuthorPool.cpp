#include "authorPool.h"

//CTOR - Private to avoid direct creation because of the shared_ptr & selfFilling with default empty author
AuthorPool::AuthorPool(const std::string& authorFilePath): 
	m_authorsFilePath{} {
}

std::shared_ptr<AuthorPool> AuthorPool::create(const std::string& authorFilePath) {
	std::shared_ptr<AuthorPool> authorPoolShared{ std::shared_ptr<AuthorPool>(new AuthorPool(authorFilePath)) };
	
	
	std::shared_ptr<Author> emptyAuthor{ Author::create("Unknow", authorPoolShared) };
	
	authorPoolShared->addAuthor(emptyAuthor);


	return authorPoolShared;
}

//DTOR
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

bool AuthorPool::modifyAuthor(const std::string& authorName) {
	for (auto it{ m_authors.begin() }; it != m_authors.end(); ++it) {
		if (it->get()->getAuthorName() == authorName) {
			return it->get()->selfModify();
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
