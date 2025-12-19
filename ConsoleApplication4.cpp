#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Функция для преобразования числа, представленного строкой, из системы счисления p в десятичную
double convertNumberToDecimal(const string& n, int p) {
    int len = n.length(); // длина строки числа
    int dotPos = -1; // позиция разделителя дробной части (точка или запятая), изначально не найдено

    // Находим позицию разделителя дробной части, если он есть
    for (int i = 0; i < len; i++) {
        if (n[i] == '.' || n[i] == ',') {
            dotPos = i; // запоминаем позицию разделителя
            break;
        }
    }

    double result = 0.0; // итоговое значение в десятичной системе
    int startIdx = 0; // индекс начала строки (не используется, можно убрать)
    int endIdx = len - 1; // индекс конца строки по умолчанию

    // Если есть дробная часть
    if (dotPos != -1) {
        endIdx = len - 1; // конец строки
        // Обработка целой части числа (до разделителя)
        int power = 0; // степень основания p для целой части
        for (int i = dotPos - 1; i >= 0; i--) {
            char c = n[i]; // текущий символ
            double digitValue = 0; // значение цифры
            // Определяем значение цифры в зависимости от диапазона
            if (c >= '0' && c <= '9') {
                digitValue = c - '0'; // цифры 0-9
            }
            else if (c >= 'A' && c <= 'F') {
                digitValue = c - 'A' + 10; // буквы A-F для оснований выше 10
            }
            // Добавляем вклад текущей цифры к результату
            result += digitValue * pow(p, power);
            power++; // увеличиваем степень
        }

        // Обработка дробной части после разделителя
        int fracStart = dotPos + 1; // индекс начала дробной части
        int fracLength = endIdx - dotPos; // длина дробной части
        for (int i = 0; i < fracLength; i++) {
            char c = n[fracStart + i]; // текущий символ дробной части
            double digitValue = 0; // значение цифры
            if (c >= '0' && c <= '9') {
                digitValue = c - '0'; // цифры 0-9
            }
            else if (c >= 'A' && c <= 'F') {
                digitValue = c - 'A' + 10; // буквы A-F
            }
            // Добавляем значение дробной части с отрицательной степенью основания p
            result += digitValue * pow(p, -(i + 1));
        }
    }
    else {
        // Обработка числа без дробной части
        int power = 0; // степень основания p
        for (int i = len - 1; i >= 0; i--) {
            char c = n[i]; // текущий символ
            double digitValue = 0; // значение цифры
            if (c >= '0' && c <= '9') {
                digitValue = c - '0'; // цифры 0-9
            }
            else if (c >= 'A' && c <= 'F') {
                digitValue = c - 'A' + 10; // буквы A-F
            }
            // Добавляем вклад цифры в итоговое число
            result += digitValue * pow(p, power);
            power++; // увеличиваем степень
        }
    }

    return result;
}

int main() {
    cout << "1100111011 (2) = " << convertNumberToDecimal("1100111011", 2) << " (10)\n";
    cout << "10000000111 (2) = " << convertNumberToDecimal("10000000111", 2) << " (10)\n";
    cout << "10110101,1 (2) = " << convertNumberToDecimal("10110101,1", 2) << " (10)\n";
    cout << "100000110,10101 (2) = " << convertNumberToDecimal("100000110,10101", 2) << " (10)\n";
    cout << "671,24 (8) = " << convertNumberToDecimal("671,24", 8) << " (10)\n";
    cout << "41A,61 (16) = " << convertNumberToDecimal("41A,61", 16) << " (10)\n";

    return 0;
}