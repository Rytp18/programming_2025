#include <iostream>
using namespace std;

int main() {
    // Пункт 1
    short A;
    int i;

    cout << "A: ";
    cin >> A;
    cout << "Bit i (0-7): ";
    cin >> i;

    if (i < 0 || i > 7) {
        cout << "Error" << endl;
        return 0;
    }

    // Вывод в двоичном виде
    cout << A << " = ";
    cout << ((A >> 7) & 1);
    cout << ((A >> 6) & 1);
    cout << ((A >> 5) & 1);
    cout << ((A >> 4) & 1);
    cout << ((A >> 3) & 1);
    cout << ((A >> 2) & 1);
    cout << ((A >> 1) & 1);
    cout << ((A >> 0) & 1);
    cout << endl;

    // Проверка бита
    int bit = (A >> i) & 1;

    if (bit == 1) {
        int x, y;
        cout << "Two numbers: ";
        cin >> x >> y;
        cout << "Max: " << (x > y ? x : y) << endl;
        A = A & ~(1 << i);
    }
    else {
        A = ~A;
    }

    // Результат
    cout << "Result: " << A << " = ";
    cout << ((A >> 7) & 1);
    cout << ((A >> 6) & 1);
    cout << ((A >> 5) & 1);
    cout << ((A >> 4) & 1);
    cout << ((A >> 3) & 1);
    cout << ((A >> 2) & 1);
    cout << ((A >> 1) & 1);
    cout << ((A >> 0) & 1);
    cout << endl;

    // Пункт 2
    int N;
    cout << "Month: ";
    cin >> N;

    switch (N) {
    case 1: cout << "January"; break;
    case 2: cout << "Febrary"; break;
    case 3: cout << "March"; break;
    case 4: cout << "April"; break;
    case 5: cout << "May"; break;
    case 6: cout << "June"; break;
    case 7: cout << "July"; break;
    case 8: cout << "August"; break;
    case 9: cout << "September"; break;
    case 10: cout << "October"; break;
    case 11: cout << "November"; break;
    case 12: cout << "December"; break;
    default: cout << "Error";
    }

    return 0;
}
