a_1 = int(input('Enter a_1: '))
b_1 = int(input('Enter b_1: '))
a_2 = int(input('Enter a_2: '))
b_2 = int(input('Enter b_2: '))

start = max(a_1, a_2)
end = min(b_1, b_2)

if start <= end:
    print('Intersection: [', start, ';', end, ']', sep='')
else:
    print("No intersection")
