n = int(input('Введите чётное число: '))
lst = list()

for i in range(n):
    lst.append(i + 1)

for i in range(n):
    if i % 2 == 0:
        lst.append(i + 1)

print(lst)
