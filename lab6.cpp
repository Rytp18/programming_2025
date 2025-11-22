#include <iostream>

using namespace std;

int* findZeroColumns(int** matrix, int rows, int cols, int& zeroCount) {
    zeroCount = 0;
    
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                zeroCount++;
                break;
            }
        }
    }
    
    if (zeroCount == 0) return nullptr;
    
    int* zeroColumns = new int[zeroCount];
    
    int index = 0;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                zeroColumns[index++] = j;
                break;
            }
        }
    }
    
    return zeroColumns;
}

void processMatrix() {
    cout << "=== Punkt 1 - massives ===" << endl;
    
    int** matrix = new int*[2];
    for (int i = 0; i < 2; i++) {
        matrix[i] = new int[2];
    }
    
    int A, B, C, D;
    
    do {
        cout << "Enter A (neotricatelnoe): ";
        cin >> A;
        if (A < 0) cout << "Error! A must be neotricatelnim." << endl;
    } while (A < 0);
    
    do {
        cout << "enter B (neotricatelnoe): ";
        cin >> B;
        if (B < 0) cout << "Error! B must be neotricatelnyum." << endl;
    } while (B < 0);
    
    cout << "Enter C: ";
    cin >> C;
    cout << "Enter D: ";
    cin >> D;
    
    matrix[0][0] = A;
    matrix[0][1] = B;
    matrix[1][0] = C;
    matrix[1][1] = D;
    
    cout << "\nNachalnaya matrix 2x2:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    int newRows = 2 + A;
    int newCols = 2 + B;
    
    int** newMatrix = new int*[newRows];
    for (int i = 0; i < newRows; i++) {
        newMatrix[i] = new int[newCols];
    }
    
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            if (i < 2 && j < 2) {
                newMatrix[i][j] = matrix[i][j];
            } else {
                newMatrix[i][j] = (i - 1) * C + (j - 2) * D;
            }
        }
    }
    
    cout << "\nUvelichennaya matrix " << newRows << "x" << newCols << ":" << endl;
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            cout << newMatrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    int zeroCount;
    int* zeroColumns = findZeroColumns(newMatrix, newRows, newCols, zeroCount);
    
    cout << "\nStolbci with nulevimi znacheniyami: ";
    if (zeroCount > 0) {
        for (int i = 0; i < zeroCount; i++) {
            cout << zeroColumns[i] << " ";
        }
        cout << endl;
        
        int finalCols = newCols - zeroCount;
        int** finalMatrix = new int*[newRows];
        
        for (int i = 0; i < newRows; i++) {
            finalMatrix[i] = new int[finalCols];
            int newJ = 0;
            for (int j = 0; j < newCols; j++) {
                bool skip = false;
                for (int k = 0; k < zeroCount; k++) {
                    if (j == zeroColumns[k]) {
                        skip = true;
                        break;
                    }
                }
                if (!skip) {
                    finalMatrix[i][newJ++] = newMatrix[i][j];
                }
            }
        }
        
        cout << "\nFinal matrix after delete stolbcov " << newRows << "x" << finalCols << ":" << endl;
        for (int i = 0; i < newRows; i++) {
            for (int j = 0; j < finalCols; j++) {
                cout << finalMatrix[i][j] << "\t";
            }
            cout << endl;
        }

        for (int i = 0; i < newRows; i++) {
            delete[] finalMatrix[i];
        }
        delete[] finalMatrix;
    } else {
        cout << "no nulevih stolbcov" << endl;
    }
    
    for (int i = 0; i < 2; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    for (int i = 0; i < newRows; i++) {
        delete[] newMatrix[i];
    }
    delete[] newMatrix;
    
    if (zeroColumns) delete[] zeroColumns;
}
void processPointers() {
    cout << "\n=== punkt 2 - ukazateliand adesa ===" << endl;
    
    double a, b;
    
    cout << "enter znachenie peremennoi a: ";
    cin >> a;
    cout << "enter znachenie peremennoi b: ";
    cin >> b;
    
    cout << "\nIshodnie znacheniya:" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    
    double* ptrA = new double;
    double* ptrB = new double;
    
    *ptrA = a;
    *ptrB = b;
    
    cout << "adresa peremennih:" << endl;
    cout << "adress a: " << &a << ", adress b: " << &b << endl;
    cout << "ukazatel ptrA: " << ptrA << ", ukazatel ptrB: " << ptrB << endl;
    
    *ptrA *= 3;
    cout << "\nAfter uvelucheniya a v 3 raza:" << endl;
    cout << "a = " << *ptrA << ", b = " << *ptrB << endl;
    
    double temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;
    
    cout << "\nAfter obmena znachenyi:" << endl;
    cout << "a = " << *ptrA << ", b = " << *ptrB << endl;
    
    a = *ptrA;
    b = *ptrB;
    
    cout << "ishodnie peremennie after obmen:" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    
    delete ptrA;
    delete ptrB;
}

int main() {
    processMatrix();
    processPointers();
    
    return 0;
}
