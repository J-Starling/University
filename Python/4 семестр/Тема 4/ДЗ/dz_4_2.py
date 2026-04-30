import random
import os


def find_max_path():
    # Ввод размеров матрицы
    n = int(input("Введите количество строк N: "))
    m = int(input("Введите количество столбцов M: "))

    # Генерация матрицы
    matrix = [[random.randint(-9, 9) for _ in range(m)] for _ in range(n)]

    print("\nСгенерированная матрица:")
    for i, row in enumerate(matrix):
        print(f"{i}: {row}")

    print("\nВведите координаты (индексация с 0):")
    r1, c1 = map(int, input("Старт (строка и столбец через пробел): ").split())
    r2, c2 = map(int, input("Финиш (строка и столбец через пробел): ").split())

    best_path = []
    max_sum = float("-inf")

    def find_all_paths(r, c, current_sum, current_path, visited):
        nonlocal max_sum, best_path

        current_path.append((r, c))
        visited.add((r, c))
        current_sum += matrix[r][c]

        if (r, c) == (r2, c2):
            if current_sum > max_sum:
                max_sum = current_sum
                best_path = list(current_path)
        else:
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < m and (nr, nc) not in visited:
                    find_all_paths(nr, nc, current_sum, current_path, visited)

        # Бектрек
        visited.remove((r, c))
        current_path.pop()

    find_all_paths(r1, c1, 0, [], set())

    # Стрелочки для визуализации
    arrows = {}
    for i in range(len(best_path) - 1):
        curr_r, curr_c = best_path[i]
        next_r, next_c = best_path[i+1]

        if next_r > curr_r:
            arrows[(curr_r, curr_c)] = "v"
        elif next_r < curr_r:
            arrows[(curr_r, curr_c)] = "^"
        elif next_c > curr_c:
            arrows[(curr_r, curr_c)] = ">"
        elif next_c < curr_c:
            arrows[(curr_r, curr_c)] = "<"

    # Формирование пути
    original_matrix_str = []
    for row in matrix:
        original_matrix_str.append("\t".join(map(str, row)))

    route_matrix_str = []
    for r in range(n):
        row_display = []
        for c in range(m):
            if (r, c) == (r1, c1) or (r, c) == (r2, c2):
                row_display.append("+")
            elif (r, c) in arrows:
                row_display.append(arrows[(r, c)])
            else:
                row_display.append(".")
        route_matrix_str.append("\t".join(row_display))

    # Запись в файл
    script_dir = os.path.dirname(os.path.abspath(__file__))
    full_path = os.path.join(script_dir, "matrix_out.txt")

    with open(full_path, "w", encoding="utf-8") as f:
        f.write("Исходная матрица\n")
        f.write("\n".join(original_matrix_str))
        f.write(f"\n\nСтарт: ({r1},{c1}), Финиш: ({r2},{c2})\n")
        f.write(f"Максимальная сумма: {max_sum}\n")
        f.write("\nМаршрут\n")
        f.write("\n".join(route_matrix_str))

    print(f"\nРезультаты находятся по пути: {full_path}")


# Запуск программы
find_max_path()
