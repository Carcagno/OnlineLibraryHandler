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

## 4. Features List

### 1) Login  
**Command:** *None* — user enters their `userName` at startup.  
Allows any user to log in to the system and access commands according to their role.

### 2) Administrator - Create Account  
**Command:** `createUser`  
Creates a new `Administrator` or `Reader` account by specifying `userName` and `userType` (`A` or `R`). Restricted to `Administrator`.

### 3) Administrator - Delete Account  
**Command:** `deleteUser`  
Deletes an existing user account identified by `userName`. Restricted to `Administrator`.

### 4) Administrator - Modify Account  
**Command:** `modifyUser`  
Updates account details (`userName`, `userType`). Restricted to `Administrator`.

### 5) Administrator - Show User Info  
**Command:** `showUser`  
Displays information about a given account (`userName`, `userType`, borrowed books if `Reader`). Restricted to `Administrator`.

### 6) Administrator - Create Author  
**Command:** `createAuthor`  
Adds a new author to the system by specifying `authorName`. Restricted to `Administrator`.

### 7) Administrator - Delete Author  
**Command:** `deleteAuthor`  
Removes an author from the system using `authorName`. Restricted to `Administrator`.

### 8) Administrator - Modify Author  
**Command:** `modifyAuthor`  
Updates the `authorName` of an existing author. Restricted to `Administrator`.

### 9) Administrator - Create Book  
**Command:** `createBook`  
Adds a new book to the library with `title`, `authorName`, `category`, and `publicationDate`. Restricted to `Administrator`.

### 10) Administrator - Delete Book  
**Command:** `deleteBook`  
Removes a book from the library by `title`. Restricted to `Administrator`.

### 11) Administrator - Modify Book  
**Command:** `modifyBook`  
Updates details of an existing book (`title`, `authorName`, `category`, `publicationDate`). Restricted to `Administrator`.

### 12) Reader - Borrow Book  
**Command:** `borrowBook`  
Allows a `Reader` to borrow a book by specifying its `title` if available.

### 13) Reader - Return Book  
**Command:** `giveBackBook`  
Allows a `Reader` to return a previously borrowed book by `title`.

### 14) Reader - Display Own Information  
**Command:** `displayMe`  
Displays the `Reader`’s own account details (`userName`, `userType`, number of borrowed books, list of borrowed books).

### 15) Common - Search Book  
**Command:** `searchBook`  
Searches for a book by `title` and displays its details (`title`, `authorName`, `category`, `publicationDate`, availability).

### 16) Common - Search Author  
**Command:** `searchAuthor`  
Searches for an author by `authorName` and lists their books with details (`title`, `category`, `publicationDate`, availability).

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

