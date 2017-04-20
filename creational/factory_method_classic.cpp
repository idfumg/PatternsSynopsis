/*
  Классический вариант паттерна Factory Method использует идею
  полиморфной фабрики. Специально выделенный для создания объектов
  полиморфный базовый класс Factory объявляет интерфейс
  фабричного метода createWarrior(), а производные классы его
  реализуют.
 */

#include <iostream>
#include <vector>

using namespace std;

class Warrior {
public:
    virtual void info() const = 0;
    virtual ~Warrior() {}
};

class Infantryman : public Warrior {
public:
    void info() const {
        std::cout << "Infantryman" << std::endl;
    }
};

class Archer : public Warrior {
public:
    void info() const {
        std::cout << "Archer" << std::endl;
    }
};

class Horseman : public Warrior {
public:
    void info() const {
        std::cout << "Horseman" << std::endl;
    }
};

class Factory {
public:
    virtual Warrior* createWarrior() = 0;
    virtual ~Factory() {}
};

class InfantryFactory : public Factory {
public:
    Warrior* createWarrior() {
        return new Infantryman;
    }
};

class ArcherFactory : public Factory {
public:
    Warrior* createWarrior() {
        return new Archer;
    }
};

class HorsemanFactory : public Factory {
public:
    Warrior* createWarrior() {
        return new Horseman;
    }
};

int main() {
    InfantryFactory* infantry_factory = new InfantryFactory;
    ArcherFactory* archer_factory = new ArcherFactory;
    HorsemanFactory* horseman_factory = new HorsemanFactory;

    const vector<Warrior*> warriors = {
        infantry_factory->createWarrior(),
        archer_factory->createWarrior(),
        horseman_factory->createWarrior()
    };

    for (const Warrior* warrior: warriors)
        warrior->info();

    return 0;
}
