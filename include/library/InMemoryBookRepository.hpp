#pragma once

#include "IBookRepository.hpp"
#include <vector>

namespace library {

// Реалізація сховища в оперативній пам'яті (зручно для роботи та незалежного тестування)
class InMemoryBookRepository : public IBookRepository {
private:
    std::vector<Book> storage_;

public:
    void save(const Book& book) override {
        storage_.push_back(book);
    }

    std::vector<Book> findAll() const override {
        return storage_;
    }
};

} // namespace library
