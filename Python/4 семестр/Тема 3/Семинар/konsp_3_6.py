def rek(N, *args):
    if len(args) == 0:
        return "Недостаточно параметров"
    half = len(args) // 2
    coefficients = args[:half]
    initial_values = args[half:]
    if len(initial_values) < len(coefficients):
        return "Количество начальных значений меньше порядка рекуррентности"
    if N <= len(initial_values):
        return initial_values[N-1]
    sequence = list(initial_values)
    for i in range(len(initial_values), N):
        next_val = 0
        for j in range(len(coefficients)):
            next_val += coefficients[j] * sequence[i - 1 - j]
        sequence.append(next_val)
    return sequence[N-1]


data = list(map(float, input().split()))
N = int(data[0])
print(rek(N, *data[1:]))
