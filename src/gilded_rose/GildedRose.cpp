#include "gilded_rose/GildedRose.hpp"
#include "gilded_rose/ItemStrategyFactory.hpp"

namespace gilded_rose {

void GildedRose::updateQuality() {
    for (auto& item : items) {
        auto strategy = ItemStrategyFactory::createFor(item);
        strategy->update(item);
    }
}

} // namespace gilded_rose
