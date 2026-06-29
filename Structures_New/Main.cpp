#include <iostream>
#include <Windows.h>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Address {
    char* city;
    char* street;
    int houseNumber;
};

struct Student {
    char* lastName;
    char* firstName;
    char* middleName;
    Date birthDate;
    Address homeAddress;
    char* phoneNumber;

    int* termGrades;
    int termGradesCount;

    int* courseGrades;
    int courseGradesCount;

    int* examGrades;
    int examGradesCount;
};

void initStudent(Student& student);
void printStudent(const Student& student);
char* inputString(const char* prompt);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Регистрация и заполнение данных студента ===\n";
    Student student;

    initStudent(student);
    printStudent(student);

    delete[] student.lastName;
    delete[] student.firstName;
    delete[] student.middleName;
    delete[] student.phoneNumber;
    delete[] student.homeAddress.city;
    delete[] student.homeAddress.street;
    delete[] student.termGrades;
    delete[] student.courseGrades;
    delete[] student.examGrades;

    return 0;
} 

char* inputString(const char* prompt) {
    cout << prompt;
    char buffer[256];
    cin.getline(buffer, 256);

    char* str = new char[strlen(buffer) + 1];
    strcpy_s(str, strlen(buffer) + 1, buffer);
    return str;
}

void initStudent(Student& student) {
    student.lastName = inputString("Введите фамилию: ");
    student.firstName = inputString("Введите имя: ");
    student.middleName = inputString("Введите отчество: ");

    cout << "Введите дату рождения (день месяц год через пробел): ";
    cin >> student.birthDate.day >> student.birthDate.month >> student.birthDate.year;
    cin.ignore();

    cout << "--- Заполнение адреса ---\n";
    student.homeAddress.city = inputString("Город: ");
    student.homeAddress.street = inputString("Улица: ");
    cout << "Номер дома: ";
    cin >> student.homeAddress.houseNumber;
    cin.ignore();

    student.phoneNumber = inputString("Введите номер телефона: ");

    cout << "Количество зачётов: ";
    cin >> student.termGradesCount;
    student.termGrades = new int[student.termGradesCount];
    cout << "Введите оценки за зачёты через пробел: ";
    for (int i = 0; i < student.termGradesCount; ++i) {
        cin >> student.termGrades[i];
    }

    cout << "Количество курсовых работ: ";
    cin >> student.courseGradesCount;
    student.courseGrades = new int[student.courseGradesCount];
    cout << "Введите оценки за курсовые через пробел: ";
    for (int i = 0; i < student.courseGradesCount; ++i) {
        cin >> student.courseGrades[i];
    }

    cout << "Количество экзаменов: ";
    cin >> student.examGradesCount;
    student.examGrades = new int[student.examGradesCount];
    cout << "Введите оценки за экзамены через пробел: ";
    for (int i = 0; i < student.examGradesCount; ++i) {
        cin >> student.examGrades[i];
    }
    cin.ignore();
}

void printStudent(const Student& student) {
    cout << "                КАРТОЧКА СТУДЕНТА                 \n";
    cout << "ФИО: " << student.lastName << " " << student.firstName << " " << student.middleName << "\n";
    cout << "Дата рождения: " << student.birthDate.day << "."
        << student.birthDate.month << "." << student.birthDate.year << "\n";
    cout << "Адрес: г. " << student.homeAddress.city << ", ул. "
        << student.homeAddress.street << ", д. " << student.homeAddress.houseNumber << "\n";
    cout << "Телефон: " << student.phoneNumber << "\n";

    cout << "--------------------------------------------------\n";
    cout << "Оценки за зачёты: ";
    for (int i = 0; i < student.termGradesCount; ++i) cout << student.termGrades[i] << " ";
    cout << "\n";

    cout << "Оценки за курсовые: ";
    for (int i = 0; i < student.courseGradesCount; ++i) cout << student.courseGrades[i] << " ";
    cout << "\n";

    cout << "Оценки за экзамены: ";
    for (int i = 0; i < student.examGradesCount; ++i) cout << student.examGrades[i] << " ";
    cout << "\n";
}