#pragma once

#include "IBookPrinter.hpp"
#include "IBookRepository.hpp"
#include "INotificationService.hpp"

namespace library {

// Координатор бібліотеки: залежить лише від абстракцій (DIP) і має єдину відповідальність (SRP)
class Library {
private:
    IBookRepository& repository_;
    INotificationService& notifier_;
    IBookPrinter& printer_;

public:
    Library(IBookRepository& repository,
            INotificationService& notifier,
            IBookPrinter& printer) noexcept
        : repository_(repository), notifier_(notifier), printer_(printer) {}

    void addBook(const Book& book);
    void displayBooks() const;
    std::vector<Book> getBooks() const;
};

} // namespace library
