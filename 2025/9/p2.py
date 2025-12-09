from collections import deque
from itertools import permutations
from itertools import combinations
from skimage.morphology import flood

import numpy as np


with open("input.txt", "r") as f:
    points = [(int(x),int(y)) for x,y in [line.split(',') for line in f.readlines()]]

size = 0
cords = ()
big_x = 0
big_y = 0
i = 0

# fill ones
for perm in combinations(points, 2):
    x1,y1 = perm[0]
    x2,y2 = perm[1]
    if x1>big_x: big_x = x1
    if y1>big_y: big_y = y1
grid = np.zeros((big_x+4,big_y+4),np.byte)
for i in range(len(points)):
    grid[points[i][0], points[i][1]] = 1
    cx,cy = points[i]
    nx,ny = points[i+1] if i < (len(points)-1) else points[0]

    if cx == nx:
        if cy < ny:
            while cy <= ny:
                grid[cx,cy] = 1
                cy += 1
        else:
            while cy >= ny:
                grid[cx,cy] = 1
                cy -= 1
    else:
        if cx < nx:
            while cx <= nx:
                grid[cx,cy] = 1
                cx += 1
        else:
            while cx >= nx:
                grid[cx,cy] = 1
                cx -= 1

# fill twos

# find starting point

dirs = [
    (-1,-1),(0,-1),(1,-1),
    (-1,0)        ,(1,0),
    (-1,1), (0,1), (1,1)
]
sy = grid.shape[1]//2
sx = 0
while grid[sx+1,sy] != 1:
    sx+=1
q = deque()
q.append((sx,sy))
twos = 0
while q:
    x,y = q.popleft()
    if grid[x,y] == 2:
        continue
    any_neighbours = False
    for dir in dirs:
        gx = x + dir[0]
        gy = y + dir[1]
        if gx < 0 or gy < 0: continue
        if grid[gx,gy] == 1:
            any_neighbours = True
            break
    if not any_neighbours:
        grid[x,y] = 2
        continue
    grid[x,y] = 2
    twos += 1;
    for dir in dirs:
        gx = x + dir[0]
        gy = y + dir[1]
        if gx < 0 or gy < 0: continue
        if grid[gx,gy] == 0:
            q.append((gx,gy))


print(f"Surrounded with {twos}")
maxsize = 0
i = 0


sizes = []
for perm in combinations(points, 2):
    x1,y1 = perm[0]
    x2,y2 = perm[1]
    cursize = (abs(x1-x2)+1)*(abs(y1-y2)+1)
    cords = ((x1, y1), (x2, y2))
    sizes.append((cursize, cords))






sizes.sort(reverse=True)
for perm in sizes:
    i += 1
    print(i)
    if i % 1000 == 0:
        print(f'size: {size}')
    x1,y1 = perm[1][0]
    x2,y2 = perm[1][1]

    cursize = perm[0]
    if cursize < size: break

    sx = x1 if x1 < x2 else x2
    sy = y1 if y1 < y2 else y2
    bx = x1 if x1 > x2 else x2
    by = y1 if y1 > y2 else y2

    valid = True
    #1 x+
    for tx in range(sx,bx+1):
        if grid[tx, sy] == 2 or grid[tx,sy] == 2:
            valid = False
            break
    #3 y+
    if not valid: continue
    for ty in range(sy,by+1):
        if grid[sx, ty] == 2 or grid[bx,ty] == 2:
            valid = False
            break
    if not valid: continue
    size = cursize






print(np.rot90(np.fliplr(grid)))
# print(grid.size)
# print(grid)
print(size)