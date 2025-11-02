//Cristina Gómez
//19-10266
//Examen 2
//Pregunta 1b2

package main

import "fmt"

// Decisiones de implementacion: Para hacer este algoritmo, usé el método recursivo clásico.
// Comparado con la forma iterativa o de recursion de cola, este puede ser mucho más fácil de visualizar
// y entender, además de que es estable. Otro detalle importante es que decidi que tome un array de tipo float64,
// así le podemos tener números enteros como decimales sin problema.


// Esta funcion mergesort toma un arreglo y lo ordena utilizando el algoritmo de ordenacion Merge Sort.
// Recibe como parametros un arreglo de float64 y devuelve un nuevo arreglo de elementos ordenado.
func MergeSort(arr []float64) []float64 {
    if len(arr) <= 1 {
        return arr
    }

    mid := len(arr) / 2
    izq := MergeSort(arr[:mid])
    der := MergeSort(arr[mid:])

    return merge(izq, der)
}

// Esta seria una funcion axuliar para la funcion MergeSort, donde toma dos arreglos ordenados y los combina en uno solo ordenado
// devuelve una nuevo slice que contiene todos los elementos de izq y der en orden ascendente.
// recibe como parametros ambas mitades del arreglo original ya ordenadas y devuelve un nuevo arreglo
// que contiene todos los elementos de izquierda y derecha en orden ascendente.
func merge(izq, der []float64) []float64 {
    resultado := make([]float64, 0, len(izq)+len(der))
    i, j := 0, 0

    for i < len(izq) && j < len(der) {
        if izq[i] < der[j] {
            resultado = append(resultado, izq[i])
            i++
        } else {
            resultado = append(resultado, der[j])
            j++
        }
    }

    resultado = append(resultado, izq[i:]...)
    resultado = append(resultado, der[j:]...)

    return resultado
}

func main() {
    arr := []float64{38.5, 27.2, 43, 3.3, 50, 82.4, 12}
    fmt.Println("Arreglo Original:", arr)
    sortedArr := MergeSort(arr)
    fmt.Println("Array Ordenado:", sortedArr)
}