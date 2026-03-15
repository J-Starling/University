import os

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'input.txt')

with open(file_path, 'r', encoding='utf-8') as file:
    content = file.read()

castle = {}
pairs = content.replace('{', '').replace('}', '').split(',')
for pair in pairs:
    if ':' in pair:
        key, value = pair.split(':')
        castle[int(key.strip())] = int(value.strip())

indices = sorted(castle.keys())
heights = [castle[i] for i in indices]

n = len(heights)
if n == 0:
    water_blocks = 0
else:
    left_max = [0] * n
    right_max = [0] * n

    left_max[0] = heights[0]
    for i in range(1, n):
        left_max[i] = max(left_max[i-1], heights[i])

    right_max[n-1] = heights[n-1]
    for i in range(n-2, -1, -1):
        right_max[i] = max(right_max[i+1], heights[i])

    water_blocks = 0
    for i in range(n):
        water_level = min(left_max[i], right_max[i])
        if water_level > heights[i]:
            water_blocks += water_level - heights[i]

print((f"Запас воды: {water_blocks}"))
