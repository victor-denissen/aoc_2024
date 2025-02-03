with open("input","r") as file:
    content = file.read()

    dataBlock = []

    id = 0
    isFile = True
    for char in content:
        if not char.isdigit():
            continue

        repeat = int(char)
        if isFile:
            for _ in range(repeat):
                dataBlock.append(id)
            id += 1
        else:
            for _ in range(repeat):
                dataBlock.append('.')
        isFile = not isFile
    # print(dataBlock)

def remove_trailing(dataBlock):
    while dataBlock and dataBlock[-1] == ".":
        dataBlock.pop()
    return dataBlock

dataBlock = remove_trailing(dataBlock)
while '.' in dataBlock:
    lastChar = dataBlock[-1]
    index = dataBlock.index('.')
    dataBlock[index] = lastChar
    dataBlock.pop()
    dataBlock = remove_trailing(dataBlock)
    # print(dataBlock)

id = 0
result = 0
for char in dataBlock:
    number = int(char)
    result += number * id
    id += 1
print(result)
