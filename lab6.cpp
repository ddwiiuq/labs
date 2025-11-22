#include <iostream>
#include <cctype>
#include <cstdlib>
#include <limits>
using namespace std;

int readInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            int next = cin.peek();
            if (next == EOF || next == '\n' || next == ' ' || next == '\t' || next == '\r') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
        cout << "Ошибка: введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readDouble(const char* prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "Ошибка: введите вещественное число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int* findZeroColumns(int** matrix, int rows, int cols, int* zeroColCount) {
    bool* colHasZero = (bool*)calloc(cols, sizeof(bool));
    *zeroColCount = 0;

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (matrix[i][j] == 0) {
                colHasZero[j] = true;
                break;
            }
        }
        if (colHasZero[j]) {
            (*zeroColCount)++;
        }
    }

    int* result = nullptr;
    if (*zeroColCount > 0) {
        result = (int*)malloc((*zeroColCount) * sizeof(int));
        int idx = 0;
        for (int j = 0; j < cols; ++j) {
            if (colHasZero[j]) {
                result[idx++] = j;
            }
        }
    }
    free(colHasZero);
    return result;
}

void removeZeroColumnsInPlace(int** matrix, int rows, int* cols, int* colsToRemove, int numToRemove) {
    if (numToRemove == 0 || *cols == 0) return;

    bool* toRemove = (bool*)calloc(*cols, sizeof(bool));
    for (int k = 0; k < numToRemove; ++k) {
        if (colsToRemove[k] >= 0 && colsToRemove[k] < *cols) {
            toRemove[colsToRemove[k]] = true;
        }
    }

    int newCols = *cols - numToRemove;
    if (newCols <= 0) {
        for (int i = 0; i < rows; ++i) {
            free(matrix[i]);
            matrix[i] = nullptr;
        }
        *cols = 0;
        free(toRemove);
        return;
    }

    for (int i = 0; i < rows; ++i) {
        int writeIndex = 0;
        for (int readIndex = 0; readIndex < *cols; ++readIndex) {
            if (!toRemove[readIndex]) {
                matrix[i][writeIndex] = matrix[i][readIndex];
                writeIndex++;
            }
        }
        int* temp = (int*)realloc(matrix[i], newCols * sizeof(int));
        if (temp) {
            matrix[i] = temp;
        }
    }

    *cols = newCols;
    free(toRemove);
}

void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == nullptr || cols == 0) {
        cout << "Матрица пуста.\n";
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout.width(5);
            cout << matrix[i][j];
        }
        cout << '\n';
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    // === Пункт 1 ===
    int** matrix = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; ++i) {
        matrix[i] = (int*)malloc(2 * sizeof(int));
    }

    cout << "Введите элементы начальной матрицы 2x2 (целые числа):\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            matrix[i][j] = readInt("");
        }
    }

    int A, B, C, D;
    while (true) {
        A = readInt("Введите A (строки для добавления снизу): ");
        if (A >= 0) break;
        cout << "Ошибка: A должно быть >= 0.\n";
    }
    while (true) {
        B = readInt("Введите B (столбцы для добавления справа): ");
        if (B >= 0) break;
        cout << "Ошибка: B должно быть >= 0.\n";
    }
    C = readInt("Введите C (целое): ");
    D = readInt("Введите D (целое): ");

    int rows = 2;
    int cols = 2;

    if (A > 0) {
        int** temp = (int**)realloc(matrix, (rows + A) * sizeof(int*));
        if (!temp) { cerr << "Ошибка памяти\n"; return 1; }
        matrix = temp;
        for (int i = rows; i < rows + A; ++i) {
            matrix[i] = (int*)malloc((cols + B) * sizeof(int));
        }
        rows += A;
    }

    if (B > 0) {
        for (int i = 0; i < rows; ++i) {
            int* temp = (int*)realloc(matrix[i], (cols + B) * sizeof(int));
            if (!temp) { cerr << "Ошибка памяти\n"; return 1; }
            matrix[i] = temp;
        }
        cols += B;
    }

    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i < 2 && j < 2) continue; 
            matrix[i][j] = (i - 1) * C + (j - 1) * D;
        }
    }

    cout << "\nМатрица после расширения (" << rows << "x" << cols << "):\n";
    printMatrix(matrix, rows, cols);

    int zeroCount = 0;
    int* zeroCols = findZeroColumns(matrix, rows, cols, &zeroCount);

    if (zeroCount > 0) {
        cout << "\nНайдено " << zeroCount << " столбец(ов) с нулями. Индексы: ";
        for (int i = 0; i < zeroCount; ++i) {
            cout << zeroCols[i] << " ";
        }
        cout << "\n";

        removeZeroColumnsInPlace(matrix, rows, &cols, zeroCols, zeroCount);

        cout << "\nМатрица после удаления столбцов (" << rows << "x" << cols << "):\n";
        printMatrix(matrix, rows, cols);
    } else {
        cout << "\nНулевых значений не найдено.\n";
    }

    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(zeroCols);

    // === Пункт 2 ===
    cout << "\nПункт 2: Указатели\n";
    double* a = new double;
    double* b = new double;

    *a = readDouble("Введите вещественное a: ");
    *b = readDouble("Введите вещественное b: ");

    cout << "До: a = " << *a << ", b = " << *b << "\n";

    *a *= 3;
    double temp = *a;
    *a = *b;
    *b = temp;

    cout << "После: a = " << *a << ", b = " << *b << "\n";

    delete a;
    delete b;

    return 0;
}
