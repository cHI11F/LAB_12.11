#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_12.11/LAB_12.11.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        // Тест для перевірки додавання книги до бібліотеки
        TEST_METHOD(TestAddBook)
        {
            BinarySearchTree library;
            // Створюємо екземпляр книги, яку додамо до бібліотеки
            Book newBook;
            newBook.udcNumber = 123456;
            newBook.author = "John Doe";
            newBook.title = "The Book Title";
            newBook.year = 2000;
            newBook.quantity = 5;

            // Додаємо книгу до бібліотеки
            library.addBook(newBook.udcNumber, newBook.author, newBook.title, newBook.year, newBook.quantity);

            // Перевіряємо, чи книга дійсно додана, порівнюючи корінь бінарного дерева
            Assert::IsTrue(library.getRoot() != nullptr);
        }

        // Тест для перевірки видалення книги з бібліотеки
        TEST_METHOD(TestDeleteBook)
        {
            BinarySearchTree library;
            // Створюємо екземпляр книги, яку додамо до бібліотеки
            Book newBook;
            newBook.udcNumber = 123456;
            newBook.author = "John Doe";
            newBook.title = "The Book Title";
            newBook.year = 2000;
            newBook.quantity = 5;

            // Додаємо книгу до бібліотеки
            library.addBook(newBook.udcNumber, newBook.author, newBook.title, newBook.year, newBook.quantity);

            // Видаляємо книгу з бібліотеки за роком видання
            library.deleteBook(2000);

            // Перевіряємо, чи книга дійсно видалена, перевіряючи, чи корінь бінарного дерева є нульовим
            Assert::IsFalse(library.getRoot() != nullptr);
        }

        // Тест для перевірки виводу книг за роком видання
        TEST_METHOD(TestPrintBooksByYear)
        {
            BinarySearchTree library;
            // Створюємо кілька екземплярів книг, які додаємо до бібліотеки
            Book book1, book2, book3;
            book1.udcNumber = 123456;
            book1.author = "John Doe";
            book1.title = "The Book Title 1";
            book1.year = 2000;
            book1.quantity = 5;

            book2.udcNumber = 789012;
            book2.author = "Jane Smith";
            book2.title = "The Book Title 2";
            book2.year = 2005;
            book2.quantity = 3;

            book3.udcNumber = 345678;
            book3.author = "Alice Johnson";
            book3.title = "The Book Title 3";
            book3.year = 2010;
            book3.quantity = 7;

            // Додаємо книги до бібліотеки
            library.addBook(book1.udcNumber, book1.author, book1.title, book1.year, book1.quantity);
            library.addBook(book2.udcNumber, book2.author, book2.title, book2.year, book2.quantity);
            library.addBook(book3.udcNumber, book3.author, book3.title, book3.year, book3.quantity);

            // Перевіряємо правильність виводу книг за роком видання
            // Очікуємо, що вивід буде у відповідному порядку: за зростанням року видання
            Assert::ExpectException<exception>([&library] { library.printBooksByYear(); });
        }
    };
}
