#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <algorithm>
void displayMenu();
void showVector(const std::vector<int>& vec);
void showArray(const std::array<int, 10>& arr);
void processVariant(std::vector<int>& vec);
void variantTask(std::vector<int>& vec);
void variantFive(std::vector<int>& vec);
void searchInVector(const std::vector<int>& vec, int value);
void sortByValue(std::array<int, 10> arr, bool ascending);
void sortByReference(std::array<int, 10>& arr, bool ascending);
void sortByPointer(std::array<int, 10>* arr, bool ascending);

int main() {
    std::srand(std::time(nullptr));

    std::vector<int> numbers;
    std::array<int, 10> fixedArray;

    int choice;
    do {
        displayMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 0:
            std::cout << "Exit program.\n";
            break;

        case 1:
            showVector(numbers);
            break;

        case 2: {
            int value;
            std::cout << "Enter value: ";
            std::cin >> value;
            numbers.insert(numbers.begin(), value);
            break;
        }

        case 3: {
            int value;
            std::cout << "Enter value: ";
            std::cin >> value;
            numbers.push_back(value);
            break;
        }

        case 4:
            numbers.clear();
            std::cout << "Vector cleared.\n";
            break;

        case 5: {
            int value;
            std::cout << "Enter value to search: ";
            std::cin >> value;
            searchInVector(numbers, value);
            break;
        }

        case 6:
            processVariant(numbers);
            break;

        default:
            std::cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

void displayMenu() {
    std::cout << "\n=== Menu ===\n";
    std::cout << "0. Exit\n";
    std::cout << "1. View array\n";
    std::cout << "2. Add element to beginning\n";
    std::cout << "3. Add element to end\n";
    std::cout << "4. Clear array\n";
    std::cout << "5. Search element\n";
    std::cout << "6. Process variant task\n";
}

void showVector(const std::vector<int>& vec) {
    if (vec.empty()) {
        std::cout << "Array is empty\n";
        return;
    }

    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]\n";
}

void searchInVector(const std::vector<int>& vec, int value) {
    std::vector<size_t> indices;

    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        std::cout << "[]\n";
    }
    else {
        std::cout << "[";
        for (size_t i = 0; i < indices.size(); ++i) {
            std::cout << indices[i];
            if (i != indices.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]\n";
    }
}

void processVariant(std::vector<int>& vec) {
    if (vec.empty()) {
        std::cout << "Array is empty. Add some elements first.\n";
        return;
    }

    std::cout << "Original array: ";
    showVector(vec);

    int variantChoice;
    std::cout << "Select variant (1 or 5): ";
    std::cin >> variantChoice;

    if (variantChoice == 1) {
        variantTask(vec);
    }
    else if (variantChoice == 5) {
        variantFive(vec);
    }
    else {
        std::cout << "Invalid variant choice!\n";
    }
}
void variantTask(std::vector<int>& vec) {
    std::vector<int> result = vec;

    for (int& num : result) {
        if (num % 2 == 0) {
            num += 2;
        }
        else {
            num = -num;
        }
    }

    std::cout << "Result array: ";
    showVector(result);
}

void variantFive(std::vector<int>& vec) {
    int K;
    std::cout << "Enter K value: ";
    std::cin >> K;

    int sum = 0;
    int n = 0;

    while (sum < K) {
        n++;
        sum += n;
    }

    if (sum != K) {
        std::cout << "Cannot represent K as sum of consecutive numbers\n";
        return;
    }

    std::vector<int> newVec(vec.size() + n, 0);

    int leftPos = 0;
    int rightPos = newVec.size() - 1;

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            newVec[leftPos++] = i;
        }
        else {
            newVec[rightPos--] = i;
        }
    }

    for (size_t i = 0; i < vec.size(); i++) {
        newVec[leftPos + i] = vec[i];
    }

    std::cout << "Result array: ";
    showVector(newVec);
}

void showArray(const std::array<int, 10>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]\n";
}

void sortByValue(std::array<int, 10> arr, bool ascending) {
    if (ascending) {
        std::sort(arr.begin(), arr.end());
    }
    else {
        std::sort(arr.begin(), arr.end(), std::greater<int>());
    }

    std::cout << "Array after sort by value: ";
    showArray(arr);
}

void sortByReference(std::array<int, 10>& arr, bool ascending) {
    if (ascending) {
        std::sort(arr.begin(), arr.end());
    }
    else {
        std::sort(arr.begin(), arr.end(), std::greater<int>());
    }
}

void sortByPointer(std::array<int, 10>* arr, bool ascending) {
    if (ascending) {
        std::sort(arr->begin(), arr->end());
    }
    else {
        std::sort(arr->begin(), arr->end(), std::greater<int>());
    }
}

void demonstrateArrayFunctions() {
    std::cout << "\n=== Array Demonstration ===\n";

    std::array<int, 10> myArray;

    for (int i = 0; i < 10; i++) {
        myArray[i] = std::rand() % 21 - 10;
    }

    std::cout << "Original array: ";
    showArray(myArray);

    std::array<int, 10> copy1 = myArray;
    sortByValue(copy1, true);
    std::cout << "Original array unchanged: ";
    showArray(myArray);

    std::array<int, 10> copy2 = myArray;
    sortByReference(copy2, false);
    std::cout << "Array after sort by reference: ";
    showArray(copy2);

    std::array<int, 10> copy3 = myArray;
    sortByPointer(&copy3, true);
    std::cout << "Array after sort by pointer: ";
    showArray(copy3);

    std::cout << "\n=== Explanation ===\n";
    std::cout << "1. Pass by value: Creates a copy, original unchanged\n";
    std::cout << "2. Pass by reference: Modifies the original array\n";
    std::cout << "3. Pass by pointer: Same as reference but using pointer syntax\n";
}
