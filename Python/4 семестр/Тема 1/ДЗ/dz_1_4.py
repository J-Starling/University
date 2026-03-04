import random

iter_num = int(input('Input number of iterations: '))
hit = 0

for _ in range(iter_num):
    x = random.random()
    y = random.random()

    if x**2 + y**2 <= 1:
        hit += 1

pi = 4 * hit / iter_num

print(pi)
