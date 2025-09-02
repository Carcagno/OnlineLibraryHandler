#include <iostream>
#include <sstream>


#include "pch.h"

#include "../OnlineLibraryHandler/Reader.cpp"
#include "../OnlineLibraryHandler/Administrator.cpp"
#include "../OnlineLibraryHandler/Author.cpp"
#include "../OnlineLibraryHandler/Book.cpp"
#include "../OnlineLibraryHandler/UserPool.cpp"
#include "../OnlineLibraryHandler/BookStock.cpp"
#include "../OnlineLibraryHandler/AuthorPool.cpp"
#include "../OnlineLibraryHandler/Utils.cpp"

class AuthorPool;

TEST(AdminTest, CreateAndDestroy) {
	std::shared_ptr<AuthorPool> authorPool{ AuthorPool::create("PlaceHolder/Path") };
	std::shared_ptr<BookStock> bookStock{ std::make_shared<BookStock>("PlaceHolder/Path") };
	std::shared_ptr<UserPool> userPool{ std::make_shared<UserPool>("PlaceHolder/Path") };
	std::shared_ptr<Administrator> a1{ std::make_shared<Administrator>("admin", bookStock) };
		

	ASSERT_EQ(a1.get()->getUserName(), "admin") << "Admin name not set properly";
	ASSERT_EQ(a1.get()->getUserType(), 'A') << "Admin type not set properly";
}

TEST(AdminTest, GoodCreateUsers) {
	testing::internal::CaptureStdout();
	std::streambuf* cin_backup = std::cin.rdbuf();

	std::shared_ptr<AuthorPool> authorPool{ AuthorPool::create("PlaceHolder/Path") };
	std::shared_ptr<BookStock> bookStock{ std::make_shared<BookStock>("PlaceHolder/Path") };
	std::shared_ptr<UserPool> userPool{ std::make_shared<UserPool>("PlaceHolder/Path") };
	std::shared_ptr<Administrator> a1{ std::make_shared<Administrator>("admin", bookStock) };

	std::stringstream ss("John\nA\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	a1.get()->addUser(userPool);
	std::string output = testing::internal::GetCapturedStdout();

	std::weak_ptr<IUser> user{ userPool.get()->getUserFromPool("John") };
	std::shared_ptr<Administrator> adminCreated(dynamic_pointer_cast<Administrator>(user.lock()));
	ASSERT_TRUE(adminCreated) << "Unvalid created User";

	ASSERT_EQ(adminCreated.get()->getUserName(), "John") << "Created admin name not set properly";
	ASSERT_EQ(adminCreated.get()->getUserType(), 'A') << "Created admin type not set properly";
	std::cin.rdbuf(cin_backup);
}

TEST(AdminTest, BadCreateUsers) {
	testing::internal::CaptureStdout();

	std::streambuf* cin_backup = std::cin.rdbuf();

	std::shared_ptr<AuthorPool> authorPool{ AuthorPool::create("PlaceHolder/Path") };
	std::shared_ptr<BookStock> bookStock{ std::make_shared<BookStock>("PlaceHolder/Path") };
	std::shared_ptr<UserPool> userPool{ std::make_shared<UserPool>("PlaceHolder/Path") };
	std::shared_ptr<Administrator> a1{ std::make_shared<Administrator>("admin", bookStock) };

	std::stringstream ss("Jill\nZ\nJohn\nA\n");
	std::stringbuf* buf = ss.rdbuf();
	std::cin.rdbuf(buf);

	a1.get()->addUser(userPool);
	std::string output = testing::internal::GetCapturedStdout();

	std::weak_ptr<IUser> user{ userPool.get()->getUserFromPool("John") };
	std::shared_ptr<Administrator> adminCreated(dynamic_pointer_cast<Administrator>(user.lock()));
	ASSERT_NE(adminCreated.get()->getUserName(), "Jill") << "Created admin unproperly handle error in input creation";
	ASSERT_NE(adminCreated.get()->getUserType(), 'Z') << "Created admin unproperly handle error in input creation";

	std::cin.rdbuf(cin_backup);
}