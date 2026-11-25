#pragma once

#include "IItemUpdateStrategy.hpp"

namespace gilded_rose {

// 1. Звичайний товар: -1 до Quality щодня, -2 після завершення SellIn
class RegularItemStrategy : public IItemUpdateStrategy {
public:
    void update(Item& item) const override {
        item.sellIn -= 1;
        const int degradeStep = (item.sellIn < 0) ? 2 : 1;
        decreaseQuality(item, degradeStep);
    }
};

// 2. Aged Brie: якість зростає на +1 до SellIn < 0 та на +2 після
class AgedBrieStrategy : public IItemUpdateStrategy {
public:
    void update(Item& item) const override {
        item.sellIn -= 1;
        const int improveStep = (item.sellIn < 0) ? 2 : 1;
        increaseQuality(item, improveStep);
    }
};

// 3. Sulfuras: легендарний товар, SellIn і Quality (80) ніколи не змінюються
class SulfurasStrategy : public IItemUpdateStrategy {
public:
    void update(Item& /*item*/) const override {
        // Легендарний предмет не має терміну продажу та зберігає сталу якість
    }
};

// 4. Backstage passes: якість зростає з наближенням концерту і падає до 0 після події
class BackstagePassStrategy : public IItemUpdateStrategy {
public:
    void update(Item& item) const override {
        item.sellIn -= 1;
        if (item.sellIn < 0) {
            item.quality = 0;
            return;
        }

        if (item.sellIn < 5) {
            increaseQuality(item, 3);
        } else if (item.sellIn < 10) {
            increaseQuality(item, 2);
        } else {
            increaseQuality(item, 1);
        }
    }
};

// 5. Індивідуальне розширення: Conjured (Зачаровані товари)
// Правило: Quality зменшується вдвічі швидше за звичайні товари (-2 щодня, -4 після SellIn < 0)
class ConjuredItemStrategy : public IItemUpdateStrategy {
public:
    void update(Item& item) const override {
        item.sellIn -= 1;
        const int degradeStep = (item.sellIn < 0) ? 4 : 2;
        decreaseQuality(item, degradeStep);
    }
};

} // namespace gilded_rose
