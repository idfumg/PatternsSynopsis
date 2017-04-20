/*
  Паттерн Adapter, представляет собой программную обертку над
  существующими классами, преобразует их интерфейсы к виду, пригодному
  для последующего использования.
 */

#include <iostream>

class ExecuteInterface {
public:
    virtual ~ExecuteInterface() {}
    virtual void execute() = 0;
};

template <typename T>
class ExecuteAdapter : public ExecuteInterface {
public:
    ExecuteAdapter(T* object, void (T::*method) ()) {
        this->object = object;
        this->method = method;
    }

    ~ExecuteAdapter() {
        delete this->object;
    }

    void execute() {
        (this->object->*this->method)();
    }

private:
    T* object;
    void (T::*method)();
};

class Foo1 {
public:
    ~Foo1() {
        std::cout << "Foo1::dtor" << std::endl;
    }

    void doThis() {
        std::cout << "Foo1::doThis" << std::endl;
    }
};

class Foo2 {
public:
    ~Foo2() {
        std::cout << "Foo2::dtor" << std::endl;
    }

    void doThat() {
        std::cout << "Foo2::doThat" << std::endl;
    }
};

class Foo3 {
public:
    ~Foo3() {
        std::cout << "Foo3::dtor" << std::endl;
    }

    void doSomething() {
        std::cout << "Foo3::doSomething" << std::endl;
    }
};

ExecuteInterface** initialize() {
    ExecuteInterface** array = new ExecuteInterface* [3];

    array[0] = new ExecuteAdapter<Foo1>(new Foo1(), &Foo1::doThis);
    array[1] = new ExecuteAdapter<Foo2>(new Foo2(), &Foo2::doThat);
    array[2] = new ExecuteAdapter<Foo3>(new Foo3(), &Foo3::doSomething);

    return array;
}

int main() {
    ExecuteInterface** objects = initialize();
    for (int i = 0; i < 3; ++i)
        objects[i]->execute();

    for (int i = 0; i < 3; ++i)
        delete objects[i];

    delete objects;

    return 0;
}
