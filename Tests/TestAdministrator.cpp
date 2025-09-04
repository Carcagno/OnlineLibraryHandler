#include <iostream>
#include <sstream>


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

class AdministratorTest : public testing::Test {
protected:
	std::shared_ptr<AuthorPool> m_authorPool{};
	std::shared_ptr<AuthorPool> m_authorPool2{};
	std::shared_ptr<BookStock> m_bookStock{};
	std::shared_ptr<UserPool> m_userPool{};
	std::shared_ptr<Administrator> m_a1{};

	AdministratorTest() {
		m_authorPool = AuthorPool::create("PlaceHolder/Path");
		m_authorPool2 = AuthorPool::create("PlaceHolder/Path");
		m_bookStock = std::make_shared<BookStock>("PlaceHolder/Path");
		m_userPool = std::make_shared<UserPool>("PlaceHolder/Path");
		m_a1 = std::make_shared<Administrator>("admin", m_bookStock);


		std::shared_ptr<Author> author(Author::create("John Frutz", m_authorPool2));
	}

	~AdministratorTest() {

	}

};

TEST_F(AdministratorTest, CreateAndDestroy) {
	ASSERT_EQ(m_a1.get()->getUserName(), "admin") << "Admin name not set properly";
	ASSERT_EQ(m_a1.get()->getUserType(), 'A') << "Admin type not set properly";
}

TEST_F(AdministratorTest, GoodCreateUsers) {
	bool isUserCreated{ false };

	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("John\nA\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isUserCreated = m_a1.get()->addUser(m_userPool);
	std::string output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(isUserCreated) << "User Admin was not created properly";

	std::weak_ptr<IUser> user{ m_userPool.get()->getUserFromPool("John") };
	std::shared_ptr<Administrator> adminCreated(dynamic_pointer_cast<Administrator>(user.lock()));
	ASSERT_TRUE(adminCreated) << "Unvalid created User";

	ASSERT_EQ(adminCreated.get()->getUserName(), "John") << "Created admin name not set properly";
	ASSERT_EQ(adminCreated.get()->getUserType(), 'A') << "Created admin type not set properly";
	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, BadCreateUsers) {
	bool isUserCreated{false};

	testing::internal::CaptureStdout();

	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("Jill\nZ\nJohn\nA\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isUserCreated = m_a1.get()->addUser(m_userPool);
	std::string output = testing::internal::GetCapturedStdout();

	ASSERT_FALSE(isUserCreated) << "User Admin was not created properly";
	
	testing::internal::CaptureStdout();
	isUserCreated = m_a1.get()->addUser(m_userPool);
	output = testing::internal::GetCapturedStdout();
	
	ASSERT_TRUE(isUserCreated) << "User Admin was not created properly";

	std::weak_ptr<IUser> user{ m_userPool.get()->getUserFromPool("John") };
	std::shared_ptr<Administrator> adminCreated(dynamic_pointer_cast<Administrator>(user.lock()));
	ASSERT_NE(adminCreated.get()->getUserName(), "Jill") << "Created admin unproperly handle error in input creation";
	ASSERT_NE(adminCreated.get()->getUserType(), 'Z') << "Created admin unproperly handle error in input creation";

	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, DeleteUser) {
	bool isUserDeleted{ false };
	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("John\nA\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	m_a1.get()->addUser(m_userPool);

	std::weak_ptr<IUser> user{ m_userPool.get()->getUserFromPool("John") };
	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	if (true)
	{
		std::shared_ptr<Administrator> adminCreated(dynamic_pointer_cast<Administrator>(user.lock()));
		ASSERT_TRUE(adminCreated) << "Unvalid created User";
	}
	
	testing::internal::CaptureStdout();
	std::stringstream ss2("John\n");
	std::stringbuf* buf2 = ss2.rdbuf();
	std::cin.rdbuf(buf2);

	isUserDeleted = m_a1.get()->deleteUser(m_userPool);

	output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(isUserDeleted, true) << "Created admin was not deleted correctly";
	ASSERT_EQ(m_userPool.get()->isEmpty(), true) << "Created admin was not deleted correctly";
	std::cin.rdbuf(cin_backup);

}

TEST_F(AdministratorTest, ModifyUser) {
	bool isUserModified{ false };
	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("John\nA\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	m_a1.get()->addUser(m_userPool);

	std::weak_ptr<IUser> user{ m_userPool.get()->getUserFromPool("John") };
	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	std::shared_ptr<Administrator> adminCreated(dynamic_pointer_cast<Administrator>(user.lock()));
	ASSERT_TRUE(adminCreated) << "Unvalid created User";

	testing::internal::CaptureStdout();
	std::stringstream ss2("John\nBilly\nR\n");
	std::stringbuf* buf2 = ss2.rdbuf();
	std::cin.rdbuf(buf2);

	isUserModified = m_a1.get()->modifyUser(m_userPool);

	output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(isUserModified) << "Admin was not Modified correctly";

	ASSERT_NE(adminCreated.get()->getUserName(), "John") << "Created admin unproperly handle error in input creation";
	ASSERT_NE(adminCreated.get()->getUserType(), 'A') << "Created admin unproperly handle error in input creation";

	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, CreateAuthor) {
	bool isAuthorCreated{ false };
	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("Georges Orwell\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isAuthorCreated =  m_a1.get()->addAuthor(m_authorPool);

	std::weak_ptr<Author> author{ m_authorPool.get()->getAuthorFromPool("Georges Orwell") };
	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	ASSERT_TRUE(isAuthorCreated) << "Author was not created properly";

	std::shared_ptr<Author> authorCreated((author.lock()));
	ASSERT_TRUE(authorCreated) << "Unvalid created Author";

	ASSERT_EQ(authorCreated.get()->getAuthorName(), "Georges Orwell") << "Created author unproperly created";

	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, DeleteAuthor) {
	bool isAuthorCreated{ false };
	bool isAuthordeleted{ false };


	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("Georges Orwell\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isAuthorCreated = m_a1.get()->addAuthor(m_authorPool);

	std::weak_ptr<Author> author{ m_authorPool.get()->getAuthorFromPool("Georges Orwell") };
	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	ASSERT_TRUE(isAuthorCreated) << "Author was not created properly";
 
	std::shared_ptr<Author> authorCreated((author.lock()));
	ASSERT_TRUE(authorCreated) << "Unvalid created Author";

	ASSERT_EQ(authorCreated.get()->getAuthorName(), "Georges Orwell") << "Created author unproperly created";

	testing::internal::CaptureStdout();
	std::stringstream ss2("Georges Orwell\n");
	std::stringbuf* buf2 = ss2.rdbuf();
	std::cin.rdbuf(buf2);

	isAuthordeleted = m_a1.get()->deleteAuthor(m_authorPool);
	output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(isAuthordeleted) << "Author was not delete properly";

	ASSERT_TRUE(m_authorPool.get()->isEmpty()) << "Author was not deleted properly from the pool";

	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, ModifyAuthor) {
	bool isAuthorCreated{ false };
	bool isAuthorModified{ false };


	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("Georges Orwell\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isAuthorCreated = m_a1.get()->addAuthor(m_authorPool);

	std::weak_ptr<Author> author{ m_authorPool.get()->getAuthorFromPool("Georges Orwell") };
	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	ASSERT_TRUE(isAuthorCreated) << "Author was not created properly";

	std::shared_ptr<Author> authorCreated((author.lock()));
	ASSERT_TRUE(authorCreated) << "Unvalid created Author";

	ASSERT_EQ(authorCreated.get()->getAuthorName(), "Georges Orwell") << "Created author unproperly created";

	testing::internal::CaptureStdout();
	std::stringstream ss2("Georges Orwell\nAnne Boulanger\n");
	std::stringbuf* buf2 = ss2.rdbuf();
	std::cin.rdbuf(buf2);

	isAuthorModified = m_a1.get()->modifyAuthor(m_authorPool);
	output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(isAuthorModified) << "Author was not modified properly";

	std::weak_ptr<Author> authorChanged{ m_authorPool.get()->getAuthorFromPool("Anne Boulanger") };
	std::shared_ptr<Author> authorChangedShared{ authorChanged.lock() };

	ASSERT_TRUE(authorChangedShared) << "Author was not changed properly in the pool";
	ASSERT_EQ(authorChangedShared.get()->getAuthorName(), "Anne Boulanger") << "Author name was not properly changed un the pool";

	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, CreateBook) {
	bool isBookCreated{ false };

	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("The mysterious wall of the earth\nJohn Frutz\n1\n1995");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isBookCreated = m_a1.get()->addBook(m_bookStock, m_authorPool2);

	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	ASSERT_TRUE(isBookCreated) << "Book was not created properly";

	std::shared_ptr<Book> createdBook{m_bookStock.get()->getBookFromStock("The mysterious wall of the earth")};

	ASSERT_TRUE(createdBook) << "Created Book not valid";

	EXPECT_EQ(createdBook.get()->getAuthor().lock().get()->getAuthorName(), "John Frutz") << "Created book has wrong author";
	EXPECT_EQ(createdBook.get()->getCategory(), static_cast<Book::bookCategory>(1)) << "Created book has wrong category";
	EXPECT_EQ(createdBook.get()->getPublicationDate(), 1995) << "Created book has wrong publicationDate";
}

TEST_F(AdministratorTest, DeleteBook) {
	bool isBookCreated{ false };
	bool isBookDeleted{ false };
	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("The mysterious wall of the earth\nJohn Frutz\n1\n1995");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isBookCreated = m_a1.get()->addBook(m_bookStock, m_authorPool2);

	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	ASSERT_TRUE(isBookCreated) << "Book was not created properly";

	std::shared_ptr<Book> createdBook{ m_bookStock.get()->getBookFromStock("The mysterious wall of the earth") };

	ASSERT_TRUE(createdBook) << "Created Book not valid";

	testing::internal::CaptureStdout();
	std::stringstream ss2("The mysterious wall of the earth\n");
	std::stringbuf* buf2 = ss2.rdbuf();
	std::cin.rdbuf(buf2);

	isBookDeleted = m_a1.get()->deleteBook(m_bookStock);
	output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(isBookDeleted) << "Book was not correctly deleted";
	ASSERT_TRUE(m_bookStock.get()->isStockEmpty());

	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, ModifyBook) {
	bool isBookCreated{ false };
	bool isBookModified{ false };
	bool isAuthorCreated{ false };

	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("The mysterious wall of the earth\nJohn Frutz\n1\n1995");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	isBookCreated = m_a1.get()->addBook(m_bookStock, m_authorPool2);

	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	ASSERT_TRUE(isBookCreated) << "Book was not created properly";

	std::shared_ptr<Book> createdBook{ m_bookStock.get()->getBookFromStock("The mysterious wall of the earth") };

	ASSERT_TRUE(createdBook) << "Created Book not valid";

	testing::internal::CaptureStdout();
	std::stringstream ss3("Tolstoi\n");
	std::stringbuf* buf3 = ss3.rdbuf();
	std::cin.rdbuf(buf3);

	isAuthorCreated = m_a1.get()->addAuthor(m_authorPool2);

	std::weak_ptr<Author> author{ m_authorPool2.get()->getAuthorFromPool("Tolstoi") };
	output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	ASSERT_TRUE(isAuthorCreated) << "Author was not created properly";

	testing::internal::CaptureStdout();
	std::stringstream ss2("The mysterious wall of the earth\nWar and peace\nTolstoi\n4\n1845");
	std::stringbuf* buf2 = ss2.rdbuf();
	std::cin.rdbuf(buf2);

	isBookModified = m_a1.get()->modifyBook(m_bookStock, m_authorPool2);
	output = testing::internal::GetCapturedStdout();

	ASSERT_TRUE(isBookModified) << "Book was not correctly Modified";

	std::shared_ptr<Book> bookShared{ m_bookStock.get()->getBookFromStock("War and peace").lock()};

	ASSERT_TRUE(bookShared) << "The book that was modified is impossible to find in the book stock. Either not modified, corrupted or deleted by mistake";
	EXPECT_EQ(bookShared.get()->getAuthor().lock().get()->getAuthorName(), "Tolstoi") << "Modified book has wrong author";
	EXPECT_EQ(bookShared.get()->getCategory(), static_cast<Book::bookCategory>(4)) << "Modified book has wrong category";
	EXPECT_EQ(bookShared.get()->getPublicationDate(), 1845) << "Modified book has wrong publicationDate";

	std::cin.rdbuf(cin_backup);
}

