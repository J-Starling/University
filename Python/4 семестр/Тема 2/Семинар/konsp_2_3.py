text = input('Введите текст: ')
sep = input('Введите разделитель: ')
result = ''

for i in range(len(text)):
    result += text[i]
    if i < len(text) - 1:
        result += sep

print(result)
