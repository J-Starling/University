import os

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'string.txt')
with open(filename, 'r', encoding='utf-8') as file:
    text = file.read()

exclude = r' .,!?;:-"\'()[]{}1234567890\n\t\r'

counts = {}
for char in text:
    if char not in exclude:
        counts[char] = counts.get(char, 0) + 1

if counts:
    max_count = max(counts.values())
    result = [char for char, cnt in counts.items() if cnt == max_count]
    print(f"Наиболее частые символы: {result}")
    print(f"Встречаются {max_count} раз(а)")

print(result)
