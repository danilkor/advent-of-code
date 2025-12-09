with open("input.txt", 'r') as f:
    lines = f.readlines()

operations =[op for op in lines.pop().split()]
print(operations)
result = 0

allspaces = False
numbers = []
curnums = [""]*len(lines)
iter = 0
for i in range(len(lines[0])):
    if allspaces:
        allspaces = False
        numbers.append(curnums)
        curnums = [""]*len(lines)
        iter = 0
    allspaces = True

    for j in range(len(lines)):
        if lines[j][i] != " ":
            allspaces = False
            curnums[iter]+=lines[j][i].replace("\n", "")
    iter += 1
numbers.append(curnums)
print(numbers)
for i in range(len(numbers)):
    expr = ""
    for j in range(len(numbers[i])):
        if len(numbers[i][j]) > 0:
            expr += numbers[i][j]
            expr += operations[i]
    expr = expr[:-1]
    print(expr)
    result += eval(expr)
print(result)

