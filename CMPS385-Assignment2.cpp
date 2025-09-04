/*
CMPS 385 - Data Structures (Fall 2025)
Assignment 2: Library Book Management System
Aditya Singh
Program purpose:
- Add a new book with auto-generated 5-digit ID
- Borrow/Return by ID
- Display details by ID
- List all available books
- Exit

Problem 2: Create a simple Library book
Management System Using Classes
*/

#include <iostream>
#include <string> 
#include <iomanip>
#include <cstdlib> // rand/srand
#include <ctime>
#include <limits> // clearLine
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    int year;
    bool available; // true = available, false = borrowed

public:
    //Default Constructor
    Book();
    // Constructor Declaration
    Book(int _id, string t, string a, int y, bool _available);

    // methods
    void display();
    void borrowBook();
    void returnBook();

    // getters
    int getId();
    string getTitle();
    string getAuthor();
    int getYear();
    bool isAvailable();
};

// Default constructor definition
Book::Book() {
    id = 0;
    title = "";
    author = "";
    year = 0;
    available = true;
}


// Constructor definition outside of class
Book::Book(int _id, string t, string a, int y, bool _available) {
    id = _id;
    title = t;
    author = a;
    year = y;
    available = _available;
}

int Book::getId() { return id; }
string Book::getTitle() { return title; }
string Book::getAuthor() { return author; }
int Book::getYear() { return year; }
bool Book::isAvailable() { return available; }

void Book::display() {
    cout << "ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Year: " << year << endl;

    cout << "Status: ";
    if (available) {
        cout << "Available\n";
    }
    else {
        cout << "Borrowed\n";
    }

}

void Book::borrowBook() {
    if (available == true) {
        available = false;
        cout << "You have borrowed this book " << title << endl;
    }
    else {
        cout << "Sorry This book " << title << " is already being borrowed \n";
    }
}

void Book::returnBook() {
    if (available == false) {
        available = true;
        cout << "You returned " << title << endl;
    }
    else {
        cout << "This book is available nobody has borrowed it\n";
    }
}

// Array for books, increments by 1, max 100
Book libraryArray[100];
int bookCount = 0;

// clears leftover lines before getline occurs
void clearLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// checks whether id exists already
bool IDExists(int id) {
    for (int i = 0; i < bookCount; ++i) {
        if (libraryArray[i].getId() == id)
        return true;
    }
    return false;
}

// generate a unique 5-digit ID
int generateUniqueID() {
    int id;
    do {
        id = 10000 + rand() % 90000; // 10,000-99,999
    } while (IDExists(id));
    return id;
}

// find array index by ID (or -1)
int findIndexById(int id) {
    for (int i = 0; i < bookCount; ++i) {
        if (libraryArray[i].getId() == id)
        return i;
    }
    return -1;
}

// 1) Add a new book
void addBook() {
    if (bookCount >= 100) {
        cout << "MAXIMUM counts only 100 you have reached it. Cannot ADD BOOK!!!!\n";
        return;
    }

    string title, author;
    int year;

    cout << "ENTER title of book!";
    clearLine();
    getline(cin, title);

    cout << "ENTER author of book!\n";
    getline(cin, author);

    cout << "ENTER year of book!\n";
    cin >> year;
    if (!cin) { cin.clear(); clearLine(); cout << "Invalid year.\n"; return; }

    int id = generateUniqueID();
    Book b(id, title, author, year, true);

    libraryArray[bookCount] = b;
    bookCount++;

    cout << "Book added successfully!\n";
    cout << "Title: " << title << "\n";
    cout << "ID: " << id << "\n";
}

// 2) Borrow a book
void borrowBookById() {
    cout << "Enter ID OF BOOK YOU ARE TRYING TO BORROW\n";
    int id; cin >> id;

    int index = findIndexById(id);
    if (index == -1) {
        cout << "book does not exist cannot be found\n";
        return;
    }

    if (libraryArray[index].isAvailable()) {
        libraryArray[index].borrowBook();
        cout << "YOU HAVE SUCESSFULLY BORROWED \n"
            << libraryArray[index].getTitle() << endl;
    }
    else {
        cout << "Sorrythat book is currently not available.\n";
    }
}

// 3) Return a book
void returnBookById() {
    cout << "Enter Book ID: \n";
    int id;
    cin >> id;

    int index = findIndexById(id);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    if (!libraryArray[index].isAvailable()) {
        libraryArray[index].returnBook();
        cout << "You have successfully returned ! \n"
            << libraryArray[index].getTitle() << endl;
    }
    else {
        cout << "THIS book was not borrowed.\n";
    }
}

// 4) Display details of a book (by ID)
void displayBookById() {
    cout << "Enter Book ID: \n";
    int id;
    cin >> id;

    int index = findIndexById(id);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    libraryArray[index].display();
}

// 5) List all available books
void listAvailableBooks() {
    bool found = false;
    cout << "Available Books:\n";
    for (int i = 0; i < bookCount; ++i) {
        if (libraryArray[i].isAvailable()) {
            found = true;
            cout << "ID:  " << libraryArray[i].getId()
                << " |Title:  " << libraryArray[i].getTitle()
                << " |Author:  " << libraryArray[i].getAuthor()
                << " |Year:  " << libraryArray[i].getYear() << "\n";
        }
    }
    if (!found) {
        cout << "There are no books available at the moment.\n";
    }

}

int main() {
    srand(static_cast<unsigned>(time(0)));//used to generate ID more Randomly

    while (true) {
        cout << "******** Welcome to the Library ********\n";
        cout << " Please choose one of the following options 1-6 Below\n";
        cout << "1.Add A New Book\n";
        cout << "2.Borrow a Book\n";
        cout << "3.Return a Book\n";
        cout << "4.Display Details of a book (By ID)\n";
        cout << "5.List all available books\n";
        cout << "6.Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (!cin) { cin.clear(); clearLine(); cout << "Invalid choice.\n"; continue; }

        if (choice == 1) addBook();
        else if (choice == 2) borrowBookById();
        else if (choice == 3) returnBookById();
        else if (choice == 4) displayBookById();
        else if (choice == 5) listAvailableBooks();
        else if (choice == 6) {
            cout << "Thank you for using the Library System!";
            return 0;
        }
        else {
            cout << "Invalid Choice please choose a number between 1-6\n";
        }
    }
}
