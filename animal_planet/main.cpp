#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class Vehicle {
protected:
    int maxCargoWeight;

public:
    Vehicle(int cargo) : maxCargoWeight(cargo) {}
    virtual ~Vehicle() {}

    virtual void transportCargo(int currentWeight) {
        cout << "[Транспорт] Проверка возможности перевозки груза весом " << currentWeight << " кг...\n";
        if (currentWeight <= maxCargoWeight) {
            cout << "  => Успешно! Груз закреплен, транспорт отправляется в путь.\n";
        }
        else {
            cout << "  => Отказ! Груз слишком тяжелый для этого вида транспорта.\n";
        }
    }
};

class Herbivore {
protected:
    string name;
    int weight;
    bool life;

public:
    Herbivore(string nm, int wt) : name(nm), weight(wt), life(true) {}
    virtual ~Herbivore() {}

    int getWeight() const { return weight; }
    bool isAlive() const { return life; }
    string getName() const { return name; }

    void setDead() {
        life = false;
        weight = 0;
    }

    virtual void eatGrass() {
        if (!life) return;
        weight += 10;
        cout << "[Травоядное] " << name << " поел траву. Вес увеличился до " << weight << ".\n";
    }
};

class Wildebeest : public Herbivore {
public:
    Wildebeest(int wt = 150) : Herbivore("Антилопа Гну", wt) {}
};

class Bison : public Herbivore {
public:
    Bison(int wt = 300) : Herbivore("Бизон", wt) {}
};

class Reindeer : public Herbivore, public Vehicle {
public:
    
    Reindeer(int wt = 120, int cargo = 80)
        : Herbivore("Северный олень", wt), Vehicle(cargo) {
    }

    void showInfo() {
        cout << "[Олень] Статус: " << (isAlive() ? "Жив" : "Мертв")
            << " | Собственный вес: " << getWeight() << " кг"
            << " | Грузоподъемность: " << maxCargoWeight << " кг\n";
    }
};

class Carnivore {
protected:
    string name;
    int power;

public:
    Carnivore(string nm, int pw) : name(nm), power(pw) {}
    virtual ~Carnivore() {}

    int getPower() const { return power; }
    string getName() const { return name; }

    virtual void eat(Herbivore* target) {
        if (!target->isAlive()) {
            cout << "[Хищник] " << name << " видит, что " << target->getName() << " уже мертв.\n";
            return;
        }

        cout << "[Охота] " << name << " (Сила: " << power << ") атакует "
            << target->getName() << " (Вес: " << target->getWeight() << ")...\n";

        if (power > target->getWeight()) {
            power += 10;
            target->setDead();
            cout << "  => Успех! " << name << " съел добычу. Сила выросла до " << power << ".\n";
        }
        else {
            power -= 10;
            cout << "  => Неудача! Докучать " << target->getName() << " было плохой идеей. "
                << name << " потерял силу. Текущая сила: " << power << ".\n";
        }
    }
};

class Wolf : public Carnivore {
public:
    Wolf(int pw = 100) : Carnivore("Волк", pw) {}
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Тестирование множественного наследования ===\n\n";

    Reindeer* reindeer = new Reindeer(130, 90);

    reindeer->showInfo();

    cout << "\n--- Проверка функций Травоядного ---\n";
    reindeer->eatGrass(); 

    cout << "\n--- Проверка функций Транспорта ---\n";
    reindeer->transportCargo(50); 
    reindeer->transportCargo(120); 

    cout << "\n--- Проверка взаимодействия в экосистеме ---\n";
    Wolf* tundraWolf = new Wolf(150);

    tundraWolf->eat(reindeer);

    cout << "\n";
    reindeer->showInfo();

    delete reindeer;
    delete tundraWolf;

    return 0;
}