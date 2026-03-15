import os

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'input.txt')
output_path = os.path.join(script_dir, 'output.txt')

with open(file_path, 'r', encoding='utf-8') as file:
    text = file.read()

max_spaces = 0
current_spaces = 0
for char in text:
    if char == ' ':
        current_spaces += 1
        if current_spaces > max_spaces:
            max_spaces = current_spaces
    else:
        current_spaces = 0

result = ''
i = 0
while i < len(text):
    if text[i] == ' ':
        j = i
        while j < len(text) and text[j] == ' ':
            j += 1
        if j - i == max_spaces:
            result += '*'
        else:
            result += ' ' * (j - i)
        i = j
    else:
        result += text[i]
        i += 1

with open(output_path, 'w', encoding='utf-8') as file:
    file.write(result)
