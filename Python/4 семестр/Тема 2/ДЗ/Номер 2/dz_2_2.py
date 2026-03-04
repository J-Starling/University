import os

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'numbers.txt')
with open(filename, 'r') as file:
    lines = file.readlines()

complex_numbers = []
for line in lines:
    clean_line = line.strip()
    if clean_line:
        complex_numbers.append(complex(clean_line))

modules = []
for num in complex_numbers:
    module = (num.real ** 2 + num.imag ** 2) ** 0.5
    modules.append((num, module))

print('Исходные числа и их модули: ')
for num, module in modules:
    print(f'{num}: модуль = {module:.3f}')

modules.sort(key=lambda ZV: ZV[1])

print('Отсортированный список по модулю: ')
for num, _ in modules:
    print(num)
