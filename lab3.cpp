#include <iostream>
using namespace std;

int main() {
    int n, num;
    cout << "n = ";
    cin >> n;

    int sum = 0, max = -9999, index = -1;

    for (int i = 1; i <= n; i++) {
        cin >> num;
        if (num % 2 == 0) {
            sum += num;
            if (num > max) {
                max = num;
                index = i;
            }
        }
    }

    if (index == -1) {
        cout << "no even" << endl;
    }
    else {
        cout << "Sum: " << sum << endl;
        cout << "Max: " << max << endl;
        cout << "Pos: " << index << endl;
    }

    int x;
    cout << "x = ";
    cin >> x;

    if (x < 0) x = -x;

    int min = 9;
    while (x > 0) {
        int d = x % 10;
        if (d != 0 && d != 7) {
            if (d < min) min = d;
        }
        x = x / 10;
    }

    if (min == 9) {
        cout << "no nums" << endl;
    }
    else {
        cout << "Min digit: " << min << endl;
    }

    return 0;
}
