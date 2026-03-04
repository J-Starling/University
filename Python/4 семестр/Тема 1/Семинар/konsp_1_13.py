a = int(input('Enter a: '))
b = int(input('Enter b: '))
max_sum = 0

for i in range(a, b + 1):
    adj_sum = 0
    for j in range(1, i // 2 + 1):
        if i % j == 0:
            adj_sum += j
        if adj_sum > max_sum:
            max_sum = adj_sum
            max_num = i

print(max_num)
