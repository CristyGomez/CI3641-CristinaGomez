//Cristina Gómez
//19-10266
//Examen 2
//Pregunta 1b1

package main

import "fmt"

//La función toma un número entero positivo y cuenta cuántos pasos se necesitan para reducirlo a 1
//si el número es par, se divide entre 2; si es impar, se multiplica por 3 y se suma 1.
//y asi sucesivamente hasta llegar a 1.
//retorna el conteo de pasos necesarios para llegar a 1.
func count(n int) int {
	contador := 0
	for n != 1 {
		if n%2 == 0 {
			n = n / 2
			contador++
		} else {
			n = 3*n + 1
			contador++
		}
	}
	return contador
}

func main() {
	var n int
	
	fmt.Print("Ingrese un número positivo: ")
	_, err := fmt.Scan(&n)
	
	if err != nil {
		fmt.Println("Error: Debe ingresar un número válido")
		return
	}
	
	if n <= 0 {
		fmt.Println("Error: El número debe ser positivo")
		return
	}

	result := count(n)
	fmt.Printf("Número de pasos para reducir %d a 1: %d\n", n, result)
}