import os

script_dir = os.path.dirname(os.path.abspath(__file__))
filename_1 = os.path.join(script_dir, 'rows.txt')
with open(filename_1, 'r', encoding='utf-8') as file:
    rows_lines = file.readlines()

filename_2 = os.path.join(script_dir, 'cols.txt')
with open(filename_2, 'r', encoding='utf-8') as file:
    cols_lines = file.readlines()

filename_3 = os.path.join(script_dir, 'values.txt')
with open(filename_3, 'r', encoding='utf-8') as file:
    values_lines = file.readlines()

n = int(rows_lines[0].strip())
m = int(cols_lines[0].strip())

sparse_matrix = {}

num_elements = min(len(rows_lines) - 1, len(cols_lines) - 1, len(values_lines))

for k in range(num_elements):
    i = int(rows_lines[k + 1].strip())
    j = int(cols_lines[k + 1].strip())
    value = float(values_lines[k].strip())
    sparse_matrix[(i, j)] = value

vector = [i for i in range(1, m + 1)]

print("Разреженная матрица:")
for (i, j), value in sparse_matrix.items():
    print(f"({i}, {j}) = {value}")

print(f"\nВектор: {vector}")

result = [0] * n

for (i, j), value in sparse_matrix.items():
    result[i - 1] += value * vector[j - 1]

print("\nРезультат умножения матрицы на вектор:")
for i, val in enumerate(result, 1):
    print(f"result[{i}] = {val}")
