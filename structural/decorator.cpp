/*
  Позволяет добавлять новые обязанности в поведении или состоянии
  отдельных объектов во время выполнения программы.
 */

#include <iostream>

using namespace std;

class Widget {
public:
    virtual void draw() const = 0;
    virtual ~Widget() {
        cout << "Widget::~Widget" << endl;
    }
};

class TextField : public Widget {
public:
    TextField(int width, int height) {
        this->width = width;
        this->height = height;
    }

    void draw() const {
        cout << "TextField: "
             << this->width << ", " << this->height
             << '\n';
    }

    virtual ~TextField() {
        cout << "TextField::~TextField" << endl;
    }

private:
    int width;
    int height;

};

class Decorator : public Widget {
public:
    Decorator(Widget* widget) {
        this->widget = widget;
    }

    void draw() const {
        this->widget->draw();
    }

    virtual ~Decorator() {
        cout << "Decorator::~Decorator" << endl;
        delete widget;
    }

private:
    Widget* widget;
};

class BorderDecorator : public Decorator {
public:
    BorderDecorator(Widget* widget) : Decorator(widget) {}

    void draw() const {
        Decorator::draw();
        cout << "        BorderDecorator" << '\n';
    }

    virtual ~BorderDecorator() {
        cout << "BorderDecorator::~BorderDecorator" << endl;
    }
};

class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(Widget* widget) : Decorator(widget) {}

    void draw() const {
        Decorator::draw();
        cout << "    ScrollDecorator" << '\n';
    }

    virtual ~ScrollDecorator() {
        cout << "ScrollDecorator::~ScrollDecorator" << endl;
    }
};

int main() {
    Widget* widget =
        new BorderDecorator(
            new BorderDecorator(
                new ScrollDecorator(
                    new BorderDecorator(
                        new TextField(80, 24)))));
    widget->draw();

    cout << "\n" << endl;
    delete widget;

    return 0;
}
