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

// Nhập phân số từ bàn phím
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

// Nhập phân số cho đến khi thành công
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

// Nhập phân số với số lần thử tối đa
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

// Xuất phân số ra dạng hỗn số
void Fraction::output() const {
    simplify(*this);
    if (abs(this->_numerator) > this->_denominator && this->_denominator != 1) {
        int wholePart = this->_numerator / this->_denominator;
        int newNumerator = abs(this->_numerator % this->_denominator);
        cout << format("{} {}/{}", wholePart, newNumerator, this->_denominator);
    }
    else if (this->_denominator == 1) cout << this->_numerator;
    else cout << *this;
}

// Tính ước chung lớn nhất (GCD) của hai số nguyên
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

// Rút gọn phân số
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

// Cộng hai phân số và trả về phân số đã rút gọn
Fraction Fraction::add(Fraction a, Fraction b) {
    Fraction result;
    
    result._numerator = a._numerator * b._denominator + b._numerator * a._denominator;
    result._denominator = a._denominator * b._denominator;
    
    return Fraction::simplify(result);
}

// Toán tử cộng hai phân số
Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction::add(*this, other);
}

// Toán tử so sánh hai phân số
bool Fraction::operator==(const Fraction& other) const {
    return (simplify(*this)._numerator == simplify(other)._numerator) &&
           (simplify(*this)._denominator == simplify(other)._denominator);
}

// Xuất phân số theo định dạng tử số/mẫu số
ostream& operator<<(ostream& os, const Fraction& frac) {
    os << format("{}/{}", frac._numerator, frac._denominator);
    return os;
}