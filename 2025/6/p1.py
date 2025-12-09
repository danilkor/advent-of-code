with open("input.txt", 'r') as f:
    lines = f.readlines()

operations = [op for op in lines.pop().split()]
numbers = [[num for num in line.split()] for line in lines]
print(operations)
print(numbers)
result = 0
for i in range(len(numbers[0])):
    expr = ""
    for j in range(len(numbers)):
        expr += numbers[j][i]
        expr += operations[i]
    expr = expr[:-1]
    result += eval(expr)
print(result)