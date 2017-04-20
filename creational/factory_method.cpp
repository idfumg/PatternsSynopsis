/*
  Позволяет системе оставаться независимой как от самого процесса порождения
  объектов, так и от их типов.
  Заранее известно, когда нужно создавать объект, но неизвестен его тип.

  Минусы:
  - базовый класс обладает знаниями о производных классах.
  - подобное использование операторы switch в ООП коде не приветствуется.

  Реализация на основе обобщенного конструктора.
 */

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

enum class  Warrior_ID {
    Infantryman_ID,
    Archer_ID,
    Horseman_ID
};

class Warrior {
public:
    virtual void info() const = 0;
    virtual ~Warrior() {}
    static Warrior* createWarrior(const Warrior_ID& id);
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

Warrior* Warrior::createWarrior(const Warrior_ID& id) {
    switch (id) {
    case Warrior_ID::Infantryman_ID:
        return new Infantryman();
    case Warrior_ID::Archer_ID:
        return new Archer();
    case Warrior_ID::Horseman_ID:
        return new Horseman();
    default:
        assert(false);
    }
}

int main() {
    const vector<Warrior*> warriors = {
        Warrior::createWarrior(Warrior_ID::Infantryman_ID),
        Warrior::createWarrior(Warrior_ID::Archer_ID),
        Warrior::createWarrior(Warrior_ID::Horseman_ID)
    };

    for (const Warrior* warrior : warriors)
        warrior->info();

    return 0;
}
