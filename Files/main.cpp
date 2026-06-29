#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

int main() {
    
    SetConsoleCP(1251);       
    SetConsoleOutputCP(1251); 

    string theme;
    string word;

    cout << "=== Программа распределения слов по темам ===\n";

    cout << "Введите название темы (например: цветы, животные, авто): ";
    cin >> theme;

    cout << "Введите существительное, соответствующее этой теме: ";
    cin >> word;

    string fileName = theme + ".txt";

    ofstream outputFile(fileName, ios::app);

    if (outputFile.is_open()) {
        outputFile << word << "\n";
        outputFile.close();

        cout << "\n[Успешно] Слово \"" << word << "\" добавлено в файл \"" << fileName << "\"!\n";
    }
    else {
        cout << "\n[Ошибка] Не удалось открыть или создать файл.\n";
    }

    return 0;
}