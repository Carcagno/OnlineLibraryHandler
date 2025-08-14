# General Technical Specifications

## 1. Context & Introduction

The project is a terminal-based library manager. It is a showcase project designed to demonstrate my mastery of `C++`.  
The goal is to provide a high-quality product as an example of good development practices.  
The intended usage scenario is for fictional library managers (`Administrator`) and library users (`Reader`).

There are already many real-world projects that manage libraries. The purpose here is **not** to surpass existing products, but solely to create and deliver a professional-looking showcase application.

---

## 2. Goals

The main goal of the project is to provide a **terminal-based** library management system that supports all core operations related to managing books in a library.

**Examples of supported operations:**
- Add a book (with details such as `authorName`, `title`, `publicationDate`, etc.)
- Find a book (by `authorName` or `title`)
- Remove a book or multiple books (by `title` or by `authorName`)
- Add a user (`Administrator` or `Reader`)
- Borrow a book
- Return a book

In a fictional scenario where no similar software exists and all operations are performed manually, such a system would significantly simplify library management, saving both time and paperwork.

---

## 3. General Description

This software is a **terminal-based library management system** without a graphical user interface.  
It is designed to provide simple features — some already listed in [2. Goals](#2-goals).

By typing basic text commands with the right arguments, and depending on the type of the logged-in user, the following categories of features will be available:

### 1) Administrators
This type of user can perform all "administrative" tasks, including:
- User management commands (`createUser`, `deleteUser`, `modifyUser`, etc.)
- Book management commands (`createBook`, `deleteBook`, `modifyBook`, update `title`, `authorName`, `category`, etc.)
- Author management commands (`createAuthor`, `deleteAuthor`, `modifyAuthor`, etc.)

### 2) Readers
This type of user can:
- Borrow a book
- Return a book

### 3) Common
Both `Administrator` and `Reader` users have access to:
- Search for a book by `title` (displays its availability)
- Search for an author by `authorName` (displays all their books)

---

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

---

## 5. Use Cases

Describes the main usage scenarios of the software.

**Examples:**
- A user searches for a book by `title`
- An `Administrator` deletes an author

---

## 6. Constraints

**Technical:**  
- Programming language: `C++` (modern version, specified standard)  
- Target OS: defined during development  
- Possible dependencies: to be confirmed during design phase

**Functional:**  
- Text-based UI with focus on ergonomics  
- Secure handling of user and book data  
- Fast execution for common operations

**Organizational:**  
- Deadlines to be set according to project scope  
- Budget: N/A — personal project  
- Responsibilities: single developer

---

## 7. Acceptance & Quality Criteria

Defines the quality benchmarks for considering the project complete:
- Successful execution of defined features
- Basic automated or manual testing
- Robustness against invalid inputs
- Adequate documentation of code and usage

---

## 8. Deliverables

- Complete `C++` source code  
- Documentation (technical and user guide)  
- Test files and execution examples  

---

## 9. Glossary (optional)

**`userName`** – Unique identifier for a user.  
**`userType`** – Type of the user (`A` = Administrator, `R` = Reader).  
**`authorName`** – Name of a book's author.  
**`title`** – Book title.  
**`category`** – Book category or genre.  
**`publicationDate`** – Book’s publication date.

---

## 10. Annexes (optional)

- Additional diagrams  
- Early prototypes or sketches  
- References
