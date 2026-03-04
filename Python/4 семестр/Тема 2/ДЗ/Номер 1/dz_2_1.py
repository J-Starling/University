import os

N = int(input("Введите пороговое значение N: "))
ip_count = {}
ip_login_logout = {}

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'loginfo.txt')
with open(filename, 'r', encoding='utf-8') as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) >= 4:
            ip_address = parts[3]
            event = parts[4] if len(parts) > 4 else ""
            if ip_address in ip_count:
                ip_count[ip_address] += 1
            else:
                ip_count[ip_address] = 1
            if ip_address not in ip_login_logout:
                ip_login_logout[ip_address] = {'LOGIN': False, 'LOGOUT': False}
            if event == 'LOGIN' or event == 'LOGOUT':
                ip_login_logout[ip_address][event] = True

ip_with_both = [ip for ip, events in ip_login_logout.items()
                if events['LOGIN'] and events['LOGOUT']]

print(f"\nIP-адреса, встречающиеся более {N} раз:")
for ip, count in ip_count.items():
    if count > N:
        print(f"{ip}: {count}")
