#pragma once

#include "Book.hpp"

namespace library {

// Абстракція сервісу сповіщень (DIP, OCP, ISP)
class INotificationService {
public:
    virtual ~INotificationService() = default;
    virtual void notifyNewBook(const Book& book) = 0;
};

} // namespace library
