#include <iostream>
#include <vector>
#include <memory>

#include "IUser.h"
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
    std::shared_ptr<IUser> activeUser{ std::make_shared<Administrator>("admin", bookStock) };
    //std::shared_ptr<IUser> activeUser{ std::make_shared<Reader>("reader", bookStock) };


    //to be refined - Add a basic login feature to setup activeUser

    std::cout << "You are now logged as: " << std::endl;
    activeUser.get()->displayUser();

    activeUser.get()->selfExecute(authorPool, bookStock, userPool);
 
    return 0;
}
