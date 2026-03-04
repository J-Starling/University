import os

script_dir = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(script_dir, 'graph.txt')
with open(filename, 'r', encoding='utf-8') as file:
    lines = file.readlines()

graph = {}

for line in lines:
    line = line.strip()
    if line:
        parts = line.split()
        if len(parts) >= 2:
            node1, node2 = parts[0], parts[1]
            if node1 not in graph:
                graph[node1] = []
            graph[node1].append(node2)
            if node2 not in graph:
                graph[node2] = []
            graph[node2].append(node1)

degrees = {}
for node in graph:
    degrees[node] = len(graph[node])

with open(filename, 'a', encoding='utf-8') as file:
    file.write("\nВершины и степени:\n")
    for node in sorted(degrees.keys()):
        file.write(f"{node}: {degrees[node]}\n")
