class Vector2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, vector):
        x = self.x + vector.x
        y = self.y + vector.y

        return Vector2D(x, y)

    def __str__(self):
        return "(" + str(self.x) + ";" + str(self.y) + ")"


def main():
    vec1 = Vector2D(3, 7)
    vec2 = Vector2D(5, 9)

    vec_sum = vec1.__add__(vec2)
    print("Sum of vectors:", vec_sum.__str__())


if __name__ == '__main__':
    main()
