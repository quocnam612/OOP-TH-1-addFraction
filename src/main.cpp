#include <iostream>
#include <expected>
#include <tuple>
#include <format>
using std::cout, std::cin;
using std::format;
using std::expected;
using std::tuple, std::make_tuple;

#include "main.h"
#include "Fraction.h"

expected<tuple<Fraction, Fraction>, string> executeGetInputUseCase();
void executeAddFractionsUseCase(const Fraction& a, const Fraction& b);

int main() {
    cout << "Chương trình tính tổng hai phân số\n";

    auto result = executeGetInputUseCase();
    if (result.has_value()) {
        auto [a, b] = result.value();
        executeAddFractionsUseCase(a, b);
    } else {
        cout << result.error();
    }
    
    bye();
    return 0;
}

void bye() {
    cout << "\nChương trình đang thoát. Bấm enter để kết thúc...";
    cin.get();
}

expected<tuple<Fraction, Fraction>, string> executeGetInputUseCase() {
    auto result = Fraction::getFractionRetry("\nNhập phân số thứ nhất theo định dạng x/y: "); 
    if (!result.has_value()) {
        return unexpected(result.error());
    }
    Fraction a = result.value();

    result = Fraction::getFractionRetry("\nNhập phân số thứ hai theo định dạng x/y: ");
    if (!result.has_value()) {
        return unexpected(result.error());
    }
    Fraction b = result.value();

    return make_tuple(a, b);
}

void executeAddFractionsUseCase(const Fraction& a, const Fraction& b) {
    Fraction result = a + b;
    cout << "\nTổng hai phân số " << a << " và " << b << " là: " << result << "\n";
}