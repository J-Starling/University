text = input('Введите текст: ')
string = text.split('#')
lst = list()

for i in range(len(string)):
    lst.append(string[i])

max_index = lst.index(max(lst))
min_index = lst.index(min(lst))
min_elem = min(lst)

lst[min_index] = lst[max_index]
lst[max_index] = min_elem

print(lst)
