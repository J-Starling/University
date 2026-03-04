import math

x = float(input('Input x: '))
n = int(input('Input number of terms: '))

function = x * math.sin(x)

sum_for = 0
for i in range(1, n + 1):
    if i == 1:
        sum_for += 1 * math.sin(i * x)
    else:
        sum_for += (8 * i * (-1)**(i + 1)) / \
            (math.pi * (i**2 - 1)**2) * math.sin(i * x)

sum_while = 0
i = 1
while i <= n:
    if i == 1:
        sum_while += 1 * math.sin(i * x)
    else:
        sum_while += (8 * i * (-1)**(i + 1)) / \
            (math.pi * (i**2 - 1)**2) * math.sin(i * x)
    i += 1

print('Function value:', function)
print('Sum_for:', sum_for)
print('Sum_while:', sum_while)
