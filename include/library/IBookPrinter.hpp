#pragma once

#include "Book.hpp"
#include <iostream>
#include <vector>

namespace library {

// Абстракція відображення списку книг (SRP, ISP)
class IBookPrinter {
public:
    virtual ~IBookPrinter() = default;
    virtual void printBooks(const std::vector<Book>& books) const = 0;
};

// Консольна реалізація виведення книг
class ConsoleBookPrinter : public IBookPrinter {
public:
    void printBooks(const std::vector<Book>& books) const override {
        for (const auto& book : books) {
            std::cout << "Title: " << book.getTitle()
                      << ", Author: " << book.getAuthor() << '\n';
        }
    }
};

} // namespace library
