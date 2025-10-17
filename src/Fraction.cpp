#include "Fraction.h"
#include <iostream>
#include <format>
#include <regex>
#include <sstream>
using std::cout, std::cin;
using std::format;
using std::regex, std::regex_match;
using std::istringstream;

Fraction::Fraction() : _numerator(0), _denominator(1) {}

Fraction::Fraction(int num, int denom) : _numerator(num), _denominator(denom) {}

expected<Fraction, string> Fraction::getFraction(string message) {
    cout << message;
    
    string buffer;
    getline(cin, buffer);
    
    // 1. Rỗng - Edge case
    if (buffer.length() == 0) {
       return unexpected(" Empty input data");  
    }  
    
    // 2. Không đúng định dạng
    if (!regex_match(buffer, regex(R"((-?\d+)/(-?\d+))"))) {
        return unexpected(" Invalid fraction format");
    } 

    // 3. Không đúng miền giá trị
    if (!regex_match(buffer, regex(R"(.+/(-?(?!0+$)(.+)))"))) {
        return unexpected(" Fraction values out of range");
    }

    // Main success scenario / Happy path
    istringstream iss(buffer);
    Fraction frac;

    getline(iss, buffer, '/');
    frac._numerator = stoi(buffer);
    getline(iss, buffer, '/');
    frac._denominator = stoi(buffer);

    return frac;
}

Fraction Fraction::getFractionLoop(string message) {
    expected<Fraction, string> result;

    do {
        result = Fraction::getFraction(message);

        if (!result.has_value()){
            cout << "Lỗi nhập liệu:" << result.error() << "\n";
            cout << "Vui lòng nhập lại.\n";
        }
    } while (!result.has_value());    
    
    return result.value();
}

expected<Fraction, string> Fraction::getFractionRetry(string message, int maxAttempts) {
    int failCount = 0;
    expected<Fraction, string> result;

    do {
        result = Fraction::getFraction(message);
        
        if (!result.has_value()){
            failCount++;
            cout << "Lỗi nhập liệu:" << result.error() << "\n";
            
            if (failCount != maxAttempts ) {
                cout << "Vui lòng nhập lại. Bạn còn " << maxAttempts - failCount << " lần thử\n";
            }  
        }
    } while (!result.has_value() 
        && (failCount != maxAttempts)
    );
    
    if (failCount == maxAttempts) {
        return unexpected(format(
            "Bạn đã nhập quá số lần cho phép là: {}", 
            maxAttempts
        ));
    }
    
    return result.value();
}

void Fraction::output() const {
    if (_denominator == 1) cout << format("{}", _numerator);
    else cout << format("({}/{})", _numerator, _denominator);
} 

int Fraction::gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction Fraction::simplify(Fraction f) {
    int gcd = Fraction::gcd(f._numerator, f._denominator);
    
    f._numerator /= gcd;
    f._denominator /= gcd;
    
    // Đảm bảo mẫu số luôn dương
    if (f._denominator < 0) {
        f._numerator = -f._numerator;
        f._denominator = -f._denominator;
    }
    
    return f;
}

Fraction Fraction::add(Fraction a, Fraction b) {
    Fraction result;
    
    result._numerator = a._numerator * b._denominator + b._numerator * a._denominator;
    result._denominator = a._denominator * b._denominator;
    
    return Fraction::simplify(result);
}

Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction::add(*this, other);
}

bool Fraction::operator==(const Fraction& other) const {
    return (simplify(*this)._numerator == simplify(other)._numerator) &&
           (simplify(*this)._denominator == simplify(other)._denominator);
}

ostream& operator<<(ostream& os, const Fraction& frac) {
    if (frac._denominator == 1) os << format("{}", frac._numerator);
    else os << format("{}/{}", frac._numerator, frac._denominator);
    return os;
}