password = '2137'
input_password = input('Enter a password: ')

while password != input_password:
    print('Wrong password. Try again')
    input_password = input('Enter a password: ')

print('Passwort accepted')
