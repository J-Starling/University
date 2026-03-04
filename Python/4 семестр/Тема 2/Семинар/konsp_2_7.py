string = input('Введите строку: ')
char = input('Введите символ: ')
lst = list()

for i in range(len(string)):
    if string[i] == char:
        lst.append(i)

print('Позиции символа в строке: ', lst)
print('Сумма элементов: ', sum(lst))
