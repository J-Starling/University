n = int(input('Input an integer: '))

while n > 9:
    sum_digits = 0
    while n > 0:
        sum_digits += n % 10
        n //= 10
    n = sum_digits

print(n)
