#!/usr/bin/env python3
import sys


def mixed_product(a, b, c):
    """Вычисляет смешанное произведение векторов a, b, c"""
    bx_c = (
        b[1]*c[2] - b[2]*c[1],
        b[2]*c[0] - b[0]*c[2],
        b[0]*c[1] - b[1]*c[0]
    )
    result = a[0]*bx_c[0] + a[1]*bx_c[1] + a[2]*bx_c[2]
    return result


def print_formula(a, b, c, result):
    """Выводит формулу смешанного произведения"""
    print("\nФормула:")
    print("a · (b × c) =")
    print(f"  | {a[0]} {a[1]} {a[2]} |")
    print(f"  | {b[0]} {b[1]} {b[2]} | = {result}")
    print(f"  | {c[0]} {c[1]} {c[2]} |")

    det = f"({a[0]}*({b[1]}*{c[2]} - {b[2]}*{c[1]}) - " \
        f"{a[1]}*({b[0]}*{c[2]} - {b[2]}*{c[0]}) + " \
        f"{a[2]}*({b[0]}*{c[1]} - {b[1]}*{c[0]}))"
    print("\nРазвернутая формула:")
    print(f"a·(b×c) = {det} = {result}")


def parse_arguments():
    """Ручной парсинг аргументов командной строки"""
    vectors = None
    show_formula = False

    i = 1  # пропускаем имя скрипта
    while i < len(sys.argv):
        arg = sys.argv[i]

        if arg == '-v':
            # Проверяем, что есть достаточно аргументов после -v
            if i + 9 >= len(sys.argv):
                print("Ошибка: после -v должно быть 9 координат")
                sys.exit(1)

            try:
                vectors = [float(sys.argv[i + j]) for j in range(1, 10)]
            except ValueError:
                print("Ошибка: координаты должны быть числами")
                sys.exit(1)

            i += 10  # пропускаем -v и 9 координат

        elif arg == '-h':
            show_formula = True
            i += 1
        else:
            print(f"Неизвестный аргумент: {arg}")
            print(
                "python script.py -v x1 y1 z1 x2 y2 z2 x3 y3 z3 [-h]")
            sys.exit(1)

    if vectors is None:
        print("Ошибка: не указан флаг -v с координатами")
        print(
            "python script.py -v x1 y1 z1 x2 y2 z2 x3 y3 z3 [-h]")
        sys.exit(1)

    return vectors, show_formula


def main():
    vectors, show_formula = parse_arguments()

    # Разделяем координаты на три вектора
    a = (vectors[0], vectors[1], vectors[2])
    b = (vectors[3], vectors[4], vectors[5])
    c = (vectors[6], vectors[7], vectors[8])

    # Вычисляем смешанное произведение
    result = mixed_product(a, b, c)

    print(f"Вектор a: {a}")
    print(f"Вектор b: {b}")
    print(f"Вектор c: {c}")
    print(f"\nСмешанное произведение a·(b×c) = {result}")

    if show_formula:
        print_formula(a, b, c, result)


if __name__ == "__main__":
    main()
