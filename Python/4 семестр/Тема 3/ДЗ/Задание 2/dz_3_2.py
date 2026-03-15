import os

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')
with open(file_path, 'r', encoding='utf-8') as file:
    text = file.read()

words = []
current_word = ''
for char in text.lower():
    if char.isalpha():
        current_word += char
    else:
        if current_word:
            words.append(current_word)
            current_word = ''
if current_word:
    words.append(current_word)

word_counts = {}
for word in words:
    word_counts[word] = word_counts.get(word, 0) + 1

max_count = 0
for count in word_counts.values():
    if count > max_count:
        max_count = count

result_words = []
for word, count in word_counts.items():
    if count == max_count:
        result_words.append(word.upper())

for word in result_words:
    print(word)
