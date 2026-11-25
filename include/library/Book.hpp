#pragma once

#include <stdexcept>
#include <string>
#include <utility>

namespace library {

// Сутність предметної області: інкапсулює дані книги та відповідає лише за її стан (SRP)
class Book {
private:
    std::string title_;
    std::string author_;

public:
    Book(std::string title, std::string author)
        : title_(std::move(title)), author_(std::move(author)) {
        if (title_.empty()) {
            throw std::invalid_argument("Назва книги не може бути порожньою");
        }
        if (author_.empty()) {
            throw std::invalid_argument("Ім'я автора не може бути порожнім");
        }
    }

    const std::string& getTitle() const noexcept { return title_; }
    const std::string& getAuthor() const noexcept { return author_; }

    bool operator==(const Book& other) const noexcept {
        return title_ == other.title_ && author_ == other.author_;
    }
};

} // namespace library
