a = float(input('Input a: '))
b = float(input('Input b: '))
c = float(input('Input c: '))
d = float(input('Input d: '))
e = float(input('Input e: '))
f = float(input('Input f: '))

deter = a * d - b * c
deter_x = e * d - b * f
deter_y = a * f - c * e

if deter == 0:
    if deter_x == 0 and deter_y == 0:
        print('Infinite solutions')
    else:
        print('No solutions')
else:
    x = deter_x / deter
    y = deter_y / deter
    print('Number of solutions: 1; x =', x, '; y = ', y, sep='')
