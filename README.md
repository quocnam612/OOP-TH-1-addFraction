# Chương trình tính tổng hai phân số

## Thông tin sinh viên

MSSV: **24120098**
Họ và tên: *Nguyễn Quốc Nam*

## Biên dịch & chạy

```Bash
g++ -std=c++23 src/*.cpp -o ./out/app
```

```Bash
./out/app
```

## Gtest

```bash
g++ -std=c++23 -Wall -g -pthread test/main.cpp src/Fraction.cpp src/usecase.cpp -lgtest_main -lgtest -lpthread -o ./test/tests
```

```bash
./test/tests
```
