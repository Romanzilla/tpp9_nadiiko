#pragma once

#include <ostream>
#include <string>
#include <utility>

namespace gilded_rose {

// Збережено оригінальну структуру Item відповідно до обмежень завдання Kata
struct Item {
    std::string name;
    int sellIn;
    int quality;

    Item(std::string itemName, int itemSellIn, int itemQuality)
        : name(std::move(itemName)), sellIn(itemSellIn), quality(itemQuality) {}
};

inline std::ostream& operator<<(std::ostream& os, const Item& item) {
    return os << item.name << ", " << item.sellIn << ", " << item.quality;
}

} // namespace gilded_rose
