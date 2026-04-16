import os
import re

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')

with open(file_path, "r") as file:
    string = file.read().upper()

parts = re.split(r'(?<=[WSC])(?=[WSC])', string)
print('Максимальное количество символов:', len(max(parts)))
