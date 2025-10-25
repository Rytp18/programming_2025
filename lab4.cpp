#include <iostream>
#include <cmath>
#include <climits>

int findMinDigit(int num) {
    if (num == 0) return 0;
    
    int minDigit = 9;
    num = abs(num); 
    
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
    
    std::cout << "Enter " << NMax << " element of massive:" << std::endl;
    for (int i = 0; i < NMax; ++i) {
        std::cin >> arr[i];
    }
    
    int minDigitFirst = findMinDigit(arr[0]);
    int minDigitLast = findMinDigit(arr[NMax - 1]);
    
    std::cout << "min num of 1 num: " << minDigitFirst << std::endl;
    std::cout << "Min num of last num: " << minDigitLast << std::endl;
    
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
        std::cout << "The massive is sorted in ascending order" << std::endl;
    }
    
    std::cout << "Massive after sorting:" << std::endl;
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
    
    for (int i = 0; i < ROWS; ++i) {
        int rowSum = 0;
        for (int j = 0; j < COLS; ++j) {
            rowSum += matrix[i][j];
        }
        
        int diff = abs(rowSum);
        if (diff < minDiff) {
            minDiff = diff;
            closestRow = i;
        }
        
        std::cout << "Summ or row " << i << ": " << rowSum << std::endl;
    }
    
    std::cout << "The row with the closest sum to 0: " << closestRow << std::endl;
    
    // Заменяем все значения в найденной строке на 0
    for (int j = 0; j < COLS; ++j) {
        matrix[closestRow][j] = 0;
    }
    
    std::cout << "Matrix after sorting:" << std::endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
