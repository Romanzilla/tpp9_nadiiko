#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace minitest {

struct TestCase {
    std::string suite;
    std::string name;
    std::function<void()> fn;
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

struct Registrar {
    Registrar(std::string suite, std::string name, std::function<void()> fn) {
        registry().push_back(TestCase{std::move(suite), std::move(name), std::move(fn)});
    }
};

template <typename T, typename U>
void assertEqual(const T& actual, const U& expected, const char* exprA, const char* exprB, int line) {
    if (!(actual == expected)) {
        std::ostringstream oss;
        oss << "Рядок " << line << ": очікувалося (" << exprA << " == " << exprB
            << "), отримано [" << actual << "] замість [" << expected << "]";
        throw std::runtime_error(oss.str());
    }
}

inline void assertTrue(bool cond, const char* expr, int line) {
    if (!cond) {
        std::ostringstream oss;
        oss << "Рядок " << line << ": умова (" << expr << ") є хибною";
        throw std::runtime_error(oss.str());
    }
}

inline int runAllTests() {
    int passed = 0;
    int failed = 0;
    std::cout << "\n====================================================================\n";
    std::cout << " ЗАПУСК МОДУЛЬНИХ ТЕСТІВ (" << registry().size() << " тест-кейсів)\n";
    std::cout << "====================================================================\n";

    for (const auto& tc : registry()) {
        try {
            tc.fn();
            ++passed;
            std::cout << "[  OK  ] " << tc.suite << "." << tc.name << '\n';
        } catch (const std::exception& ex) {
            ++failed;
            std::cout << "[ FAIL ] " << tc.suite << "." << tc.name << "\n         " << ex.what() << '\n';
        }
    }

    std::cout << "--------------------------------------------------------------------\n";
    std::cout << " Підсумок тестування: ПРОЙДЕНО = " << passed
              << ", ПОМИЛОК = " << failed << '\n';
    std::cout << "====================================================================\n";
    return failed == 0 ? 0 : 1;
}

} // namespace minitest

#define TEST_CASE(Suite, Name) \
    static void test_##Suite##_##Name(); \
    static ::minitest::Registrar reg_##Suite##_##Name(#Suite, #Name, &test_##Suite##_##Name); \
    static void test_##Suite##_##Name()

#define ASSERT_EQ(actual, expected) \
    ::minitest::assertEqual((actual), (expected), #actual, #expected, __LINE__)

#define ASSERT_TRUE(cond) \
    ::minitest::assertTrue((cond), #cond, __LINE__)
