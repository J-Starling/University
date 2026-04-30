import os
import re

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'text.txt')

with open(file_path, 'r', encoding='utf-8') as file:
    text = file.read()

pattern = r"begin code\s*\n(.*?)\n\s*end code"
blocks = re.findall(pattern, text, re.DOTALL | re.IGNORECASE)
blocks = [block.strip() for block in blocks]


def execute_code_block(block):
    print(block)

    globals_dict = {}

    try:
        exec(block, globals_dict)
        return True
    except SyntaxError as e:
        print(f"\nСинтаксическая ошибка в строке {e.lineno}: {e.msg}")
        return False
    except Exception as e:
        print(f"\nОшибка выполнения: {type(e).__name__}: {e}")
        return False


if len(blocks) > 1:
    execute_code_block(blocks[1])
else:
    execute_code_block(blocks[0])
