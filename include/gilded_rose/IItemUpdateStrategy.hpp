#pragma once

#include "Item.hpp"

namespace gilded_rose {

// Абстрактна стратегія щоденного оновлення характеристик товару (OCP, DIP, LSP)
class IItemUpdateStrategy {
public:
    virtual ~IItemUpdateStrategy() = default;
    virtual void update(Item& item) const = 0;

protected:
    static constexpr int kMinQuality = 0;
    static constexpr int kMaxQuality = 50;

    static void increaseQuality(Item& item, int amount = 1) noexcept {
        item.quality += amount;
        if (item.quality > kMaxQuality) {
            item.quality = kMaxQuality;
        }
    }

    static void decreaseQuality(Item& item, int amount = 1) noexcept {
        item.quality -= amount;
        if (item.quality < kMinQuality) {
            item.quality = kMinQuality;
        }
    }
};

} // namespace gilded_rose
