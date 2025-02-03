with open("example","r") as file:
    content = file.read()

    dataBlock = []

    id = 0
    isFile = True
    for char in content:
        if not char.isdigit():
            continue

        repeat = int(char)
        temp = []
        if isFile:
            for _ in range(repeat):
                temp.append(id)
            id += 1
        else:
            for _ in range(repeat):
                temp.append('.')
        dataBlock.append(temp)
        isFile = not isFile


result = []
rev_copy = dataBlock.reverse()

for i, list in enumerate(dataBlock):
    if all(item != "." for item in list):
        result.append(list)
        continue
    list_size = len(list)
    for rev_list in rev_copy:
        if list_size >= len(rev_list):
            result.append(rev_list)










# def remove_trailing(dataBlock):
#     while dataBlock and dataBlock[-1] == ".":
#         dataBlock.pop()
#     return dataBlock
#
# dataBlock = remove_trailing(dataBlock)
# while '.' in dataBlock:
#     lastChar = dataBlock[-1]
#     index = dataBlock.index('.')
#     dataBlock[index] = lastChar
#     dataBlock.pop()
#     dataBlock = remove_trailing(dataBlock)
#
# id = 0
# result = 0
# for char in dataBlock:
#     number = int(char)
#     result += number * id
#     id += 1
# print(result)
#
