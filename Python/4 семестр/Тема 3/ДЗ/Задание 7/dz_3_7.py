import os

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')

with open(file_path, 'r', encoding='utf-8') as file:
    text = file.read()

char_counts = {}
for char in text:
    char_counts[char] = char_counts.get(char, 0) + 1

seen = set()
for char in text:
    if char_counts[char] == 2 and char not in seen:
        print(char, end='')
        seen.add(char)
