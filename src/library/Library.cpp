#include "library/Library.hpp"

namespace library {

void Library::addBook(const Book& book) {
    repository_.save(book);
    notifier_.notifyNewBook(book);
}

void Library::displayBooks() const {
    printer_.printBooks(repository_.findAll());
}

std::vector<Book> Library::getBooks() const {
    return repository_.findAll();
}

} // namespace library
