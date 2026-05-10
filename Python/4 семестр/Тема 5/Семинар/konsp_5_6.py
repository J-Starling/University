class Shape:
    def area(self):
        pass


class Rectangle(Shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def area(self):
        return self.width * self.height


class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return 3.14 * self.radius ** 2


class Triangle(Shape):
    def __init__(self, a, height):
        self.a = a
        self.height = height

    def area(self):
        return 0.5 * self.a * self.height


def main():
    shapes = [
        Rectangle(5, 3),
        Circle(4),
        Triangle(6, 4)
    ]

    for shape in shapes:
        print(f"{shape.__class__.__name__} area: {shape.area()}")


if __name__ == "__main__":
    main()
