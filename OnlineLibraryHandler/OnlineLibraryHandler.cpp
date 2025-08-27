#include <iostream>
#include <vector>
#include <memory>

#include "Reader.h"
#include "Administrator.h"
#include "Author.h"
#include "Book.h"

int main()
{
    Reader r1{ "Jose"};
    Reader r2{ "Polo"};

    Administrator a1{"Don"};
    Administrator a2{ "Bill" };

    std::vector<std::shared_ptr<IUser>> userVect{std::make_shared<Reader>(r1), std::make_shared<Reader>(r2), std::make_shared<Administrator>(a1), std::make_shared<Administrator>(a2) };

    r1.displayUser();
    r2.displayUser();

    a1.displayUser();
    a2.displayUser();

    std::cout << "\n=====vect=====" << std::endl;
    for (std::shared_ptr<IUser> user : userVect) {
        if (user->getUserType() == 'A') {
            std::shared_ptr<Administrator> tmpA { std::dynamic_pointer_cast<Administrator>(user) };

            tmpA.get()->displayUser();
        }
        else {
            std::shared_ptr<Reader> tmpR{ std::dynamic_pointer_cast<Reader>(user) };

            tmpR.get()->displayUser();
        }
    }

    std::shared_ptr<Author> aut1{ std::make_shared<Author>("Jean Valjean") };
    std::shared_ptr<Book> b1{ std::make_shared<Book>("Alice", aut1, Book::bookCategory::Classic, 1894) };

    aut1->printAuthor();
    b1->printBook();

    return 0;
}
