n = int(input('Введите количество чисел: '))
lst = list()
for i in range(n):
    lst.append(int(input('Введите число: ')) ** 3)

print('Список: ', lst)
print('Сумма элементов: ', sum(lst))
