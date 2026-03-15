def print_sum(m):
    s = 0
    while m != 0:
        s += m % 10
        m = m // 10
    print(s)
    if s > 20:
        return True


n = int(input())
print_sum(n)
