import os

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'input.txt')
output_path = os.path.join(script_dir, 'output.txt')

with open(file_path, 'r', encoding='utf-8') as file:
    text = file.read()

text = text.replace('-\n', '')
text = text.replace('-\r\n', '')

words = []
current_word = ''
for char in text:
    if ('a' <= char <= 'z') or ('A' <= char <= 'Z'):
        current_word += char
    else:
        if current_word:
            words.append(current_word)
            current_word = ''
        if char != '\n' and char != '\r':
            words.append(char)
if current_word:
    words.append(current_word)

used = [False] * len(words)

for i in range(len(words) - 1, -1, -1):
    if used[i] or not words[i].isalpha():
        continue
    for j in range(i - 1, -1, -1):
        if used[j] or not words[j].isalpha():
            continue
        if words[i].lower() == words[j].lower()[::-1]:
            used[i] = True
            used[j] = True
            break

result = ''
for i, word in enumerate(words):
    if not used[i]:
        result += word

with open(output_path, 'w', encoding='utf-8') as file:
    file.write(result)
