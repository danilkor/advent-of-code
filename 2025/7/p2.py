from functools import lru_cache
with open("input.txt", 'r') as f:
    lines = [list(line) for line in f.readlines()]

start = 0
for i in range(len(lines[0])):
    if lines[0][i] == 'S':
        start = i
        break

@lru_cache(None)
def dfs(position):
    y,x = position
    while y < len(lines) and lines[y][x] != '^':
        y+=1
    if y >= len(lines): return 1
    return dfs((y,x+1)) + dfs((y,x-1))

print(dfs((1,start)))
