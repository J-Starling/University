import itertools

string = 'RGUNG'

print('Упорядоченные пары: ', list(itertools.permutations(string, 2)))
print('Комбинации: ', list(itertools.combinations(string, 2)))
