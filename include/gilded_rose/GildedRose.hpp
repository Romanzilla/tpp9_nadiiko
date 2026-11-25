#pragma once

#include "Item.hpp"
#include <vector>

namespace gilded_rose {

// Збережено публічний інтерфейс GildedRose для повної сумісності з Kata
class GildedRose {
public:
    std::vector<Item>& items;

    explicit GildedRose(std::vector<Item>& itemsList) noexcept
        : items(itemsList) {}

    void updateQuality();
};

} // namespace gilded_rose
