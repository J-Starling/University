import os
import re

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')

with open(file_path, 'r', encoding='utf-8') as file:
    words = list(re.split(r'[/\d]+', file.read()))

result = list()

for word in words:
    if re.fullmatch(r"[^жЖрРкК]*[кК][^жЖрРкК]*[кК][^жЖрРкК]*[кК][^жЖрРкК]*",
                    word):
        result.append(word)

print(result)
