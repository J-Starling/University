import os
import math

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'trajectories.txt')
with open(filename, 'r', encoding='utf-8') as file:
    lines = file.readlines()

trajectories = {}
distances = {}

for line in lines:
    line = line.strip()
    if not line:
        continue
    parts = line.split(' ', 2)
    if len(parts) >= 3 and parts[0] == 'No':
        traj_num = int(parts[1])
        coords_str = parts[2]
        coords_pairs = coords_str.split(';')
        coordinates = []
        for pair in coords_pairs:
            pair = pair.strip()
            if pair:
                xy = pair.split(',')
                if len(xy) == 2:
                    x = int(xy[0].strip())
                    y = int(xy[1].strip())
                    coordinates.append((x, y))
        if coordinates:
            trajectories[traj_num] = coordinates
            total_distance = 0.0
            for i in range(len(coordinates) - 1):
                x1, y1 = coordinates[i]
                x2, y2 = coordinates[i + 1]
                distance = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
                total_distance += distance
            distances[traj_num] = round(total_distance, 2)

print("Суммарные расстояния по траекториям:")
for traj_num in sorted(distances.keys()):
    print(f"Траектория {traj_num}: {distances[traj_num]}")

traj_vertices = {}
for traj_num, coords in trajectories.items():
    traj_vertices[traj_num] = coords

matches = {}

traj_numbers = list(traj_vertices.keys())
for i in range(len(traj_numbers)):
    for j in range(i + 1, len(traj_numbers)):
        t1 = traj_numbers[i]
        t2 = traj_numbers[j]
        vert1 = traj_vertices[t1]
        vert2 = traj_vertices[t2]
        for start1 in range(len(vert1)):
            for start2 in range(len(vert2)):
                length = 0
                while (start1 + length < len(vert1) and
                        start2 + length < len(vert2) and
                       vert1[start1 + length] == vert2[start2 + length]):
                    length += 1
                if length >= 2:
                    matches[(t1, t2, start1, start2)] = length

if matches:
    max_match = max(matches.items(), key=lambda x: x[1])
    (t1, t2, start1, start2), length = max_match
    segment_coords = traj_vertices[t1][start1:start1 + length]
    print("Наибольший общий участок:")
    print(f"Траектории: {t1} и {t2}")
    print("Координаты участка:")
    for i, (x, y) in enumerate(segment_coords):
        print(f"  {i+1}: ({x}, {y})")
else:
    print("Общих участков не найдено")
