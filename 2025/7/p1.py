with open("input.txt", 'r') as f:
    lines = [list(line) for line in f.readlines()]

splits = 0
for i in range(1, len(lines)):
    for c in range(len(lines[i])):
        if lines[i-1][c] == 'S':
            lines[i][c] = '|'
        if lines[i-1][c] == '|':
            if lines[i][c] == '^':
                splits+=1
                lines[i][c-1] = '|'
                lines[i][c+1] = '|'
            else:
                lines[i][c] = '|'
print(splits)