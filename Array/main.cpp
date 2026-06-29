#include <iostream>
#include <Windows.h>
#include "array_functions.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int size = 5;
    int* myArr = new int[size] { 10, 20, 30, 40, 50 };

    cout << "Исходный массив: ";
    printArray(myArr, size);

    insertAt(myArr, size, 2, 99);
    cout << "После вставки 99 на индекс 2: ";
    printArray(myArr, size);

    insertAtStart(myArr, size, 5);
    cout << "После добавления 5 в начало: ";
    printArray(myArr, size);

    removeAtEnd(myArr, size);
    cout << "После удаления с конца: ";
    printArray(myArr, size);

    removeAt(myArr, size, 3);
    cout << "После удаления элемента на индексе 3: ";
    printArray(myArr, size);

    removeAtStart(myArr, size);
    cout << "После удаления с начала: ";
    printArray(myArr, size);

    delete[] myArr;

    cout << "\n=== Демонстрация очистки двумерного массива ===\n";

    int rows = 3;
    int cols = 4;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    cout << "[Успешно] Память под матрицу " << rows << "x" << cols << " выделена.\n";

    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    
    delete[] matrix;

    matrix = nullptr;

    cout << "[Успешно] Двумерный массив правильно удален из кучи без утечек памяти.\n";

    return 0;
}