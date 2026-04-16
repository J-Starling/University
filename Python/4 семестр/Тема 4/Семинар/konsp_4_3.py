import re

result = str()

string = input('Введите строку: ')

numbers = re.findall(r'\d+', string)
parts = re.split(r'\d+', string)

result += parts[0]
for i in range(len(numbers)):
    result += str(int(numbers[i]) * 2)
    result += parts[i+1]

print(result)
