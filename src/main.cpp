#include "../tests/MiniTest.hpp"
#include "gilded_rose/GildedRose.hpp"
#include "library/Book.hpp"
#include "library/IBookPrinter.hpp"
#include "library/InMemoryBookRepository.hpp"
#include "library/Library.hpp"
#include "library/NotificationServices.hpp"

#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    std::cout << "====================================================================\n";
    std::cout << " Лабораторна робота №9: Рефакторинг програмного коду та принципи SOLID\n";
    std::cout << "====================================================================\n";

    // 1. Демонстрація рефакторингу системи управління бібліотекою
    std::cout << "\n--- Частина 1: Система управління бібліотекою (SOLID) ---\n";
    {
        using namespace library;
        InMemoryBookRepository repo;
        EmailNotificationService emailNotifier;
        ConsoleBookPrinter printer;

        Library library(repo, emailNotifier, printer);
        library.addBook(Book("The Catcher in the Rye", "J.D. Salinger"));
        library.addBook(Book("To Kill a Mockingbird", "Harper Lee"));

        std::cout << "\nСписок книг у бібліотеці:\n";
        library.displayBooks();

        // Демонстрація підміни реалізації сповіщень (DIP + OCP) без зміни Library
        std::cout << "\nПідміна сервісу сповіщень на SMS (без зміни коду Library):\n";
        SmsNotificationService smsNotifier;
        Library smsLibrary(repo, smsNotifier, printer);
        smsLibrary.addBook(Book("1984", "George Orwell"));
    }

    // 2. Демонстрація Gilded Rose Kata + розширення Conjured
    std::cout << "\n--- Частина 2: Gilded Rose Kata + розширення Conjured ---\n";
    {
        using namespace gilded_rose;
        std::vector<Item> items = {
            Item("+5 Dexterity Vest", 10, 20),
            Item("Aged Brie", 2, 0),
            Item("Sulfuras, Hand of Ragnaros", 0, 80),
            Item("Backstage passes to a TAFKAL80ETC concert", 6, 20),
            Item("Conjured Mana Cake", 3, 12)
        };

        GildedRose app(items);
        for (int day = 0; day <= 2; ++day) {
            std::cout << "\nДень " << day << " (Назва, SellIn, Quality):\n";
            for (const auto& item : items) {
                std::cout << "  " << item << '\n';
            }
            app.updateQuality();
        }
    }

    // 3. Запуск модульних тестів
    return minitest::runAllTests();
}
