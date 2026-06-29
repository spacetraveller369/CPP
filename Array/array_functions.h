#pragma once
#include <iostream>


void insertAt(int*& arr, int& size, int index, int value);
void insertAtStart(int*& arr, int& size, int value);
void removeAtEnd(int*& arr, int& size);
void removeAt(int*& arr, int& size, int index);
void removeAtStart(int*& arr, int& size);
void printArray(const int* arr, int size);


void insertAt(int*& arr, int& size, int index, int value) {
    if (index < 1 || index >= size) {
        std::cout << "[Ошибка] Неверный индекс для вставки в середину!\n";
        return;
    }
    int* newArr = new int[size + 1];

    for (int i = 0; i < index; ++i) {
        newArr[i] = arr[i];
    }
    newArr[index] = value;
    for (int i = index; i < size; ++i) {
        newArr[i + 1] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    size++;
}

void insertAtStart(int*& arr, int& size, int value) {
    int* newArr = new int[size + 1];
    newArr[0] = value;
    for (int i = 0; i < size; ++i) {
        newArr[i + 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size++;
}

void removeAtEnd(int*& arr, int& size) {
    if (size <= 0) return;
    int* newArr = new int[size - 1];
    for (int i = 0; i < size - 1; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void removeAt(int*& arr, int& size, int index) {
    if (index < 0 || index >= size) {
        std::cout << "[Ошибка] Индекс вне диапазона массива!\n";
        return;
    }
    int* newArr = new int[size - 1];
    for (int i = 0; i < index; ++i) {
        newArr[i] = arr[i];
    }
    for (int i = index + 1; i < size; ++i) {
        newArr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void removeAtStart(int*& arr, int& size) {
    if (size <= 0) return;
    int* newArr = new int[size - 1];
    for (int i = 1; i < size; ++i) {
        newArr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void printArray(const int* arr, int size) {
    if (size == 0) {
        std::cout << "Массив пуст\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
