def sum_range(start, end):
    if start > end:
        start, end = end, start
    total = 0
    for i in range(start, end + 1):
        total += (lambda x: x ** 2)(i)
    return total


start = int(input())
end = int(input())
print(sum_range(start, end))
