<h1 style="text-align: center;">general technical specifications</h1>


<h2 name="ContextAndIntroductionLink">1. Context & introduction</h2>

The project is a terminal based library manager. It is only a showcase project to show my mastering of the C++. The goal here is to provide a good quality product. The usage which is considered for the project is for fictives library managers (administrators) & library users (readers).

There are, beyond a shadow of a doubt, real projects already used in real library. The goal here is not to have a better product than those existing products, but to only create and provide a showcase product.


<h2 name="GoalsLink">2. Goals</h2>

The main goal of the project is to provide a terminal based library manager which allows to manage every operations in a library regarding the handling of the books. For example: add a book (with information like author, title, publication date, etc.), find a book (by author, by title), remove a book, or books (by title, by author, to delete all the books of the author), add an user (administrator, reader), borrow a book, give back a book, etc.

In a fictive world, where there are no similar software existing, and where all those task are handled manually, such project would be created to ease the management of a library, and would make a very important gain of time and paper.


<h2 name="GeneralDescriptionLink">3. General description</h2>

This software beeing a library management system, based on terminal, and which does not provide a graphical interface, it should provide simple features, as already non-exhaustively listed in the [2. Goals](#GoalsLink) section. By providing simple text command and appropriates arguments, and based on the type of the user making those operations, some basic features will be provided. 

There will be 2 categories of users:  
<h3>1) Administrators</h3>

This type of user will be allowed to type the command to handle every "administrative" task of the library:
<ul>
    <li> All users related command (create, delete, etc.).</li>
    <li> All Book creations, modifications and removal commands (Add a book, delete a book, change title, change author name, change category, etc.).</li>
    <li> All author creations, modifications and removal commands (AddAuthor, delete, change, etc.).</li>
</ul>
<h3>2) Readers</h3>
<ul>
    <li> This type of user is allowed to perform simple tasks to basically borrow and give back a book with appropriates commands.</li>
</ul>
<h3>3) Common</h3>
Both previous users will have some commands available in common:
<ul>
    <li> Search book (by title). This will display the availability of the book.</li>
    <li> Search author (by authorName). This will display all the book written by the author.</li>
</ul>

<h2 name="FeaturesList">4. FeaturesList</h2>

<h3>1) Login</h3>
**Command: None** (Should only enter his name) </br>

The user must be able to login with his name. This will be ask directly by the application everytime she will be launched.

<h3>2) Administrator - create account</h3>
**Command: createUser** </br>

If the user is an administrator, he must be able to create account of both types: Administrator & Reader. For this, the connected administrator will need to type "createUser". It will then be asked to him:

<ul> <li> userName</li> <li> userType \$$A | R\$$</li> </ul>
A message will be prompt to confirm if the user creation will be successfull.

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>3) Administrator - delete an account</h3>
**Command: deleteUser** </br>

If the user is an administrator, he must be able to delete account of both types: Administrator & Reader. For this, the connected administrator will need to type "deleteUser". It will then be asked to him:

<ul> <li> The userName he wants to delete</li> </ul>
If the entered username exists, it must be deleted, and a confirmation message of the successful deletion must be prompted. Otherwise, an error message must be prompted (telling the user if the name was not an existing user, or if the user could'nt be deleted for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>4) Administrator - modify account</h3>
**Command: modifyUser** </br>

If the user is an administrator, he must be able to modify the information of an existing account of both types: Administrator & Reader. For this, the connected administrator will need to type "modifyUser". It will then be asked to him:

<ul> <li> The userName of the account to modify </li> <li> The new userName (leave empty if unchanged) </li> <li> The new userType \$$A | R\$$ (leave empty if unchanged) </li> </ul>
If the modification is successful, the account's information should be updated according to the provided details, and a confirmation message of the successful modification must be prompted.

Otherwise, an error message must be prompted (telling the user if the account does not exist, or if the information could not be updated for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>5) Administrator - show user info</h3>
**Command: showUser** </br>

If the user is an administrator, he must be able to show the user info of both types: Administrator and Reader. For this, the connected administrator will need to type "showUser". It will then be asked to him:

<ul> <li> The userName to show </li> </ul>
If the user exists, all the informations about the user must be prompted to him:

<ul> <li> The userName</li> <li>- The userType (Administrator or Reader)</li> <li>- If reader:</li> <ul> <li>- The borrowedBookCount</li> <li>- The borrowedBookList</li> </ul> </ul>
Otherwise, an error message must be prompted (telling the user if the name was not an existing user, or if the user info could'nt be prompted for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>6) Administrator - Create author</h3>
**Command: createAuthor** </br>

If the user is an administrator, he must be able to create a new author. For this, the connected administrator will need to type "createAuthor". It will then be asked to him:

<ul> <li> The name of the author </li> </ul>
If the creation of the author is successfull, the author should be created, and a confirmation message of the successful creation must be prompted.

Otherwise, an error message must be prompted (telling the user if the author was already existing, or if the author could'nt be created for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>7) Administrator - Delete author</h3>
**Command: deleteAuthor** </br>

If the user is an administrator, he must be able to delete an author. For this, the connected administrator will need to type "deleteAuthor". It will then be asked to him:

<ul> <li> The name of the author to delete </li> </ul>
If the deletion of the author is successfull, the author should be deleted, and a confirmation message of the successful deletion must be prompted.

Otherwise, an error message must be prompted (telling the user if the author was not existing, or if the author could'nt be deleted for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>8) Administrator - Modify author</h3>
**Command: modifyAuthor** </br>

If the user is an administrator, he must be able to modify an existing author. For this, the connected administrator will need to type "modifyAuthor". It will then be asked to him:

<ul> <li> The old name of the author </li> <li> The new name of the author </li> </ul>
If the modification of the author is successfull, the author should be modified according to the informations given by the administrator, and a confirmation message of the successful modification must be prompted.

Otherwise, an error message must be prompted (telling the user if the author was not existing, or if the author could'nt be modified for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>9) Administrator - Create book</h3>
**Command: createBook** </br>

If the user is an administrator, he must be able to create a new book in the library. For this, the connected administrator will need to type "createBook". It will then be asked to him:

<ul> <li> The title of the book </li> <li> The name of the author </li> <li> The category of the book </li> <li> The publication date </li> </ul>
If the creation of the book is successful, the book should be added to the library with the provided information, and a confirmation message of the successful creation must be prompted.

Otherwise, an error message must be prompted (telling the user if the book was already existing, if the given author does not exist in the system, or if the book could not be created for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>10) Administrator - Delete book</h3>
**Command: deleteBook** </br>

If the user is an administrator, he must be able to delete an existing book from the library. For this, the connected administrator will need to type "deleteBook". It will then be asked to him:

<ul> <li> The title of the book to delete </li> </ul>
If the deletion of the book is successful, the book should be removed from the library database, and a confirmation message of the successful deletion must be prompted.

Otherwise, an error message must be prompted (telling the user if the book was not existing, or if the book could not be deleted for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>11) Administrator - Modify book</h3>
**Command: modifyBook** </br>

If the user is an administrator, he must be able to modify an existing book in the library. For this, the connected administrator will need to type "modifyBook". It will then be asked to him:

<ul> <li> The title of the book to modify </li> <li> The name of the author of the book (leave empty if unchanged) </li> <li> The new title of the book (leave empty if unchanged)</li> <li> The new category (leave empty if unchanged)</li> <li> The new publication date (leave empty if unchanged)</li> </ul>
If the modification of the book is successful, the book’s details should be updated with the provided information, and a confirmation message of the successful modification must be prompted.

Otherwise, an error message must be prompted (telling the user if the book was not existing, or if the book could not be modified for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>12) Reader - Borrow book</h3>
**Command: borrowBook** </br>

If the user is a reader, he must be able to borrow a book from the library. For this, the connected reader will need to type "borrowBook". It will then be asked to him:

<ul> <li> The title of the book to borrow </li> </ul>
If the book exists in the system and is available, it should be assigned to the reader, the availability status of the book should be updated, and a confirmation message of the successful borrowing must be prompted.

Otherwise, an error message must be prompted (telling the user if the book does not exist, if the book is already borrowed by another user, or if the borrowing could not be processed for any exterior reason).

If an administrator tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>13) Reader - Give back book</h3>
**Command: giveBackBook** </br>

If the user is a reader, he must be able to give back a book he has previously borrowed from the library. For this, the connected reader will need to type "giveBackBook". It will then be asked to him:

<ul> <li> The title of the book to give back </li> </ul>
If the book exists in the system and is currently borrowed by the reader, it should be marked as available again, removed from the reader’s borrowed books list, and a confirmation message of the successful return must be prompted.

Otherwise, an error message must be prompted (telling the user if the book does not exist, if the book was not borrowed by this user, or if the return could not be processed for any exterior reason).

If an administrator tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>14) Reader - Display me</h3>
**Command: displayMe** </br>

If the user is a reader, he must be able to display his own account information. For this, the connected reader will need to type "displayMe".

The application should then display:

<ul> <li> The userName </li> <li> The userType (Reader) </li> <li> The borrowedBookCount </li> <li> The borrowedBookList </li> </ul>
If the information can be successfully retrieved, it must be displayed to the reader along with a confirmation message indicating that the operation was successful.

Otherwise, an error message must be prompted (telling the user if his account information could not be retrieved for any exterior reason).

If an administrator tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>15) Common - Search book</h3>
**Command: searchBook** </br>

Both administrators and readers must be able to search for a book in the library. For this, the connected user will need to type "searchBook". It will then be asked to him:

<ul> <li> The title of the book to search </li> </ul>
If the book exists in the system, its details must be displayed, including:

<ul> <li> The title of the book </li> <li> The name of the author </li> <li> The category of the book </li> <li> The publication date </li> <li> The availability status (available or borrowed) </li> </ul>
If the book does not exist, an error message must be prompted indicating that no book with the given title was found.

<h3>16) Common - Search author</h3>
**Command: searchAuthor** </br>

Both administrators and readers must be able to search for an author in the library. For this, the connected user will need to type "searchAuthor". It will then be asked to him:

<ul> <li> The name of the author to search </li> </ul>
If the author exists in the system, the application must display:

<ul> <li> The name of the author </li> <li> The list of all books written by the author </li> <li> For each book: title, category, publication date, and availability status (available or borrowed) </li> </ul>
If the author does not exist, an error message must be prompted indicating that no author with the given name was found.

5. Cas d’utilisation (use cases)
Décris les principaux scénarios d’utilisation du logiciel.

Exemple : « Un utilisateur recherche un livre par titre », « Un administrateur supprime un auteur », etc.

6. Contraintes
Techniques : langage (C++ version moderne, standard utilisé…), OS cible, dépendances éventuelles, etc.

Fonctionnelles : ergonomie, sécurité des données, performance minimale…

Organisationnelles : délai, budget, responsabilités des intervenants.

7. Critères de réception et de qualité
Quels sont les critères d’acceptation pour considérer le projet comme réussi ?

Tests attendus, degré d’automatisation, robustesse, documentation…

8. Livrables
Liste précise des éléments attendus en fin de projet (code source, documentation, schémas, fichiers de tests…).

9. Glossaire (optionnel)
Définitions de termes spécifiques utilisés dans le CDC.

10. Annexes (optionnel)
Documents complémentaires, schémas préliminaires, références…

