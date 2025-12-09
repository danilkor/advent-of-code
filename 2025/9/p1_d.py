from itertools import permutations

with open("test.txt", "r") as f:
    points = [(int(x),int(y)) for x,y in [line.split(',') for line in f.readlines()]]

sizes = []
for perm in permutations(points, 2):
    x1,y1 = perm[0]
    x2,y2 = perm[1]
    cursize = (abs(x1-x2)+1)*(abs(y1-y2)+1)
    cords = ((x1, y1), (x2, y2))
    sizes.append((cursize,cords))


sizes.sort(reverse=True)
for size in sizes:
    if size[0] <= 1568849600:
        print(size)
