# Лабораторна робота №9 — Рефакторинг програмного коду та принципи SOLID

**Виконавець:** студент ФІТ 3-10 Надійко Роман Олександрович  
**Дисципліна:** Технології прикладного програмування  

## 1. Склад проєкту
* **Обов'язкове завдання (Система управління бібліотекою):**
  * `include/library/Book.hpp` — інкапсульована сутність книги (`SRP`).
  * `include/library/IBookRepository.hpp`, `InMemoryBookRepository.hpp` — абстракція та реалізація сховища (`DIP`, `ISP`).
  * `include/library/INotificationService.hpp`, `NotificationServices.hpp` — абстракція та реалізації сповіщень (`Email`, `SMS`, `Spy` для тестів; `DIP`, `OCP`).
  * `include/library/IBookPrinter.hpp` — відокремлений компонент виведення списку книг (`SRP`, `ISP`).
  * `include/library/Library.hpp`, `src/library/Library.cpp` — клас-координатор із впровадженням залежностей через конструктор.
* **Завдання Kata №2 (Gilded Rose) + Індивідуальне розширення (`Conjured`):**
  * `include/gilded_rose/Item.hpp` — збережена початкова структура товару.
  * `include/gilded_rose/IItemUpdateStrategy.hpp`, `ItemStrategies.hpp` — поліморфні стратегії оновлення (`Regular`, `AgedBrie`, `Sulfuras`, `BackstagePass` та нове розширення `ConjuredItemStrategy`).
  * `include/gilded_rose/ItemStrategyFactory.hpp`, `src/gilded_rose/ItemStrategyFactory.cpp` — вибір стратегії за типом товару.
  * `include/gilded_rose/GildedRose.hpp`, `src/gilded_rose/GildedRose.cpp` — основний клас без вкладених умовних операторів.
* **Модульні тести:** `tests/MiniTest.hpp`, `tests/TestSuites.cpp`.

## 2. Збирання та запуск у GitHub Codespaces (Linux)
```bash
cmake -B build && cmake --build build -j && ./build/solid_refactoring_app
```
