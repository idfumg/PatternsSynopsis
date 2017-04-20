#!/usr/bin/env python

'''
Структурный шаблон проектирования, используемый, чтобы разделять абстракцию и
реализацию так, чтобы они могли меняться независимо.
'''

class DrawingAPI:
    def drawCircle(self, x, y, radius):
        pass

class DrawingAPI1(DrawingAPI):
    def drawCircle(self, x, y, radius):
        print("API1.circle at [{x}, {y}] radius {radius}".format(x=x, y=y, radius=radius))

class DrawingAPI2(DrawingAPI):
    def drawCircle(self, x, y, radius):
        print("API2.circle at [{x}, {y}] radius {radius}".format(x=x, y=y, radius=radius))

class Shape:
    def draw(self):
        pass

    def resizeByPercentage(self, pct):
        pass

class CircleShape(Shape):
    def __init__(self, x, y, radius, drawingAPI):
        self.__x = x
        self.__y = y
        self.__radius = radius
        self.__drawingAPI = drawingAPI

    def draw(self):
        self.__drawingAPI.drawCircle(self.__x, self.__y, self.__radius)

    def resizeByPercentage(self, pct):
        self.__radius *= pct

def main():
    shapes = [
        CircleShape(1, 2, 3, DrawingAPI1()),
        CircleShape(5, 7, 11, DrawingAPI2())
    ]

    for shape in shapes:
        shape.resizeByPercentage(2.5)
        shape.draw()

if __name__ == "__main__":
    main()
