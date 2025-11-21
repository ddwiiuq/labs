#include <iostream>
#include <cctype>
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

// ф-я проверяющая нули
int* findZeroColumns(int** matrix, int rows, int cols, int* zeroColCount) {
    bool* colHasZero = new bool[cols]();
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

    int* result = (int*)malloc((*zeroColCount) * sizeof(int));
    int idx = 0;
    for (int j = 0; j < cols; ++j) {
        if (colHasZero[j]) {
            result[idx++] = j;
        }
    }

    delete[] colHasZero;
    return result;
}

int** removeColumns(int** matrix, int rows, int cols, int* colsToRemove, int numToRemove, int* newCols) {
    *newCols = cols - numToRemove;
    if (*newCols <= 0) {
        *newCols = 0;
        return nullptr;
    }

    bool* toRemove = new bool[cols]();
    for (int k = 0; k < numToRemove; ++k) {
        if (colsToRemove[k] >= 0 && colsToRemove[k] < cols) {
            toRemove[colsToRemove[k]] = true;
        }
    }

    int** newMat = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        newMat[i] = (int*)malloc((*newCols) * sizeof(int));
    }

    for (int i = 0; i < rows; ++i) {
        int newJ = 0;
        for (int j = 0; j < cols; ++j) {
            if (!toRemove[j]) {
                newMat[i][newJ++] = matrix[i][j];
            }
        }
    }

    delete[] toRemove;
    return newMat;
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

    // расширение изначальной 2x2 матрицы
    int newRows = 2 + A;
    int newCols = 2 + B;

    int** expanded = (int**)malloc(newRows * sizeof(int*));
    for (int i = 0; i < newRows; ++i) {
        expanded[i] = (int*)malloc(newCols * sizeof(int));
    }

    // сохраняем исходную 2x2 [A,B,C,D]
    expanded[0][0] = matrix[0][0];
    expanded[0][1] = matrix[0][1];
    expanded[1][0] = matrix[1][0];
    expanded[1][1] = matrix[1][1];

    // заполняем новые ячейки
    for (int i = 0; i < newRows; ++i) {
        for (int j = 0; j < newCols; ++j) {
            if (i < 2 && j < 2) continue;
            expanded[i][j] = ! * D;
        }
    }

    for (int i = 0; i < 2; ++i) free(matrix[i]);
    free(matrix);
    matrix = expanded;

    cout << "\nМатрица после расширения (" << newRows << "x" << newCols << "):\n";
    printMatrix(matrix, newRows, newCols);

    // ищем нули
    int zeroCount = 0;
    int* zeroCols = findZeroColumns(matrix, newRows, newCols, &zeroCount);

    if (zeroCount > 0) {
        cout << "\nНайдено " << zeroCount << " столбец(ов) с нулями. Индексы: ";
        for (int i = 0; i < zeroCount; ++i) {
            cout << zeroCols[i] << " ";
        }
        cout << "\n";

        int finalCols = 0;
        int** finalMatrix = removeColumns(matrix, newRows, newCols, zeroCols, zeroCount, &finalCols);

        cout << "\nМатрица после удаления столбцов (" << newRows << "x" << finalCols << "):\n";
        printMatrix(finalMatrix, newRows, finalCols);

        if (finalMatrix) {
            for (int i = 0; i < newRows; ++i) free(finalMatrix[i]);
            free(finalMatrix);
        }
    } else {
        cout << "\nНулевых значений не найдено.\n";
    }

    // Освобождение памяти
    for (int i = 0; i < newRows; ++i) free(matrix[i]);
    free(matrix);
    free(zeroCols);

    // == Пункт 2 ==
    cout << "\n Пункт 2: Указатели\n";
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