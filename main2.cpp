#include <iostream>
#include <string>
using namespace std;

int signs_after_dot(string n) { // количество знаков после точки
	int count = 0;
	for (int i = 0; i < size(n); i++) {
		count += 1;
		if (n[i] == '.' || n[i] == ',') break;
	}
	return size(n) - count;
}

double f(char n, int p, int i) { //для перевода числа с помощью степенного ряда
	double x = 0;
	if (n == 'A') x += 10 * pow(p, i);
	else if (n == 'B') x += 11 * pow(p, i);
	else if (n == 'C') x += 12 * pow(p, i);
	else if (n == 'D') x += 13 * pow(p, i);
	else if (n == 'E') x += 14 * pow(p, i);
	else if (n == 'F') x += 15 * pow(p, i);
	else if (n == '0') x += 0 * pow(p, i);
	else if (n == '1') x += 1 * pow(p, i);
	else if (n == '2') x += 2 * pow(p, i);
	else if (n == '3') x += 3 * pow(p, i);
	else if (n == '4') x += 4 * pow(p, i);
	else if (n == '5') x += 5 * pow(p, i);
	else if (n == '6') x += 6 * pow(p, i);
	else if (n == '7') x += 7 * pow(p, i);
	else if (n == '8') x += 8 * pow(p, i);
	else if (n == '9') x += 9 * pow(p, i);
	return x;
}

double changer(string n, int p) {
	double result = 0;
	int m = 0; // для перебора элементов string
	if (signs_after_dot(n) != 0) {
		for (int i = size(n) - signs_after_dot(n) - 2; i >= 0; i--) { // i для степени
			result += f(n[m], p, i);
			m += 1;
		}
		m += 1; // пропуск точки
		for (int i = 1; i <= signs_after_dot(n); i++) {
			result += f(n[m], p, -i);
			m += 1;
		}
	}
	else {
		for (int i = size(n) - 1; i >= 0; i--) {
			result += f(n[m], p, i);
			m += 1;
		}
	}
	return result;
}

int main() {
	cout << "1100001001 (2) = " << changer("1100001001", 2) << " (10)\n";
	cout << "1100100101 (2) = " << changer("1100100101", 2) << " (10)\n";
	cout << "1111110110,01 (2) = " << changer("1111110110,01", 2) << " (10)\n";
	cout << "11001100,011 (2) = " << changer("11001100,011", 2) << " (10)\n";
	cout << "112,04 (8) = " << changer("112,04", 8) << " (10)\n";
	cout << "334,A (16) = " << changer("334,A", 16) << " (10)\n";
}