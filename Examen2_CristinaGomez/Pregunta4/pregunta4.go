//Cristina Gómez
//19-10266
//Examen 2
//Pregunta 4 

package main

// import "fmt"

//version recursiva
//si n es mayor que a*b, realiza la suma de las llamadas recursivas segun la formula dada en el ejercicio
// es decir, desde n, se hacen llamadas recursivas restando b*i, donde i va desde 1 hasta a
//si n es menor que a*b, retorna n
func FRecursiva(n int) int {
    a, b := 6, 5
    //si n es menor que 0, no se hace nada
    if n < 0 {
        return 0
    }
    //caso base
    if 0 <= n && n < a*b {
        return n
    } else {
        //caso recursivo, sumar las llamadas recursivas, segun la formula dada en el ejercicio
        suma := 0
        for i := 1; i <= a; i++ {
            suma += FRecursiva(n - b*i)
        }
        return suma
    }
}

//version recursiva de cola utilizando memorizacion
//se utiliza un mapa para almacenar los resultados ya calculados y evitar recalcularlos
//el mapa debe ser compartido entre todas las llamadas para que la memoización funcione correctamente
//si n es mayor que a*b, realiza la suma de las llamadas recursivas segun la formula dada en el ejercicio
//es decir, desde n, se hacen llamadas recursivas restando b*i, donde i va desde 1 hasta a
//si n es menor que a*b, retorna n
func FCola(n int, memoria map[int]int) int {
    a, b := 6, 5
    //si n es menor que 0, no se almacena en memoria
    if n < 0 {
        return 0
    }
    //verificamos si ya existe el valor en la memoria
    if val, exists := memoria[n]; exists {
        return val
    }
    //caso base
    if 0 <= n && n < a*b {
        memoria[n] = n
        return n
    } else {
        //si no existe, se calcula las "a"  llamadas recursivas y se almacena en memoria
        suma := 0
        for i := 1; i <= a; i++ {
            suma += FCola(n-b*i, memoria)
        }
        memoria[n] = suma
        return suma
    }
}

// Versión iterativa
//para este caso, como es utilizando la subrutina anterior pero una version iterativa, de igual forma se utiliza una memoria para almacenar los resultados
// de 0 a n. Como en el caso aterior se utilizo un metodo de memorizacion, en este caso inicilamente llenamos la memoria hasta n, si n es menor que a*b
//retornmos el valor almacenado en memoria[n]. Si n es mayor que a*b, se procede a calcular los valores desde a*b hasta n, utilizando la formula dada en el ejercicio
func FIterativa(n int) int {
    a, b := 6, 5
    //si n es menor que 0, no se hace nada
    if n < 0 {
        return 0
    }
    //inicializacion de la memoria,para alamacenar todos los valores desde 0 hasta n
    //esto nos permite tener acceso a todos los valores previamente calculados
    memoria := make([]int, n+1)
    
    //llenamos la memoria con los valores base hasta n
    for i := 0; i <= n && i < a*b; i++ {
        memoria[i] = i
    }
    
    // Si n < a*b, retornar inmediatamente
    if n < a*b {
        return memoria[n]
    }
    
    //esto solo se calcula si n >= a*b 
    for i := a * b; i <= n; i++ {
        suma := 0
        for j := 1; j <= a; j++ {
            suma += memoria[i - b*j]
        }
        memoria[i] = suma
    }
    
    return memoria[n]
}

// func main() {
//     fmt.Printf("FRecursiva(25): %d\n", FRecursiva(25)) 
//     fmt.Printf("FRecursiva(75): %d\n", FRecursiva(75))

//     memo := make(map[int]int)
//     fmt.Printf("FCola(25): %d\n", FCola(25, memo)) 
    
//     memo2 := make(map[int]int)
//     fmt.Printf("FCola(75): %d\n", FCola(75, memo2))
    
//     fmt.Printf("FIterativa(25): %d\n", FIterativa(25))
//     fmt.Printf("FIterativa(75): %d\n", FIterativa(75))
// }

