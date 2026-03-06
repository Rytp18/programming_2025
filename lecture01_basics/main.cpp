#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void displayArray(const std::vector<int>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

std::vector<int> findElement(const std::vector<int>& arr, int target) {
    std::vector<int> indices;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            indices.push_back(i);
        }
    }
    return indices;
}

void variantTask(std::vector<int>& arr) {
    std::cout << "Array before: ";
    displayArray(arr);

    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] % 2 == 0) {
            arr[i] += 2;
        }
        else {
            arr[i] = -arr[i];
        }
    }

    std::cout << "Array after: ";
    displayArray(arr);
}

void sortByValue(std::array<int, 10> arr, bool ascending) {
    if (ascending) {
        std::sort(arr.begin(), arr.end());
    }
    else {
        std::sort(arr.begin(), arr.end(), std::greater<int>());
    }
    std::cout << "Sorted array (by value): [";
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i];
        if (i != 9) std::cout << " ";
    }
    std::cout << "]" << std::endl;
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

int main() {
    srand(time(0));
    std::vector<int> myVector;
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. View array" << std::endl;
        std::cout << "2. Add element at beginning" << std::endl;
        std::cout << "3. Add element at end" << std::endl;
        std::cout << "4. Clear array" << std::endl;
        std::cout << "5. Find element" << std::endl;
        std::cout << "6. Execute variant task" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 0:
            exitProgram = true;
            break;
        case 1:
            if (myVector.empty()) {
                std::cout << "Array is empty" << std::endl;
            }
            else {
                displayArray(myVector);
            }
            break;
        case 2: {
            int value;
            std::cout << "Enter value: ";
            std::cin >> value;
            myVector.insert(myVector.begin(), value);
            break;
        }
        case 3: {
            int value;
            std::cout << "Enter value: ";
            std::cin >> value;
            myVector.push_back(value);
            break;
        }
        case 4:
            myVector.clear();
            std::cout << "Array cleared" << std::endl;
            break;
        case 5: {
            int target;
            std::cout << "Enter element to find: ";
            std::cin >> target;
            std::vector<int> indices = findElement(myVector, target);
            if (indices.empty()) {
                std::cout << "[]" << std::endl;
            }
            else {
                std::cout << "[";
                for (size_t i = 0; i < indices.size(); ++i) {
                    std::cout << indices[i];
                    if (i != indices.size() - 1) {
                        std::cout << ",";
                    }
                }
                std::cout << "]" << std::endl;
            }
            break;
        }
        case 6:
            if (myVector.empty()) {
                std::cout << "Array is empty. Please add elements first." << std::endl;
            }
            else {
                variantTask(myVector);
            }
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    std::cout << "\n--- Part 2: Array Example ---" << std::endl;

    std::array<int, 10> myArray;

    for (int i = 0; i < 10; ++i) {
        myArray[i] = rand() % 21 - 10;
    }

    std::cout << "Original array: [";
    for (int i = 0; i < 10; ++i) {
        std::cout << myArray[i];
        if (i != 9) std::cout << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "\nSorting demonstration:" << std::endl;
    std::cout << "1. Sorting by value (creates a copy):" << std::endl;
    sortByValue(myArray, true);
    std::cout << "   Original array unchanged: [";
    for (int num : myArray) {
        std::cout << num << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "\n2. Sorting by reference (modifies original):" << std::endl;
    std::array<int, 10> tempArray = myArray;
    sortByReference(tempArray, false);
    std::cout << "   Sorted array: [";
    for (int num : tempArray) {
        std::cout << num << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "\n3. Sorting by pointer (modifies original):" << std::endl;
    sortByPointer(&myArray, true);
    std::cout << "   Sorted array: [";
    for (int num : myArray) {
        std::cout << num << " ";
    }
    std::cout << "]" << std::endl;

    return 0;
}