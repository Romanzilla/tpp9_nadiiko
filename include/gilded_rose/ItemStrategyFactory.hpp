#pragma once

#include "IItemUpdateStrategy.hpp"
#include "Item.hpp"
#include <memory>

namespace gilded_rose {

// Фабрика вибору стратегії за типом товару (SRP: ізоляція правил класифікації товарів)
class ItemStrategyFactory {
public:
    static std::unique_ptr<IItemUpdateStrategy> createFor(const Item& item);
};

} // namespace gilded_rose
