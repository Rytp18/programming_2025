#include <iostream>
#include <cmath>
#include <climits>

int findMinDigit(int num) {
    if (num == 0) return 0;

    int minDigit = 9;
    num = std::abs(num);

    while (num > 0) {
        int digit = num % 10;
        if (digit < minDigit) {
            minDigit = digit;
        }
        num /= 10;
    }
    return minDigit;
}

int main() {
    const int NMax = 4;
    const int ROWS = 3;
    const int COLS = 4;

    int arr[NMax];

    std::cout << "Enter " << NMax << " elements of array:" << std::endl;
    for (int i = 0; i < NMax; ++i) {
        std::cin >> arr[i];
    }

    int minDigitFirst = findMinDigit(arr[0]);
    int minDigitLast = findMinDigit(arr[NMax - 1]);

    std::cout << "Min digit of first number: " << minDigitFirst << std::endl;
    std::cout << "Min digit of last number: " << minDigitLast << std::endl;

    if (minDigitFirst == minDigitLast) {
        for (int i = 0; i < NMax - 1; ++i) {
            for (int j = 0; j < NMax - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        std::cout << "The array is sorted in ascending order" << std::endl;
    }

    std::cout << "Array after processing:" << std::endl;
    for (int i = 0; i < NMax; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl << std::endl;

    int matrix[ROWS][COLS];

    std::cout << "Enter matrix " << ROWS << "x" << COLS << ":" << std::endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int closestRow = 0;
    int minDiff = INT_MAX;
    bool found = false;

    for (int i = 0; i < ROWS; ++i) {
        int rowSum = 0;
        for (int j = 0; j < COLS; ++j) {
            rowSum += matrix[i][j];
        }

        int diff = std::abs(rowSum);
        std::cout << "Row " << i << ": sum = " << rowSum << ", diff = " << diff << std::endl;

        if (!found || diff < minDiff) {
            minDiff = diff;
            closestRow = i;
            found = true;
        }
    }

    if (found) {
        std::cout << "The row with the closest sum to 0: " << closestRow << std::endl;

        if (closestRow >= 0 && closestRow < ROWS) {
            for (int j = 0; j < COLS; ++j) {
                matrix[closestRow][j] = 0;
            }
        }
        else {
            std::cout << "Error: Invalid row index!" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "Error: No valid row found!" << std::endl;
        return 1;
    }

    std::cout << "Matrix after processing:" << std::endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
