import math
import random

steps = int(input('Input steps: '))
x, y, z = 0.0, 0.0, 0.0
max_distance = 0.0
total = 0.0

for _ in range(steps):
    r = random.random()
    theta = random.uniform(0, math.pi)
    phi = random.uniform(0, 2 * math.pi)

    delta_x = r * math.cos(phi) * math.cos(theta)
    delta_y = r * math.sin(phi) * math.cos(theta)
    delta_z = r * math.sin(theta)

    x += delta_x
    y += delta_y
    z += delta_z

    current = math.sqrt(x**2 + y**2 + z**2)

    if current > max_distance:
        max_distance = current

    total += current

final_distance = math.sqrt(x**2 + y**2 + z**2)
average_distance = total / steps

result = (final_distance, average_distance, max_distance)

print(result)
