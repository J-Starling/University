import os

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'string.txt')
with open(filename, 'r', encoding='utf-8') as file:
    string = file.read()
words = string.lower().split()

freq = {}
for word in words:
    if word in freq:
        freq[word] += 1
    else:
        freq[word] = 1

min_freq = min(freq.values())
rarest_words = [word for word, count in freq.items() if count == min_freq]
result = min(rarest_words)

print(result)
