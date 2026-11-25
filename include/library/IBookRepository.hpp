#pragma once

#include "Book.hpp"
#include <vector>

namespace library {

// Абстракція сховища книг (DIP, ISP)
class IBookRepository {
public:
    virtual ~IBookRepository() = default;
    virtual void save(const Book& book) = 0;
    virtual std::vector<Book> findAll() const = 0;
};

} // namespace library
