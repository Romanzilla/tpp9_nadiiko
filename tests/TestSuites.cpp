#include "MiniTest.hpp"
#include "gilded_rose/GildedRose.hpp"
#include "library/Book.hpp"
#include "library/InMemoryBookRepository.hpp"
#include "library/Library.hpp"
#include "library/NotificationServices.hpp"

// --- Тести рефакторингу системи управління бібліотекою ---

TEST_CASE(LibraryRefactoringTest, AddBookSavesToRepoAndSendsNotification) {
    using namespace library;
    InMemoryBookRepository repo;
    SpyNotificationService spyNotifier;
    ConsoleBookPrinter printer;
    Library lib(repo, spyNotifier, printer);

    lib.addBook(Book("The Catcher in the Rye", "J.D. Salinger"));
    lib.addBook(Book("To Kill a Mockingbird", "Harper Lee"));

    ASSERT_EQ(lib.getBooks().size(), static_cast<std::size_t>(2));
    ASSERT_EQ(lib.getBooks()[0].getTitle(), std::string("The Catcher in the Rye"));
    ASSERT_EQ(spyNotifier.getSentTitles().size(), static_cast<std::size_t>(2));
    ASSERT_EQ(spyNotifier.getSentTitles()[1], std::string("To Kill a Mockingbird"));
}

TEST_CASE(LibraryRefactoringTest, BookEncapsulationRejectsEmptyFields) {
    using namespace library;
    bool thrown = false;
    try {
        Book invalid("", "Author");
    } catch (const std::invalid_argument&) {
        thrown = true;
    }
    ASSERT_TRUE(thrown);
}

// --- Тести базової функціональності Gilded Rose Kata ---

TEST_CASE(GildedRoseKataTest, RegularItemDegradesBeforeAndAfterSellIn) {
    using namespace gilded_rose;
    std::vector<Item> items = {Item("+5 Dexterity Vest", 1, 10)};
    GildedRose app(items);

    app.updateQuality(); // sellIn: 0, quality: 9
    ASSERT_EQ(items[0].sellIn, 0);
    ASSERT_EQ(items[0].quality, 9);

    app.updateQuality(); // sellIn: -1, quality: 7 (удвічі швидше)
    ASSERT_EQ(items[0].sellIn, -1);
    ASSERT_EQ(items[0].quality, 7);
}

TEST_CASE(GildedRoseKataTest, QualityNeverNegativeAndNeverExceedsFifty) {
    using namespace gilded_rose;
    std::vector<Item> items = {
        Item("Elixir of the Mongoose", 2, 0),
        Item("Aged Brie", 5, 50)
    };
    GildedRose app(items);
    app.updateQuality();

    ASSERT_EQ(items[0].quality, 0);
    ASSERT_EQ(items[1].quality, 50);
}

TEST_CASE(GildedRoseKataTest, AgedBrieImprovesTwiceAsFastAfterSellIn) {
    using namespace gilded_rose;
    std::vector<Item> items = {Item("Aged Brie", 0, 10)};
    GildedRose app(items);

    app.updateQuality();
    ASSERT_EQ(items[0].sellIn, -1);
    ASSERT_EQ(items[0].quality, 12);
}

TEST_CASE(GildedRoseKataTest, SulfurasNeverChangesSellInOrQuality) {
    using namespace gilded_rose;
    std::vector<Item> items = {Item("Sulfuras, Hand of Ragnaros", 5, 80)};
    GildedRose app(items);

    app.updateQuality();
    ASSERT_EQ(items[0].sellIn, 5);
    ASSERT_EQ(items[0].quality, 80);
}

TEST_CASE(GildedRoseKataTest, BackstagePassesIncreaseAndDropToZeroAfterConcert) {
    using namespace gilded_rose;
    std::vector<Item> items = {
        Item("Backstage passes to a TAFKAL80ETC concert", 11, 20),
        Item("Backstage passes to a TAFKAL80ETC concert", 10, 20),
        Item("Backstage passes to a TAFKAL80ETC concert", 5, 20),
        Item("Backstage passes to a TAFKAL80ETC concert", 0, 20)
    };
    GildedRose app(items);
    app.updateQuality();

    ASSERT_EQ(items[0].quality, 21); // > 10 днів: +1
    ASSERT_EQ(items[1].quality, 22); // <= 10 днів: +2
    ASSERT_EQ(items[2].quality, 23); // <= 5 днів: +3
    ASSERT_EQ(items[3].quality, 0);  // після концерту: 0
}

// --- Тести індивідуального розширення: Conjured Items (OCP) ---

TEST_CASE(ConjuredExtensionTest, ConjuredItemDegradesTwiceAsFastBeforeSellIn) {
    using namespace gilded_rose;
    std::vector<Item> items = {Item("Conjured Mana Cake", 3, 10)};
    GildedRose app(items);

    app.updateQuality();
    ASSERT_EQ(items[0].sellIn, 2);
    ASSERT_EQ(items[0].quality, 8);
}

TEST_CASE(ConjuredExtensionTest, ConjuredItemDegradesFourTimesAfterSellInAndClampsAtZero) {
    using namespace gilded_rose;
    std::vector<Item> items = {Item("Conjured Mana Cake", 0, 6)};
    GildedRose app(items);

    app.updateQuality(); // sellIn: -1, quality: 6 - 4 = 2
    ASSERT_EQ(items[0].sellIn, -1);
    ASSERT_EQ(items[0].quality, 2);

    app.updateQuality(); // sellIn: -2, quality: max(0, 2 - 4) = 0
    ASSERT_EQ(items[0].sellIn, -2);
    ASSERT_EQ(items[0].quality, 0);
}
