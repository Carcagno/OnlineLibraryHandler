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
	std::shared_ptr<BookStock> m_bookStock{};
	std::shared_ptr<UserPool> m_userPool{};
	std::shared_ptr<Administrator> m_a1{};

	AdministratorTest() {
		m_authorPool = AuthorPool::create("PlaceHolder/Path");
		m_bookStock = std::make_shared<BookStock>("PlaceHolder/Path");
		m_userPool = std::make_shared<UserPool>("PlaceHolder/Path");
		m_a1 = std::make_shared<Administrator>("admin", m_bookStock);
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

	std::stringstream ss("Georges Orwell");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	m_a1.get()->addAuthor(m_authorPool);

	std::weak_ptr<Author> author{ m_authorPool.get()->getAuthorFromPool("Georges Orwell") };
	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	std::shared_ptr<Author> authorCreated((author.lock()));
	ASSERT_TRUE(authorCreated) << "Unvalid created Author";

	ASSERT_EQ(authorCreated.get()->getAuthorName(), "Georges Orwell") << "Created author unproperly created";

	std::cin.rdbuf(cin_backup);
}

TEST_F(AdministratorTest, DeleteAuthor) {
	bool isAuthorCreated{ false };
	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::stringstream ss("Georges Orwell");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	m_a1.get()->addAuthor(m_authorPool);

	std::weak_ptr<Author> author{ m_authorPool.get()->getAuthorFromPool("Georges Orwell") };
	std::string output = testing::internal::GetCapturedStdout();
	std::cin.rdbuf(cin_backup);

	std::shared_ptr<Author> authorCreated((author.lock()));
	ASSERT_TRUE(authorCreated) << "Unvalid created Author";

	ASSERT_EQ(authorCreated.get()->getAuthorName(), "Georges Orwell") << "Created author unproperly created";

	std::cin.rdbuf(cin_backup);
}

