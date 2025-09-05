#pragma once
#include "pch.h"

#include "../OnlineLibraryHandler/Reader.h"
#include "../OnlineLibraryHandler/Administrator.h"
#include "../OnlineLibraryHandler/Author.h"
#include "../OnlineLibraryHandler/Book.h"
#include "../OnlineLibraryHandler/UserPool.h"
#include "../OnlineLibraryHandler/BookStock.h"
#include "../OnlineLibraryHandler/AuthorPool.h"
#include "../OnlineLibraryHandler/Utils.h"

class AuthorPool;

class ReaderTest : public testing::Test {
protected:
	std::shared_ptr<AuthorPool> m_authorPool{};
	std::shared_ptr<BookStock> m_bookStock{};
	std::shared_ptr<UserPool> m_userPool{};
	std::shared_ptr<Administrator> m_a1{};
	std::shared_ptr<Reader> m_r1{};

	ReaderTest() {
		m_authorPool = AuthorPool::create("PlaceHolder/Path");
		m_bookStock = std::make_shared<BookStock>("PlaceHolder/Path");
		m_userPool = std::make_shared<UserPool>("PlaceHolder/Path");
		m_a1 = std::make_shared<Administrator>("admin", m_bookStock);
		m_r1 = std::make_shared<Reader>("reader", m_bookStock);

		std::shared_ptr<Author> author(Author::create("John Frutz", m_authorPool));
		std::shared_ptr<Book> book(Book::create("The yellow bridge", author, Book::bookCategory::Thriller, 1998, m_bookStock));
	}

	~ReaderTest() {

	}

};


TEST_F(ReaderTest, CreateAndDestroy) {
	ASSERT_EQ(m_r1.get()->getUserName(), "reader") << "Reader name not set properly";
	ASSERT_EQ(m_r1.get()->getUserType(), static_cast<IUser::UserType>('R')) << "Reader type not set properly";
}

TEST_F(ReaderTest, BorrowAndGiveBackBook) {
	bool isBookBorrowed{ false };
	bool isBookGivenBack{ false };
	
	testing::internal::CaptureStdout();
	isBookBorrowed = m_r1.get()->borrowBook("The yellow bridge");

	ASSERT_TRUE(isBookBorrowed) << "The book wasn't borrowed properly";

	auto book{ m_bookStock.get()->getBookFromStock("The yellow bridge") };

	EXPECT_TRUE(book.lock().get()->getIsBorrowed()) << "The book wasn't set as borrowed in the pool";

	isBookGivenBack = m_r1.get()->giveBackBook("The yellow bridge");

	ASSERT_TRUE(isBookGivenBack) << "The book wasn't given back properly";

	EXPECT_FALSE(book.lock().get()->getIsBorrowed()) << "The book wasn't set as not borrowed in the pool";
	std::string output = testing::internal::GetCapturedStdout();

}
