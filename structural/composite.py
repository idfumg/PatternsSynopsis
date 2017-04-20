#!/usr/bin/env python

'''
Структурный шаблон проектирования, объединяющий объекты в древовидную структуру
для представления иерархии от части к целому. Компоновщик  позволяет
клиентам обращаться к отдельным объектам и к группам объектов одинаково.
'''

class MenuItem():
    def __init__(self, name, action):
        self.name = name
        self.action = action

    def __str__(self):
        return self.name

class Menu(MenuItem):
    def __init__(self, name):
        MenuItem.__init__(self, name, self.show_menu)
        self.items = {}

    def add_item(self, item):
        self.items[len(self.items) + 1] = item

    def show_menu(self):
        choice = -1
        while choice:
            print('\n' * 80)
            print(self)
            choice = read_number()
            if choice in self.items:
                self.items[choice].action()

    def __str__(self):
        res_str = self.name + ':\n0: Exit'
        for i in self.items.keys():
            res_str += str.format('\n{}: {}', i, self.items[i].name)
        return res_str

def read_number(text = ''):
    INP = '>>> '
    text += '\n' + INP if text else INP
    str = ''
    try:
        str = input(text)
        return int(str)
    except ValueError:
        press_enter("Error value: '{}'! Enter the number please".format(str))
        return -1

def press_enter(str = ''):
    str += '\nPress Enter'
    input(str)

if __name__ == '__main__':
    main_menu = Menu('Main')
    main_menu.add_item(MenuItem('A', lambda : press_enter('A')))
    main_menu.add_item(MenuItem('B', lambda : press_enter('B')))

    sub_menu = Menu('Submenu')
    sub_menu.add_item(MenuItem('Sub D', lambda : press_enter('D')))
    sub_menu.add_item(MenuItem('Sub E', lambda : press_enter('E')))

    sub_sub_menu = Menu('Subsubmenu')
    sub_sub_menu.add_item(MenuItem('SubSub F', lambda : press_enter('F')))

    sub_menu.add_item(sub_sub_menu)
    main_menu.add_item(sub_menu)

    main_menu.show_menu()
