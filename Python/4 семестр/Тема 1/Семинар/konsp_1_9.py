num_1 = int(input('Enter first number: '))
num_2 = int(input('Enter second number: '))
operator = input('Enter operator: ')

if operator == '+':
    print(num_1 + num_2)
elif operator == '-':
    print(num_1 - num_2)
elif operator == '*':
    print(num_1 * num_2)
elif operator == '/':
    if num_2 == 0:
        print('Division by zero')
    else:
        print(num_1 / num_2)
else:
    print('Wrong operator')
