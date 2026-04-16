import itertools

seq = list()

j = 0
for i in itertools.count(5, 3):
    if j == 7:
        break
    j += 1
    seq.append(i)

print('Последовательность:', seq)
