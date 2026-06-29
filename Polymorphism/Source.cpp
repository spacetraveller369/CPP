#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <Windows.h>

using namespace std;

class Device {
protected:
    string manufacturer; 
    string model;        
    string name;         
    int capacity;        
    int count;           

public:
    Device(string man, string mod, string nm, int cap, int cnt)
        : manufacturer(man), model(mod), name(nm), capacity(cap), count(cnt) {
    }

    virtual ~Device() {}

    string getManufacturer() const { return manufacturer; }
    string getModel() const { return model; }
    string getName() const { return name; }
    int getCapacity() const { return capacity; }
    int getCount() const { return count; }

    void setCapacity(int cap) { capacity = cap; }
    void setCount(int cnt) { count = cnt; }

    virtual void print() const {
        cout << "Производитель: " << manufacturer << " | Модель: " << model
            << " | Имя: " << name << " | Емкость: " << capacity << " ГБ | Кол-во: " << count;
    }

    virtual void save() const {
        cout << "[Device] Данные устройства \"" << name << "\" сохранены.\n";
    }

    virtual void load() {
        cout << "[Device] Данные устройства \"" << name << "\" загружены.\n";
    }
};

class HardDrive : public Device {
public:
    HardDrive(string man, string mod, string nm, int cap, int cnt)
        : Device(man, mod, nm, cap, cnt) {
    }

    void print() const override {
        cout << "[Жесткий диск] ";
        Device::print();
        cout << "\n";
    }
    void save() const override { cout << "[HDD] Данные жесткого диска успешно сохранены.\n"; }
    void load() override { cout << "[HDD] Данные жесткого диска успешно загружены.\n"; }
};

class Smartphone : public Device {
public:
    Smartphone(string man, string mod, string nm, int cap, int cnt)
        : Device(man, mod, nm, cap, cnt) {
    }

    void print() const override {
        cout << "[Смартфон]    ";
        Device::print();
        cout << "\n";
    }
    void save() const override { cout << "[Phone] Данные смартфона успешно сохранены.\n"; }
    void load() override { cout << "[Phone] Данные смартфона успешно загружены.\n"; }
};

class Tablet : public Device {
public:
    Tablet(string man, string mod, string nm, int cap, int cnt)
        : Device(man, mod, nm, cap, cnt) {
    }

    void print() const override {
        cout << "[Планшет]     ";
        Device::print();
        cout << "\n";
    }
    void save() const override { cout << "[Tablet] Данные планшета успешно сохранены.\n"; }
    void load() override { cout << "[Tablet] Данные планшета успешно загружены.\n"; }
};

void showMenu() {
    cout << "\n--- МЕНЮ УПРАВЛЕНИЯ НОСИТЕЛЯМИ ---\n";
    cout << "1. Показать список всех носителей\n";
    cout << "2. Добавить новый носитель\n";
    cout << "3. Удалить носитель (по номеру)\n";
    cout << "4. Изменить параметры (емкость/количество по номеру)\n";
    cout << "5. Поиск по производителю\n";
    cout << "6. Использовать typeid для подсчета типов\n";
    cout << "7. Вызвать методы сохранения/загрузки для всех\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Device*> list;

    list.push_back(new HardDrive("WD", "MyPassport", "Внешний HDD 1", 2000, 5));
    list.push_back(new Smartphone("Apple", "iPhone 15", "Основной телефон", 256, 3));
    list.push_back(new Tablet("Samsung", "Galaxy Tab S9", "Рабочий планшет", 128, 2));

    int choice;
    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- СПИСОК НОСИТЕЛЕЙ ---\n";
            if (list.empty()) cout << "Список пуст.\n";
            for (size_t i = 0; i < list.size(); ++i) {
                cout << i + 1 << ". ";
                list[i]->print(); 
            }
        }
        else if (choice == 2) {
            int type, cap, cnt;
            string man, mod, nm;
            cout << "\nКакое устройство добавить? (1 - HDD, 2 - Смартфон, 3 - Планшет): ";
            cin >> type;
            cin.ignore();
            cout << "Производитель: "; getline(cin, man);
            cout << "Модель: "; getline(cin, mod);
            cout << "Наименование: "; getline(cin, nm);
            cout << "Емкость (ГБ): "; cin >> cap;
            cout << "Количество: "; cin >> cnt;

            if (type == 1) list.push_back(new HardDrive(man, mod, nm, cap, cnt));
            else if (type == 2) list.push_back(new Smartphone(man, mod, nm, cap, cnt));
            else if (type == 3) list.push_back(new Tablet(man, mod, nm, cap, cnt));
            else cout << "Неверный тип устройства.\n";
        }
        else if (choice == 3) {
            if (list.empty()) { cout << "Нечего удалять.\n"; continue; }
            int num;
            cout << "Введите номер удаляемого устройства (1-" << list.size() << "): ";
            cin >> num;
            if (num > 0 && num <= (int)list.size()) {
                delete list[num - 1];
                list.erase(list.begin() + (num - 1));
                cout << "Успешно удалено.\n";
            }
            else cout << "Неверный номер.\n";
        }
        else if (choice == 4) {
            if (list.empty()) { cout << "Список пуст.\n"; continue; }
            int num, newCap, newCnt;
            cout << "Введите номер устройства для изменения (1-" << list.size() << "): ";
            cin >> num;
            if (num > 0 && num <= (int)list.size()) {
                cout << "Текущие данные: "; list[num - 1]->print();
                cout << "Введите новую емкость (ГБ): "; cin >> newCap;
                cout << "Введите новое количество: "; cin >> newCnt;
                list[num - 1]->setCapacity(newCap);
                list[num - 1]->setCount(newCnt);
                cout << "Параметры изменены.\n";
            }
            else cout << "Неверный номер.\n";
        }
        else if (choice == 5) {
            cin.ignore();
            string searchMan;
            cout << "Введите производителя для поиска: ";
            getline(cin, searchMan);
            bool found = false;
            for (auto dev : list) {
                if (dev->getManufacturer() == searchMan) {
                    dev->print();
                    found = true;
                }
            }
            if (!found) cout << "Ничего не найдено.\n";
        }
        else if (choice == 6) {
            
            cout << "\n--- Идентификация типов через typeid ---\n";
            int hddCount = 0, phoneCount = 0, tabletCount = 0;

            for (size_t i = 0; i < list.size(); ++i) {
               
                const type_info& typeInfo = typeid(*list[i]);
                cout << "Устройство №" << i + 1 << " имеет системный тип: " << typeInfo.name() << "\n";

                if (typeInfo == typeid(HardDrive)) hddCount++;
                else if (typeInfo == typeid(Smartphone)) phoneCount++;
                else if (typeInfo == typeid(Tablet)) tabletCount++;
            }
            cout << "\nИтого статистика:\n- Жестких дисков: " << hddCount
                << "\n- Смартфонов: " << phoneCount << "\n- Планшетов: " << tabletCount << "\n";
        }
        else if (choice == 7) {
            cout << "\n--- Тестирование виртуальных методов Сохранения/Загрузки ---\n";
            for (auto dev : list) {
                dev->save();
                dev->load();
                cout << "-----------------------\n";
            }
        }

    } while (choice != 0);

    for (auto dev : list) {
        delete dev;
    }
    list.clear();

    return 0;
}