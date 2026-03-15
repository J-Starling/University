import os


def parse_points(filepath):
    points = []

    try:
        with open(filepath, "r") as file:
            text = file.read().replace("\n", " ").strip()

        items = text.split()
        for item in items:
            if not (
                item.startswith("(") and
                item.endswith(")") and
                ";" in item
            ):
                raise ValueError(f"Неверный формат данных: {item}")

            parts = item[1:-1].split(";")
            if len(parts) != 2:
                raise ValueError(f"Ошибка в координатах: {item}")

            points.append((float(parts[0]), float(parts[1])))

        if len(points) < 3:
            raise ValueError("Многоугольник должен иметь минимум 3 точки.")

        return points

    except FileNotFoundError:
        print("Файл не найден.")
        return None

    except ValueError as e:
        print(f"Ошибка: {e}")
        return None


def cross_product(o, a, b):
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])


def is_convex(points):
    n = len(points)
    signs = []

    for i in range(n):
        p1 = points[i]
        p2 = points[(i + 1) % n]
        p3 = points[(i + 2) % n]

        cp = cross_product(p1, p2, p3)
        if cp != 0:
            signs.append(cp > 0)

    return all(signs) or not any(signs)


def is_inside(points, x, y):
    n = len(points)
    inside = False
    p1x, p1y = points[0]
    for i in range(n + 1):
        p2x, p2y = points[i % n]
        if y > min(p1y, p2y):
            if y <= max(p1y, p2y):
                if x <= max(p1x, p2x):
                    if p1y != p2y:
                        xinters = (y - p1y) * (p2x - p1x) / (p2y - p1y) + p1x
                    if p1x == p2x or x <= xinters:
                        inside = not inside
        p1x, p1y = p2x, p2y
    return inside


script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')
polygon = parse_points(file_path)

if polygon:
    try:
        px = float(input("Введите X искомой точки: "))
        py = float(input("Введите Y искомой точки: "))

        convex = is_convex(polygon)
        inside = is_inside(polygon, px, py)

        print(f"\nМногоугольник выпуклый: {"да" if convex else "нет"}")
        print(f"Точка ({px}; {py}) внутри: {"да" if inside else "нет"}")

    except ValueError:
        print("Ошибка: Введите числовые координаты точки.")
