#!/usr/bin/env python

'''
Структурный шаблон проектирования, предназначенный для организации использования
функций объекта, недоступного для модификации, через специально созданный интерфейс.
'''

class GameConsole:
    def create_game_picture(self):
        return "picture from console"

class Antena:
    def create_wave_picture(self):
        return "picture from wave"

class SourceGameConsole(GameConsole):
    def get_picture(self):
        return self.create_game_picture()

class SourceAntenna(Antena):
    def get_picture(self):
        return self.create_wave_picture()

class TV:
    def __init__(self, source):
        self.source = source

    def show_picture(self):
        return self.source.get_picture()

def main():
    g = SourceGameConsole()
    a = SourceAntenna()
    game_tv = TV(g)
    cabel_tv = TV(a)
    print(game_tv.show_picture())
    print(cabel_tv.show_picture())

if __name__ == "__main__":
    main()
