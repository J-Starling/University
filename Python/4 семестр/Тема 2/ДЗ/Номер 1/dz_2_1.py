import os

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'loginfo.txt')

N = int(input("Введите пороговое значение N: "))

ip_login_count = {}
ip_logout_count = {}
ip_total_count = {}

with open(filename, 'r', encoding='utf-8') as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) >= 4:
            ip_address = parts[2]
            action = parts[3]
            if ip_address in ip_total_count:
                ip_total_count[ip_address] += 1
            else:
                ip_total_count[ip_address] = 1
            if action == "LOGIN":
                if ip_address in ip_login_count:
                    ip_login_count[ip_address] += 1
                else:
                    ip_login_count[ip_address] = 1
            elif action == "LOGOUT":
                if ip_address in ip_logout_count:
                    ip_logout_count[ip_address] += 1
                else:
                    ip_logout_count[ip_address] = 1

ip_both = set()
for ip in ip_total_count:
    if ip in ip_login_count and ip in ip_logout_count:
        ip_both.add(ip)

print("\nСловарь IP-адресов и количество их появлений в логе:")
for ip, count in ip_total_count.items():
    print(f"{ip}: {count}")

print("\nIP-адреса, которые хотя бы один раз подключались и отключались:")
for ip in ip_both:
    print(ip)

print(f"\nIP-адреса (с обоими действиями), встречающиеся более {N} раз:")
found = False
for ip in ip_both:
    if ip_total_count[ip] > N:
        print(ip)
        found = True

if not found:
    print(f"Нет IP-адресов (с обоими действиями), встречающихся более {N} раз")
