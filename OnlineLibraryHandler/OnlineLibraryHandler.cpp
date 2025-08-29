#include <iostream>
#include <vector>
#include <memory>

#include "Reader.h"
#include "Administrator.h"
#include "Author.h"
#include "Book.h"
#include "UserPool.h"
#include "BookStock.h"
#include "AuthorPool.h"

int main()
{
    std::shared_ptr<AuthorPool> authorPool{ AuthorPool::create("PlaceHolder/Path") };
    std::shared_ptr<BookStock> bookStock{ std::make_shared<BookStock>("PlaceHolder/Path") };
    std::shared_ptr<UserPool> userPool{ std::make_shared<UserPool>("PlaceHolder/Path") };
    std::shared_ptr<IUser> activeUser{ std::make_shared<Administrator>("Kevin", bookStock) };
    
    if (1 == 1) {
        std::shared_ptr<Author> aut1{ Author::create("Jean Valjean", authorPool) };

        std::shared_ptr<Book> b1{ Book::create("Alice", aut1, Book::bookCategory::Classic, 1894, bookStock) };
    }

    bookStock.get()->printAllBooks();

    authorPool.get()->printAllAuthors();

    bookStock.get()->deleteBook("Alice");

    authorPool.get()->deleteAuthor("Jean Valjean");

    bookStock.get()->printAllBooks();

    authorPool.get()->printAllAuthors();
    
    userPool.get()->displayAllUsers();


    return 0;
}
