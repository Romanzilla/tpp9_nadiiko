#include "gilded_rose/ItemStrategyFactory.hpp"
#include "gilded_rose/ItemStrategies.hpp"

namespace gilded_rose {

std::unique_ptr<IItemUpdateStrategy> ItemStrategyFactory::createFor(const Item& item) {
    if (item.name == "Aged Brie") {
        return std::make_unique<AgedBrieStrategy>();
    }
    if (item.name == "Sulfuras, Hand of Ragnaros") {
        return std::make_unique<SulfurasStrategy>();
    }
    if (item.name == "Backstage passes to a TAFKAL80ETC concert") {
        return std::make_unique<BackstagePassStrategy>();
    }
    if (item.name.rfind("Conjured", 0) == 0) {
        return std::make_unique<ConjuredItemStrategy>();
    }
    return std::make_unique<RegularItemStrategy>();
}

} // namespace gilded_rose
