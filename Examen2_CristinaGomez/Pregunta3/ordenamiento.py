def ordenamiento(arr):
    if arr == []:
        return
    else:
        menor = min(arr)
        arr.remove(menor)
        yield menor
        for x in ordenamiento(arr):
            yield x

for x in ordenamiento([1,3,3,2,1]):
    print(x, end=' ')
