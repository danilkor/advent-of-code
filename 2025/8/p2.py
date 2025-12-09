import math
from itertools import pairwise, combinations

with open("input.txt", 'r') as f:
    points = [tuple(map(int, line.split(","))) for line in f.read().splitlines()]

def dist(p1,p2):
    return int(math.sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1])+(p1[2]-p2[2])*(p1[2]-p2[2])))

pairs = []
for comb in combinations(points,2):
    pairs.append((dist(comb[0],comb[1]),comb))
pairs.sort()




graphs = list()
for point in points: graphs.append({point})

connections = 1
steps = 1000
print(len(pairs))
while True:
    node1,node2 = pairs.pop(0)[1]
    for graph1 in graphs:
        if node1 in graph1 and node2 in graph1: break
        if node1 in graph1:
            for graph2 in graphs:
                if node2 in graph2:
                    graphs.remove(graph2)
                    graphs.remove(graph1)
                    graph1 = graph1.union(graph2)
                    graphs.append(graph1)
                    if len(graphs) == 1:
                        print(node1[0]*node2[0])
                        exit(0)
                    break
            else: continue
            break





# print(graphs)
# lens = [x for x in map(len, graphs)]
# lens.sort(reverse=True)
# print(lens)
# print(lens[0]*lens[1]*lens[2])
