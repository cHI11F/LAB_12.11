#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Book {
    int udcNumber;
    string author;
    string title;
    int year;
    int quantity;
    Book* left;
    Book* right;
};

class BinarySearchTree {
private:
    Book* root;

    Book* createBook(int udcNumber, const string& author, const string& title, int year, int quantity) {
        Book* newBook = new Book;
        newBook->udcNumber = udcNumber;
        newBook->author = author;
        newBook->title = title;
        newBook->year = year;
        newBook->quantity = quantity;
        newBook->left = nullptr;
        newBook->right = nullptr;
        return newBook;
    }

    Book* addBook(Book* root, Book* newBook) {
        if (root == nullptr) {
            return newBook;
        }
        if (newBook->year < root->year) {
            root->left = addBook(root->left, newBook);
        }
        else if (newBook->year > root->year) {
            root->right = addBook(root->right, newBook);
        }
        else {
            cout << "Error: Book with the same year already exists." << endl;
        }
        return root;
    }

    Book* deleteBook(Book* root, int year) {
        if (root == nullptr) {
            return root;
        }
        if (year < root->year) {
            root->left = deleteBook(root->left, year);
        }
        else if (year > root->year) {
            root->right = deleteBook(root->right, year);
        }
        else {
            if (root->left == nullptr) {
                Book* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Book* temp = root->left;
                delete root;
                return temp;
            }
            Book* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->year = temp->year;
            root->right = deleteBook(root->right, temp->year);
        }
        return root;
    }

    void printBooksByYear(Book* root) {
        if (root != nullptr) {
            printBooksByYear(root->left);
            cout << "Year: " << root->year << ", Title: " << root->title << ", Author: " << root->author << ", Quantity: " << root->quantity << endl;
            printBooksByYear(root->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void addBook(int udcNumber, const string& author, const string& title, int year, int quantity) {
        root = addBook(root, createBook(udcNumber, author, title, year, quantity));
    }

    void deleteBook(int year) {
        root = deleteBook(root, year);
    }

    void printBooksByYear() {
        cout << "Books in the library sorted by year of publication:" << endl;
        printBooksByYear(root);
    }

    void loadBooksFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file." << endl;
            return;
        }

        int udcNumber, year, quantity;
        string author, title;

        while (file >> udcNumber >> author >> title >> year >> quantity) {
            addBook(udcNumber, author, title, year, quantity);
        }

        file.close();
    }
};

int main() {
    BinarySearchTree library;
    string filename;

    cout << "Enter the path to the text file containing book records: ";
    getline(cin, filename);

    library.loadBooksFromFile(filename);

    int choice;
    do {
        cout << "\nLibrary Management System Menu:\n"
            << "1. Add a book\n"
            << "2. Remove a book\n"
            << "3. Print books sorted by year\n"
            << "4. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        // Очистка флагів помилок та буфера вводу
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            int udcNumber, year, quantity;
            string author, title;
            cout << "Enter UDC number, author, title, year, and quantity of the book: ";
            cin >> udcNumber >> author >> title >> year >> quantity;

            // Очистка флагів помилок та буфера вводу
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            library.addBook(udcNumber, author, title, year, quantity);
            break;
        }
        case 2: {
            int year;
            cout << "Enter the year of the book to remove: ";
            cin >> year;

            // Очистка флагів помилок та буфера вводу
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            library.deleteBook(year);
            break;
        }
        case 3:
            library.printBooksByYear();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
