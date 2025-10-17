#pragma once
#include <expected>
#include <string>
using std::expected, std::unexpected;
using std::string;
using std::ostream;

/**
 * @class Fraction
 * @brief Lớp biểu diễn một phân số.
 * 
 * Lớp này bao gồm hai thuộc tính riêng (tử số và mẫu số) 
 * cùng với các phương thức để nhập/xuất phân số, 
 * và các hàm tĩnh để rút gọn, cộng hai phân số.
 */
class Fraction {
private:
    int _numerator; ///< Tử số của phân số
    int _denominator; ///< Mẫu số của phân số
public:
    /**
     * @brief Constructor mặc định
     */
    Fraction();

    /**
     * @brief Constructor
     * 
     * Khởi tạo phân số với tử số và mẫu số được chỉ định.
     */
    Fraction(int num, int denom);
    
    /**
     * @brief Nhập phân số từ bàn phím.
     * 
     * Yêu cầu người dùng nhập hai giá trị int tương ứng với tử số và mẫu số.
     * @note Phương thức này thay đổi giá trị của thuộc tính `_numerator` và `_denominator`.
     */
    static expected<Fraction, string> getFraction(string message);

    /**
     * @brief Thử nhận phân số từ bàn phím cho đến khi thành công.
     * 
     * Yêu cầu người dùng nhập hai giá trị int tương ứng với tử số và mẫu số.
     * Nếu nhập sai, sẽ yêu cầu nhập lại cho đến khi thành công.
     * @note Phương thức này thay đổi giá trị của thuộc tính `_numerator` và `_denominator`.
     */
    static Fraction getFractionLoop(string message);

    /**
     * @brief Thử nhận phân số từ bàn phím tối đa theo số lần quy địnhđịnh.
     * 
     * Yêu cầu người dùng nhập hai giá trị int tương ứng với tử số và mẫu số.
     * Nếu nhập sai, sẽ yêu cầu nhập lại cho đến khi thành công hoặc đạt số lần tối đa.
     * @note Phương thức này thay đổi giá trị của thuộc tính `_numerator` và `_denominator`.
     */
    static expected<Fraction, string> getFractionRetry(string message, int maxAttempts = 3);

    /**
     * @brief Xuất phân số ra màn hình.
     * 
     * In ra theo định dạng hỗn số nếu tử số lớn hơn mẫu số,
     * hoặc in ra dạng phân số thông thường.
     */
    void output() const;
    
    /**
     * @brief Tính ước chung lớn nhất (GCD) của hai số nguyên.
     * 
     * Sử dụng thuật toán Euclid để tìm GCD.
     * @param a Số nguyên thứ nhất
     * @param b Số nguyên thứ hai
     * @return int Ước chung lớn nhất của a và b
     */
    static int gcd(int a, int b);

    /**
     * @brief Rút gọn phân số.
     * 
     * @param f Phân số cần rút gọn
     * @return phân số đã được rút gọn
     * 
     * @details
     * Sử dụng công thức:
     * dùng ước chung lớn nhất (GCD) của tử số và mẫu số để chia cả hai.
     * 
     * @note Đây là hàm tĩnh (static), có thể gọi mà không cần tạo đối tượng:
     */
    static Fraction simplify(Fraction f);


    /**
     * @brief Công 2 phân số
     * 
     * @param a Phân số thứ nhất
     * @param b Phân số thứ hai
     * @return Tổng 2 phân số (đã được rút gọn)
     * 
     * @note Đây là hàm tĩnh (static), có thể gọi mà không cần tạo đối tượng:
     */
    static Fraction add(Fraction a, Fraction b);

    /**
     * @brief Toán tử cộng hai phân số
     * @return Tổng 2 phân số (đã được rút gọn)
     */
    Fraction operator+(const Fraction& other) const;

    /**
     * @brief Toán tử so sánh hai phân số
     * @return true nếu hai phân số bằng nhau
     */
    bool operator==(const Fraction& other) const;

    /**
     * @brief Toán tử xuất phân số
     */
    friend ostream& operator<<(ostream& os, const Fraction& frac);
};
