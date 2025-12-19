#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Основная функция для преобразования числа из десятичной системы
// n — число, p — основание системы счисления, precision — точность дробной части
string convertNumber(double n, int p, int precision) {
    // Лямбда-функция для получения дробной части числа
    auto fraction = [](double x) {
        while (x >= 1) x -= 1; // пока число >= 1, вычитаем 1, чтобы оставить только дробную часть
        return x; // возвращаем дробную часть
        };

    // Обработка целой части числа
    string int_part_str = ""; // строка для хранения целой части в новой системе
    int x = static_cast<int>(n); // приводим число к целому типу
    if (x == 0) {
        // Если число равно 0, возвращаем "0"
        int_part_str = "0";
    }
    else {
        // Массив букв для цифр выше 9 (шестнадцатеричная система)
        string letters[6] = { "A", "B", "C", "D", "E", "F" };
        // Пока x не станет 0, делим и получаем остатки
        while (x) {
            int rem = x % p; // остаток от деления на основание
            if (rem > 9) {
                // Если остаток больше 9, используем буквы A-F
                int_part_str = letters[rem - 10] + int_part_str;
            }
            else {
                // Иначе добавляем цифру
                int_part_str = to_string(rem) + int_part_str;
            }
            x /= p; // делим число на основание системы
        }
    }

    // Обработка дробной части
    double frac_part = fraction(n); // получаем дробную часть числа
    string frac_str = ""; // строка для дробной части
    int cnt = 0; // счетчик итераций (для ограничения точности)
    string letters[6] = { "A", "B", "C", "D", "E", "F" }; // буквы для цифр выше 9

    // Цикл для преобразования дробной части с точностью до precision символов
    while (cnt < precision && frac_part != 0) {
        frac_part *= p; // умножаем дробную часть на основание системы
        int digit = static_cast<int>(frac_part); // целая часть результата — следующая цифра
        if (digit > 9) {
            // Если цифра больше 9, используем букву
            frac_str += letters[digit - 10];
        }
        else {
            // Иначе добавляем цифру
            frac_str += to_string(digit);
        }
        frac_part = fraction(frac_part); // обновляем дробную часть
        cnt++; // увеличиваем счетчик
    }

    if (frac_str.empty()) {
        // Если дробная часть отсутствует, возвращаем только целую часть
        return int_part_str;
    }
    else {
        // Иначе объединяем целую и дробную части через точку
        return int_part_str + "." + frac_str;
    }
}

int main() {
    const int precision = 10; // максимальная точность дробной части
    int bases[3] = { 2, 8, 16 }; 
    double nums[5] = { 164, 255, 712.25, 670.25, 11.89 }; 

    // Проходим по всем числам и системам
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            cout << nums[i] << " = " << convertNumber(nums[i], bases[j], precision) << " (" << bases[j] << ")\n";
        }
    }
}