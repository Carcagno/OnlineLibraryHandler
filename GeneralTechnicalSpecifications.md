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
This type user will be allowed to type the command to handle every "administrative" tasks of the library:  
    - All users related command (create, delete, etc.).  
    - All Book creations, modifications and removal commands (Add a book, delete a book, change title, change author name, change category, etc.).  
    - All author creations, modifications and removal commands (AddAuthor, delete, change, etc.).  


<h3>2) Readers</h3>
This type of user is allowed to perform simple tasks to basically borrow and give back a book with appropriates commands.

<h3>3) Common</h3>
Both previous users will have some commands available in common:
    - Search book (by title). This will display the availability of the book.
    - Search author (by authorName). This will display all the book written by the author.


<h2 name="FeaturesList">4. FeaturesList</h2>

<h3>1) Login</h3>
Command: None (Should only enter his name).

The user must be able to login with his name. This will be ask directly by the application everytime she will be launched.

<h3>2) Administrator - create account</h3>
Command: createUser 

If the user is an administrator, he must be able to create account of both types: Administrator & Reader. For this, the connected administrator will need to type "createUser". It will then be asked to him:
    - userName
    - userType \[A | R\] 

A message will be prompt to confirm if the user creation will be successfull.

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.
    
<h3>3) Administrator - delete an account</h3>
Command: deleteUser 

If the user is an administrator, he must be able to delete account of both types: Administrator & Reader. For this, the connected administrator will need to type "deleteUser". It will then be asked to him:
    - The userName he wants to delete
  
If the entered username exists, it must be deleted, and a confirmation message of the successful deletion must be prompted. Otherwise, an error message must be prompted (telling the user if the name was not an existing user, or if the user could'nt be deleted for any exterior reason).

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>4) Administrator - show user info</h3>
Command: showUser 

If the user is an administrator, he must be able to show the user info of both types: Administrator and Reader. For this, the connected administrator will need to type "showUser". It will then be asked to him:
    - The userName to show 

If the user exists, all the informations about the user must be prompted to him:
    - The userName
    - The userType (Administrator or Reader)
    - If reader:
        - The borrowedBookCount
        - The borrowedBookList
Otherwise, an error message must be prompted (telling the user if the name was not an existing user, or if the user info could'nt be prompted for any exterior reason). 

If a reader tries to enter this command, an error message telling him that he does not have the right to use this command must be prompted.

<h3>5) Administrator - Create author</h3>

<h3>6) Administrator - Delete author</h3>

<h3>7) Administrator - Modify author</h3>

<h3>8) Administrator - Create book</h3>

<h3>9) Administrator - Delete book</h3>

<h3>10) Administrator - Modify book</h3>

<h3>11) Reader - Borrow book</h3>

<h3>12) Reader - Give back book</h3>

<h3>13) Reader - Display me</h3>

<h3>14) Common - Search book</h3>

<h3>15) Common - Search author</h3>


Fonctionnalités principales : celles qui sont indispensables.

Fonctionnalités secondaires : bonus, nice-to-have, évolutions possibles.

Pour chaque fonctionnalité, détaille le comportement attendu (exemple : « Ajouter un livre » : champs requis, format attendu, etc).

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

