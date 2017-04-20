/*
  Позволяет изменять поведение системы, варьируя создаваемыми объектами,
  при этом сохраняя интерфейсы. Позволяет создавать целые группы взаимосвязанных
  объектов, которые, будучи созданными одной фабрикой, реализуют общее
  поведение.
  Реализуется созданием абстрактного класса Factory, который представляет
  собой интерфейс для создания компонентов системы. Затем пишутся классы,
  реализующие этот интерфейс.

  Используется, если необходимо создавать группы взаимосвязанных объектов,
  исключая возможность одновременного использования объектов из разных
  семейств в одном контексте.

  Реализуется на основе фабричных методов.
 */

#include <iostream>
#include <vector>

using namespace std;

class Warrior {
public:
    virtual ~Warrior() {}
    virtual void info() = 0;
};

class Infantryman : public Warrior {
public:
    virtual ~Infantryman() {}
    virtual void info() = 0;
};

class Archer : public Warrior {
public:
    virtual ~Archer() {}
    virtual void info() = 0;
};

class Horseman : public Warrior {
public:
    virtual ~Horseman() {}
    virtual void info() = 0;
};

class RomanInfantryman : public Infantryman {
public:
    void info() {
        cout << "RomanInfantryman" << endl;
    }
};

class RomanArcher : public Archer {
public:
    void info() {
        cout << "RomanArcher" << endl;
    }
};

class RomanHorseman : public Horseman {
public:
    void info() {
        cout << "RomanHorseman" << endl;
    }
};

class CarthaginianInfantryman : public Infantryman {
public:
    void info() {
        cout << "CarthaginianInfantryman" << endl;
    }
};

class CarthaginianArcher : public Archer {
public:
    void info() {
        cout << "CarthaginianArcher" << endl;
    }
};

class CarthaginianHorseman : public Horseman {
public:
    void info() {
        cout << "CarthaginianHorseman" << endl;
    }
};

class ArmyFactory {
public:
    virtual ~ArmyFactory() {}
    virtual Infantryman* createInfantryman() = 0;
    virtual Archer* createArcher() = 0;
    virtual Horseman* createHorseman() = 0;
};

class RomanArmyFactory : public ArmyFactory {
public:
    Infantryman* createInfantryman() {
        return new RomanInfantryman;
    }

    Archer* createArcher() {
        return new RomanArcher;
    }

    Horseman* createHorseman() {
        return new RomanHorseman;
    }
};

class CarthaginianArmyFactory : public ArmyFactory {
public:
    Infantryman* createInfantryman() {
        return new CarthaginianInfantryman;
    }

    Archer* createArcher() {
        return new CarthaginianArcher;
    }

    Horseman* createHorseman() {
        return new CarthaginianHorseman;
    }
};

class Army {
public:
    ~Army() {
        for (Infantryman* i : vi)
            delete i;
        for (Archer* a : va)
            delete a;
        for (Horseman* h : vh)
            delete h;
    }

    void info() {
        for (Infantryman* i : vi)
            i->info();
        for (Archer* a : va)
            a->info();
        for (Horseman* h : vh)
            h->info();
    }

    vector<Infantryman*> vi;
    vector<Archer*> va;
    vector<Horseman*> vh;
};

class Game {
public:
    Army* createArmy(ArmyFactory& factory) {
        Army* rv = new Army;

        rv->vi.push_back(factory.createInfantryman());
        rv->va.push_back(factory.createArcher());
        rv->vh.push_back(factory.createHorseman());

        return rv;
    }
};

int main() {
    Game game;
    RomanArmyFactory ra_factory;
    CarthaginianArmyFactory ca_factory;

    Army* ra = game.createArmy(ra_factory);
    Army* ca = game.createArmy(ca_factory);

    cout << "Roman army:" << std::endl;
    ra->info();
    cout << "Carthaginian army:" << std::endl;
    ca->info();

    delete ra;
    delete ca;

    return 0;
}
