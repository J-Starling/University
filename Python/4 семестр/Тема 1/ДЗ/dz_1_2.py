import math
import random

x_0 = float(input('Input X coordinate of the center of the circle: '))
y_0 = float(input('Input Y coordinate of the center of the circle: '))
radius = float(input('Input radius of the circle: '))
x_a = float(input('Input X coordinate of the point A: '))
y_a = float(input('Input Y coordinate of the point A: '))
N = int(input('Input number of points: '))

min_distance = float('inf')
min_points = []

for i in range(N):
    angle = random.uniform(0, 2 * math.pi)
    x_i = x_0 + radius * math.cos(angle)
    y_i = y_0 + radius * math.sin(angle)

    distance = math.sqrt((x_i - x_a) ** 2 + (y_i - y_a) ** 2)

    if distance < min_distance:
        min_distance = distance
        min_points = [(x_i, y_i)]
    elif distance == min_distance:
        min_points.append((x_i, y_i))

print('Minimal distance:', min_distance)
print('All points with minimal distance:')
for i, (x, y) in enumerate(min_points, 1): 
    print(f'Point {i}: ({x:.6f}, {y:.6f})')
