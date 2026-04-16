#!/usr/bin/env python3
import argparse


def mixed_product(a, b, c):
    """Вычисляет смешанное произведение векторов a, b, c"""
    # a · (b × c)
    # b × c = (b2*c3 - b3*c2, b3*c1 - b1*c3, b1*c2 - b2*c1)
    bx_c = (
        b[1]*c[2] - b[2]*c[1],
        b[2]*c[0] - b[0]*c[2],
        b[0]*c[1] - b[1]*c[0]
    )
    # скалярное произведение a и (b × c)
    result = a[0]*bx_c[0] + a[1]*bx_c[1] + a[2]*bx_c[2]
    return result


def print_formula(a, b, c, result):
    """Выводит формулу смешанного произведения"""
    print("\nФормула:")
    print("a · (b × c) =")
    print(f"  | {a[0]} {a[1]} {a[2]} |")
    print(f"  | {b[0]} {b[1]} {b[2]} | = {result}")
    print(f"  | {c[0]} {c[1]} {c[2]} |")

    # Детерминантная форма
    det = f"({a[0]}*({b[1]}*{c[2]} - {b[2]}*{c[1]}) - " \
        f"{a[1]}*({b[0]}*{c[2]} - {b[2]}*{c[0]}) + " \
        f"{a[2]}*({b[0]}*{c[1]} - {b[1]}*{c[0]}))"
    print("\nРазвернутая формула:")
    print(f"a·(b×c) = {det} = {result}")


def main():
    parser = argparse.ArgumentParser(
        description='Вычисление смешанного произведения трех векторов'
    )
    parser.add_argument('-v', '--vectors',
                        nargs=9,
                        required=True,
                        type=float,
                        metavar=('x1 y1 z1', 'x2 y2 z2', 'x3 y3 z3'),
                        help='9 координат трех векторов (через пробел)')
    parser.add_argument('-h', '--help-formula',
                        action='store_true',
                        help='Вывести формулу после вычисления')

    args = parser.parse_args()

    # Разделяем координаты на три вектора
    coords = args.vectors
    a = (coords[0], coords[1], coords[2])
    b = (coords[3], coords[4], coords[5])
    c = (coords[6], coords[7], coords[8])

    # Вычисляем смешанное произведение
    result = mixed_product(a, b, c)

    print(f"Вектор a: {a}")
    print(f"Вектор b: {b}")
    print(f"Вектор c: {c}")
    print(f"\nСмешанное произведение a·(b×c) = {result}")

    if args.help_formula:
        print_formula(a, b, c, result)


if __name__ == "__main__":
    main()
