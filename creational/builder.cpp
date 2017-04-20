/*
  В системе могут существовать сложные объекты, создание которых
  за одну операцию затруднительно или невозможно. Требуется
  поэтапное создание с контролем результатов выполнения
  каждого этапа.
  Данные могут иметь несколько предствалений.

  Паттерн Builder отделяет алгоритм поэтапного конструирования
  сложного продукта от его внешнего представления так, что с
  помощью одного и того же алгоритма можно получать разные
  представления этого продукта.


 */

#include <iostream>
#include <vector>

using namespace std;

class Infantryman {
public:
    void info() const {
        cout << "Infantryman" << endl;
    }
};

class Archer {
public:
    void info() const {
        cout << "Archer" << endl;
    }
};

class Horseman {
public:
    void info() const {
        cout << "Horseman" << endl;
    }
};

class Catapult {
public:
    void info() const {
        cout << "Catapult" << endl;
    }
};

class Elephant {
public:
    void info() const {
        cout << "Elephant" << endl;
    }
};

class Army {
public:
    vector<Infantryman*> vi;
    vector<Archer*> va;
    vector<Horseman*> vh;
    vector<Catapult*> vc;
    vector<Elephant*> ve;

    void info() const {
        for (Infantryman* p : vi)
            p->info();
        for (Archer* p : va)
            p->info();
        for (Horseman* p : vh)
            p->info();
        for (Catapult* p : vc)
            p->info();
        for (Elephant* p : ve)
            p->info();
    }

    ~Army() {
        for (Infantryman* p : vi)
            delete p;
        for (Archer* p : va)
            delete p;
        for (Horseman* p : vh)
            delete p;
        for (Catapult* p : vc)
            delete p;
        for (Elephant* p : ve)
            delete p;
    }
};

class ArmyBuilder {
public:
    ArmyBuilder() : army(0) {}
    virtual ~ArmyBuilder() {}
    virtual void createArmy() {}
    virtual void buildInfantryman() {}
    virtual void buildArcher() {}
    virtual void buildHorseman() {}
    virtual void buildCatapult() {}
    virtual void buildElephant() {}
    virtual Army* getArmy() {
        return this->army;
    }

protected:
    Army* army;
};

class RomanArmyBuilder : public ArmyBuilder {
public:
    void createArmy() {
        this->army = new Army;
    }

    void buildInfantryman() {
        this->army->vi.push_back(new Infantryman);
    }

    void buildArcher() {
        this->army->va.push_back(new Archer);
    }

    void buildHorseman() {
        this->army->vh.push_back(new Horseman);
    }

    void buildCatapult() {
        this->army->vc.push_back(new Catapult);
    }
};

class CarthaginianArmyBuilder : public ArmyBuilder {
public:
    void createArmy() {
        this->army = new Army;
    }

    void buildInfantryman() {
        this->army->vi.push_back(new Infantryman);
    }

    void buildArcher() {
        this->army->va.push_back(new Archer);
    }

    void buildHorseman() {
        this->army->vh.push_back(new Horseman);
    }

    void buildElephant() {
        this->army->ve.push_back(new Elephant);
    }
};

class Director {
public:
    Army* createArmy(ArmyBuilder& builder) {
        builder.createArmy();
        builder.buildInfantryman();
        builder.buildArcher();
        builder.buildHorseman();
        builder.buildCatapult();
        builder.buildElephant();
        return builder.getArmy();
    }
};

int main() {
    Director director;
    RomanArmyBuilder ra_builder;
    CarthaginianArmyBuilder ca_builder;

    const Army* ra = director.createArmy(ra_builder);
    const Army* ca = director.createArmy(ca_builder);

    cout << "Roman army:" << endl;
    ra->info();
    cout << "Carthaginian army:" << endl;
    ca->info();

    delete ra;
    delete ca;

    return 0;
}
