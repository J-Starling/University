import os
import re

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')

with open(file_path, "r") as file:
    string = file.read()

result = re.sub(r'p{1,}m{0,}a{2,}', 'ххх', string)
print(result)
