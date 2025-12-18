#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Функция для подсчёта количества знаков после запятой или точки
int signs_after_dot(const string& n) {
    int count = 0;
    for (size_t i = 0; i < n.size(); i++) {
        if (n[i] == '.' || n[i] == ',') {
            // Когда достигли точки или запятой, возвращаем количество символов после неё
            return n.size() - i - 1;
        }
    }
    // Если точка или запятая не найдены, возвращаем 0
    return 0;
}

// Функция для преобразования одного символа в его числовое значение в системе счисления
double f(char n, int p, int i) {
    double x = 0;
    // Обработка символов от '0' до '9' и 'A' до 'F' для шестинадцатеричной системы
    if (n >= '0' && n <= '9') {
        x += (n - '0') * pow(p, i);
    } else if (n >= 'A' && n <= 'F') {
        x += (n - 'A' + 10) * pow(p, i);
    }
    return x;
}

// Основная функция для преобразования строки числа из любой системы счисления в десятичное число
double changer(const string& n, int p) {
    double result = 0;
    int dot_pos = n.find_first_of(".,"); // позиция точки или запятой
    int fractional_digits = 0;

    if (dot_pos != string::npos) {
        // Есть дробная часть
        fractional_digits = signs_after_dot(n);
    }

    int m = 0; // индекс для обхода строки

    // Обработка целой части
    if (dot_pos != string::npos) {
        // Если есть дробная часть, то целая часть идёт до точки или запятой
        for (int i = dot_pos - 1; i >= 0; i--) {
            result += f(n[i], p, i - (dot_pos - 1));
        }
        m = dot_pos + 1; // индекс после точки
    } else {
        // Нет дробной части
        for (int i = n.size() - 1; i >= 0; i--) {
            result += f(n[i], p, i);
        }
        return result; // всё число целое
    }

    // Обработка дробной части
    for (int i = 0; i < fractional_digits; i++) {
        result += f(n[m], p, - (i + 1));
        m++;
    }

    return result;
}

int main() {
    cout << "1100111011 (2) = " << changer("1100111011", 2) << " (10)\n";
    cout << "10000000111 (2) = " << changer("10000000111", 2) << " (10)\n";
    cout << "10110101,1 (2) = " << changer("10110101,1", 2) << " (10)\n";
    cout << "100000110,10101 (2) = " << changer("100000110,10101", 2) << " (10)\n";
    cout << "671,24 (8) = " << changer("671,24", 8) << " (10)\n";
    cout << "41A,61 (16) = " << changer("41A,61", 16) << " (10)\n";

    return 0;
}