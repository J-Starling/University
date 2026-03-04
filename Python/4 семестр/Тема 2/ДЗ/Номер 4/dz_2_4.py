import os

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'synonyms.txt')
with open(filename, 'r', encoding='utf-8') as file:
    lines = file.readlines()

synonyms_dict = {}
for line in lines:
    line = line.strip()
    if line:
        parts = line.split(' - ')
        if len(parts) == 2:
            word1 = parts[0].lower().strip()
            word2 = parts[1].lower().strip()
            if word1 not in synonyms_dict:
                synonyms_dict[word1] = []
            synonyms_dict[word1].append(word2)
            if word2 not in synonyms_dict:
                synonyms_dict[word2] = []
            synonyms_dict[word2].append(word1)

search_word = input("Введите слово: ").lower().strip()

if search_word in synonyms_dict:
    synonyms = synonyms_dict[search_word]
    with open(filename, 'a', encoding='utf-8') as file:
        for synonym in synonyms:
            file.write(f"{search_word} - {synonym}\n")
        file.write("\n")
    print("Синонимы найдены и записаны в файл.")
else:
    print("Синонимы для данного слова не найдены.")
