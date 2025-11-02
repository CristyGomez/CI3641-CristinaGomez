#Cristina Gómez
#19-10266
#Examen 2
#Pregunta 3

#Implementacion de un algoritmo de ordenamiento recursivo que encuentra repetidamente
#el elemento mínimo, lo va eliminando del array y luego hace yield para imprimirlo 
def ordenamiento(arr):
    #caso base
    if arr == []:
        return
    #Caso recursivo: encuentra el elemento mínimo, lo elimina, y realiza un yield
    else:
        #encuentra el elemento minimo en la lista actual
        menor = min(arr)
        #remueve cuando consigue el primer valor minimo que coincida
        arr.remove(menor)
        # yield del actual elem minimo
        yield menor
        #recursion sobre el resto de la lista
        #itera sobre los elementos
        for x in ordenamiento(arr):
            yield x

for x in ordenamiento([1,3,3,2,1]):
    print(x, end=' ')

