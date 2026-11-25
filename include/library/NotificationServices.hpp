#pragma once

#include "INotificationService.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace library {

// Конкретна реалізація сповіщень електронною поштою
class EmailNotificationService : public INotificationService {
public:
    void notifyNewBook(const Book& book) override {
        std::cout << "[Email] Надіслано сповіщення про нову книгу: \""
                  << book.getTitle() << "\" (" << book.getAuthor() << ")\n";
    }
};

// Додаткова реалізація сповіщень через SMS (демонстрація дотримання OCP без зміни Library)
class SmsNotificationService : public INotificationService {
public:
    void notifyNewBook(const Book& book) override {
        std::cout << "[SMS] Нове надходження до бібліотеки: \""
                  << book.getTitle() << "\"\n";
    }
};

// Тестовий дублер (Spy/Mock) для перевірки викликів сповіщень у модульних тестах
class SpyNotificationService : public INotificationService {
private:
    std::vector<std::string> sentTitles_;

public:
    void notifyNewBook(const Book& book) override {
        sentTitles_.push_back(book.getTitle());
    }

    const std::vector<std::string>& getSentTitles() const noexcept {
        return sentTitles_;
    }
};

} // namespace library
