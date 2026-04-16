import random
import itertools

seq_num = list()
seq_chars = list()

ran1 = int(random.random() * 10)
elem_num = int(random.random() * 10)
j = 0
for i in itertools.count(ran1, int(random.random() * 10)):
    if j == elem_num:
        break
    j += 1
    seq_num.append(i)

ran2 = int(random.random() * 100 + 40)
elem_chars = int(random.random() * 10)
j = 0
for i in itertools.count(ran2, int(random.random() * 10)):
    if (j == elem_chars or i > 140):
        break
    j += 1
    seq_chars.append(chr(i))

result = list(itertools.zip_longest(seq_chars, seq_num, fillvalue="?"))
print('Список: ', result)
