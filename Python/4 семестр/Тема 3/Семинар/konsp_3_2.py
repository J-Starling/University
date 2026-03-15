def get_jacts(m):
    lst = list()
    for i in range(1, m // 2 + 1):
        if (m % i == 0):
            lst.append(i)
    return lst


n = int(input())
print(get_jacts(n))
