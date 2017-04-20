/*
  Паттерн Composite позволяет объединять группы схожих
  объектов и управлять ими. Объекты могут быть как
  примитивными, так и составными. (директория файловой
  системы).
  Код клиента работает с примитивными и составными
  объектами единообразно.
 */

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class Unit {
public:
    virtual int getStrength() = 0;
    virtual void addUnit(Unit* p) {
        assert(false);
    }
    virtual ~Unit() {}
};

class Infantryman : public Unit {
public:
    virtual int getStrength() {
        return 1;
    }
};

class Archer : public Unit {
public:
    virtual int getStrength() {
        return 2;
    }
};

class Horseman : public Unit {
public:
    virtual int getStrength() {
        return 3;
    }
};

class CompositeUnit : public Unit {
public:
    int getStrength() {
        int total = 0;
        for (Unit* unit : units)
            total += unit->getStrength();
        return total;
    }

    void addUnit(Unit* unit) {
        units.push_back(unit);
    }

    ~CompositeUnit() {
        for (Unit* unit : units)
            delete unit;
    }

private:
    vector<Unit*> units;
};

CompositeUnit* CreateLegion() {
    CompositeUnit* legion = new CompositeUnit;

    for (int i = 0; i < 3000; ++i)
        legion->addUnit(new Infantryman);
    for (int i = 0; i < 2000; ++i)
        legion->addUnit(new Archer);
    for (int i = 0; i < 1000; ++i)
        legion->addUnit(new Horseman);

    return legion;
}

int main() {
    CompositeUnit* army = new CompositeUnit;

    for (int i = 0; i < 4; ++i)
        army->addUnit(CreateLegion());

    cout << "Roman army damaging strength is: "
         << army->getStrength() << endl;

    delete army;

    return 0;
}
