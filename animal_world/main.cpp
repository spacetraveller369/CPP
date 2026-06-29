#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

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

class Lion : public Carnivore {
public:
    Lion(int pw = 200) : Carnivore("Лев", pw) {}
};

class Wolf : public Carnivore {
public:
    Wolf(int pw = 100) : Carnivore("Волк", pw) {}
};

class Continent {
public:
    virtual ~Continent() {}
    virtual Herbivore* createHerbivore() = 0;
    virtual Carnivore* createCarnivore() = 0;
    virtual string getContinentName() const = 0;
};

class Africa : public Continent {
public:
    Herbivore* createHerbivore() override { return new Wildebeest(); }
    Carnivore* createCarnivore() override { return new Lion(); }
    string getContinentName() const override { return "Африка"; }
};

class NorthAmerica : public Continent {
public:
    Herbivore* createHerbivore() override { return new Bison(); }
    Carnivore* createCarnivore() override { return new Wolf(); }
    string getContinentName() const override { return "Северная Америка"; }
};

class AnimalWorld {
private:
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;

public:
  
    void populate(Continent* continent) {
        cout << "\n=== Заселение континента: " << continent->getContinentName() << " ===\n";
        herbivores.push_back(continent->createHerbivore());
        carnivores.push_back(continent->createCarnivore());
    }

    
    ~AnimalWorld() {
        for (auto h : herbivores) delete h;
        for (auto c : carnivores) delete c;
        herbivores.clear();
        carnivores.clear();
    }

    void mealsHerbivores() {
        cout << "\n--- [Событие] Все травоядные выходят щипать травку ---\n";
        for (auto h : herbivores) {
            if (h->isAlive()) h->eatGrass();
        }
    }

    void nutritionCarnivores() {
        cout << "\n--- [Событие] Наступает ночь. Хищники выходят на охоту ---\n";
        for (size_t i = 0; i < carnivores.size(); ++i) {
            
            if (i < herbivores.size()) {
                carnivores[i]->eat(herbivores[i]);
            }
        }
    }

    void showStatus() {
        cout << "\n--- ТЕКУЩИЙ СТАТУС МИРА ЖИВОТНЫХ ---\n";
        cout << "Травоядные:\n";
        for (auto h : herbivores) {
            cout << "  - " << h->getName() << ": " << (h->isAlive() ? "Жив, вес " + to_string(h->getWeight()) : "Мертв") << "\n";
        }
        cout << "Хищники:\n";
        for (auto c : carnivores) {
            cout << "  - " << c->getName() << ", сила: " << c->getPower() << "\n";
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    AnimalWorld world;

    Continent* africa = new Africa();
    Continent* america = new NorthAmerica();

    world.populate(africa);
    world.populate(america);

    world.showStatus();

    world.mealsHerbivores();
    world.showStatus();

    world.nutritionCarnivores();
    world.showStatus();

    delete africa;
    delete america;

    return 0;
}