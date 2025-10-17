#include "usecase.h"

expected<tuple<Fraction, Fraction>, string> executeGetInputUseCase() {
    auto result = Fraction::getFractionRetry("\nNhập phân số thứ nhất theo định dạng x/y: ", 1); 
    if (!result.has_value()) {
        return unexpected(result.error());
    }
    Fraction a = result.value();

    result = Fraction::getFractionRetry("\nNhập phân số thứ hai theo định dạng x/y: ", 1);
    if (!result.has_value()) {
        return unexpected(result.error());
    }
    Fraction b = result.value();

    return make_tuple(a, b);
}

Fraction executePrintAddFractionsUseCase(const Fraction& a, const Fraction& b) {
    Fraction result = a + b;
    cout << "\nTổng hai phân số " << a << " và " << b << " là: " << result << "\n";
    return result;
}

Fraction executeSimplifyFractionUseCase(const Fraction& f) {
    Fraction result = Fraction::simplify(f);
    cout << "\nPhân số " << f << " sau khi rút gọn là: " << result << "\n";
    return result;
}