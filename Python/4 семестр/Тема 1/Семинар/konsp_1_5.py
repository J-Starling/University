num = int(input('Enter a three-digit number: '))

a = num // 100
b = num // 10 % 10
c = num % 10

print('Sum of digits:', a + b + c)
print('Prod of digits:', a * b * c)
