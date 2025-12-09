from itertools import permutations

with open("input.txt", "r") as f:
    points = [(int(x),int(y)) for x,y in [line.split(',') for line in f.readlines()]]

size = 0
cords = ()

for perm in permutations(points, 2):
    x1,y1 = perm[0]
    x2,y2 = perm[1]
    cursize = abs(x1-x2+1)*abs(y1-y2+1)
    if cursize > size:
        size = cursize
        cords = ((x1,y1),(x2,y2))
print(size)
print(cords)