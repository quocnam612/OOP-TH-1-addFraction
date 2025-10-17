#include "main.h"
#include "usecase.h"

int main() {
    cout << "Chương trình tính tổng hai phân số\n";

    auto result = executeGetInputUseCase();
    if (result.has_value()) {
        auto [a, b] = result.value();
        executePrintAddFractionsUseCase(a, b);
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