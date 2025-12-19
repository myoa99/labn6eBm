#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Функция для преобразования числа из любой системы счисления в десятичное
double convertToDecimal(const string& n, int p) {
    // Находим позицию запятой или точки, если они есть
    int dot_pos = n.find_first_of(".,");
    int fractional_digits = 0;

    // Подсчёт количества знаков после запятой или точки
    if (dot_pos != string::npos) {
        fractional_digits = n.size() - dot_pos - 1;
    }

    double result = 0;

    // Обработка целой части числа
    if (dot_pos != string::npos) {
        // Есть дробная часть, обрабатываем целую часть до точки/запятой
        for (int i = dot_pos - 1; i >= 0; i--) {
            char ch = n[i];
            double val = 0;

            // Обработка цифр 0-9
            if (ch >= '0' && ch <= '9') {
                val = (ch - '0') * pow(p, i - (dot_pos - 1));
            }
            // Обработка букв A-F для шестнадцатеричной системы
            else if (ch >= 'A' && ch <= 'F') {
                val = (ch - 'A' + 10) * pow(p, i - (dot_pos - 1));
            }

            // Добавляем значение к итоговому результату
            result += val;
        }
    }
    else {
        // Нет дробной части, вся строка — целое число
        for (int i = n.size() - 1; i >= 0; i--) {
            char ch = n[i];
            double val = 0;

            // Обработка цифр 0-9
            if (ch >= '0' && ch <= '9') {
                val = (ch - '0') * pow(p, i);
            }
            // Обработка букв A-F
            else if (ch >= 'A' && ch <= 'F') {
                val = (ch - 'A' + 10) * pow(p, i);
            }

            // Добавляем значение к итоговому результату
            result += val;
        }
        // В случае отсутствия дробной части — возвращаем результат
        return result;
    }

    // Обработка дробной части (если есть)
    if (dot_pos != string::npos) {
        int m = dot_pos + 1; // позиция первого знака дробной части
        for (int i = 0; i < fractional_digits; i++) {
            char ch = n[m + i];
            double val = 0;

            // Обработка цифр 0-9
            if (ch >= '0' && ch <= '9') {
                val = (ch - '0') * pow(p, -(i + 1));
            }
            // Обработка букв A-F
            else if (ch >= 'A' && ch <= 'F') {
                val = (ch - 'A' + 10) * pow(p, -(i + 1));
            }

            // Добавляем дробное значение к результату
            result += val;
        }
    }

    return result; // Возвращаем итоговое десятичное число
}

int main() {
    cout << "1100111011 (2) = " << convertToDecimal("1100111011", 2) << " (10)\n";
    cout << "10000000111 (2) = " << convertToDecimal("10000000111", 2) << " (10)\n";
    cout << "10110101,1 (2) = " << convertToDecimal("10110101,1", 2) << " (10)\n";
    cout << "100000110,10101 (2) = " << convertToDecimal("100000110,10101", 2) << " (10)\n";
    cout << "671,24 (8) = " << convertToDecimal("671,24", 8) << " (10)\n";
    cout << "41A,61 (16) = " << convertToDecimal("41A,61", 16) << " (10)\n";

    return 0;
}