//Cristina Gómez
//19-10266
//Examen 2
//Pregunta 2

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// CALCULAR EL RESULTADO DADA LA EXPRESION EN PREFIJO
//dada una expresion en prefijo, es clave que se lea la expresion de derecha a izquierda, por lo que el 
//bucle for itera desde el final hasta el inicio de la expresion.
//Cuando se encuentra un número, se apila directamente, cuando se encuentra un operador, se desapilan
//luego dependiendo de la operacion que se quiere realizar, se filtra mediante el switch y se realiza la operacion.
//el resultado se apila de nuevo para continuar con el bucle. el final retorna el resultado
func calcularPrefijo(expresion []string) int{
	pila := make([]int, 0)
	
	for i := len(expresion) - 1; i >= 0; i-- {
		elem := expresion[i]
		//si el elemento se puede convertir a numero, se apila, sino, se entiende que es un operador
		if num, err := strconv.Atoi(elem); err == nil {
			pila = append(pila, num)
		} else {
			izquierda := pila[len(pila)-1]
			pila = pila[:len(pila)-1]
			derecha := pila[len(pila)-1]
			pila = pila[:len(pila)-1]
			
			var resultado int
			switch elem {
			case "+":
				resultado = izquierda + derecha
			case "-":
				resultado = izquierda - derecha
			case "*":
				resultado = izquierda * derecha
			case "/":
				if derecha == 0 {
					fmt.Println("Error: Division por cero")
					return 0
				}
				resultado = izquierda / derecha
			default:
				fmt.Println("Operador no valido en la expresion")
				return 0
			}
			pila = append(pila, resultado)
		}
	}
	return pila[0]
}

// CALCULAR EL RESULTADO DADA LA EXPRESION EN POSTFIJO
//en este caso, la mecanica es un poco similar al prefijo, pero en este caso se lee de izquierda a derecha
func calcularPostfijo(expresion []string) int{
	pila := make([]int, 0)
	
	for i := 0; i < len(expresion); i++ {
    	elem := expresion[i]
		if num, err := strconv.Atoi(elem); err == nil {
			pila = append(pila, num)
		} else {
			derecha := pila[len(pila)-1]
			pila = pila[:len(pila)-1]
			izquierda := pila[len(pila)-1]
			pila = pila[:len(pila)-1]
			
			var resultado int
			switch elem {
			case "+":
				resultado = izquierda + derecha
			case "-":
				resultado = izquierda - derecha
			case "*":
				resultado = izquierda * derecha
			case "/":
				if derecha == 0 {
					fmt.Println("Error: Division por cero")
					return 0
				}
				resultado = izquierda / derecha
			default:
				fmt.Println("Operador no valido en la expresion")
				return 0
			}
			pila = append(pila, resultado)
		}
	}
	return pila[0]
}

// Función auxiliar para verificar si contiene operadores
func contieneOperadores(s string, ops []string) bool {
	for _, op := range ops {
		if strings.Contains(s, op) {
			return true
		}
	}
	return false
}

// MOSTRAR EL INFIJO DADA LA EXPRESION EN PREFIJO
//inicialmente, se maneja similar a como se hace en calcularPrefijo,pero en este caso en vez de trabajar con una pila
//se trabaja con una lista de strings. la idea de esto es que cuando se encuentra un numero, se agrega a la lista directamente,
//pero cuando se encuentra un operador, se extraen los dos ultimos elementos de la lista (que serian los operandos)
//y se construye una nueva cadena de texto con el formato "elem1 operador elem2", teniendo en cuenta
//las reglas de precedencia, se utiliza la funcion auxiliar "contieneOperadores" para saber si existe un operador a la izquierda
//o a la derecha del elemento que estamos preguntando, y asi agregar paréntesis cuando sea necesario.
//Finalmente, esta nueva cadena se vuelve a apilar en la lista para continuar con el proceso hasta que se procese toda la expresion.
func mostrarPrefijo(expresion []string) string{
	lista := make([]string, 0)
	
	for i := len(expresion) - 1; i >= 0; i-- {
		elem := expresion[i]
		if _, err := strconv.Atoi(elem); err == nil {
			lista = append(lista, elem)
		} else {
			izquierda := lista[len(lista)-1]
			lista = lista[:len(lista)-1]
			derecha := lista[len(lista)-1]
			lista = lista[:len(lista)-1]
			
			switch elem {
				case "+", "-":
					// Para + y -: poner paréntesis solo si los operandos tienen * o /
					izq_alto := contieneOperadores(izquierda, []string{"*", "/"})
					der_alto := contieneOperadores(derecha, []string{"*", "/"})

					//para evitar poner parentesis dobles, se verifica si ya tiene parentesis
					if der_alto && !strings.HasPrefix(derecha, "(") {
						derecha = "(" + derecha + ")"
					}
					if elem == "-" && izq_alto && !strings.HasPrefix(izquierda, "(") {
						izquierda = "(" + izquierda + ")"
					}
					
					lista = append(lista, izquierda+" "+elem+" "+derecha)
					
				case "*", "/":
					// Para * y /: poner paréntesis si los operandos tienen + o -
					izq_bajo := contieneOperadores(izquierda, []string{"+", "-"})
					der_bajo := contieneOperadores(derecha, []string{"+", "-"})
					
					if izq_bajo && !strings.HasPrefix(izquierda, "(") {
						izquierda = "(" + izquierda + ")"
					}
					if der_bajo && !strings.HasPrefix(derecha, "(") {
						derecha = "(" + derecha + ")"
					}
					if elem == "/" && contieneOperadores(derecha, []string{"+", "-", "*", "/"}) && !strings.HasPrefix(derecha, "(") {
						derecha = "(" + derecha + ")"
					}
					
					lista = append(lista, izquierda+" "+elem+" "+derecha)
				default:
					fmt.Println("Operador no valido en la expresion")
					return ""
			}
		}
	}
	return lista[0]
}

// MOSTRAR EL INFIJO DADA LA EXPRESION EN POSTFIJO
//en este caso, la logica es similar a la de mostrarPrefijo, pero la expresion se lee de izquierda a derecha 
func mostrarPostfijo(expresion []string) string{
	lista := make([]string, 0)
	
	for i := 0; i < len(expresion); i++ {
    	elem := expresion[i]
		if _, err := strconv.Atoi(elem); err == nil {
			lista = append(lista, elem)
		} else {
			derecha := lista[len(lista)-1]
			lista = lista[:len(lista)-1]
			izquierda := lista[len(lista)-1]
			lista = lista[:len(lista)-1]
			
			switch elem {
				case "+", "-":
					// Para + y -: poner paréntesis solo si los operandos tienen * o /
					izq_alto := contieneOperadores(izquierda, []string{"*", "/"})
					der_alto := contieneOperadores(derecha, []string{"*", "/"})
					
					if der_alto && !strings.HasPrefix(derecha, "(") {
						derecha = "(" + derecha + ")"
					}
					if elem == "-" && izq_alto && !strings.HasPrefix(izquierda, "(") {
						izquierda = "(" + izquierda + ")"
					}
					
					lista = append(lista, izquierda+" "+elem+" "+derecha)
					
				case "*", "/":
					// Para * y /: poner paréntesis si los operandos tienen + o -
					izq_bajo := contieneOperadores(izquierda, []string{"+", "-"})
					der_bajo := contieneOperadores(derecha, []string{"+", "-"})
					
					if izq_bajo && !strings.HasPrefix(izquierda, "(") {
						izquierda = "(" + izquierda + ")"
					}
					if der_bajo && !strings.HasPrefix(derecha, "(") {
						derecha = "(" + derecha + ")"
					}
					if elem == "/" && contieneOperadores(derecha, []string{"+", "-", "*", "/"}) && !strings.HasPrefix(derecha, "(") {
						derecha = "(" + derecha + ")"
					}
					lista = append(lista, izquierda+" "+elem+" "+derecha)
				default:
					fmt.Println("Operador no valido en la expresion")
					return ""
			}
		}
	}
	return lista[0]
}

func Simulador() {
	scanner := bufio.NewScanner(os.Stdin)
	
	for {
		fmt.Println("Ingrese la opcion que desea\n EVAL PRE|POST <expresion>\n MOSTRAR PRE|POST <expresion>\n SALIR")
		fmt.Print("-> ")
		if !scanner.Scan() {
			break
		}
		
		entrada := scanner.Text()
		orden := strings.Fields(entrada)
		
		if len(orden) == 0 {
			fmt.Println("Secuencia de comandos no valida")
			continue
		}
		
		switch orden[0] {
		case "EVAL":
			if len(orden) < 3 {
				fmt.Println("Secuencia de comandos no valida")
				continue
			}
			switch orden[1] {
			case "PRE":
				expresion := orden[2:]
				resultado := calcularPrefijo(expresion)
				fmt.Println(resultado)
			case "POST":
				expresion := orden[2:]
				resultado := calcularPostfijo(expresion)
				fmt.Println(resultado)
			default:
				fmt.Println("Secuencia de comandos no valida")
			}
			
		case "MOSTRAR":
			if len(orden) < 3 {
				fmt.Println("Secuencia de comandos no valida")
				continue
			}
			switch orden[1] {
			case "PRE":
				expresion := orden[2:]
				resultado := mostrarPrefijo(expresion)
				fmt.Println(resultado)
			case "POST":
				expresion := orden[2:]
				resultado := mostrarPostfijo(expresion)
				fmt.Println(resultado)
			default:
				fmt.Println("Secuencia de comandos no valida")
			}
			
		case "SALIR":
			return
		default:
			fmt.Println("Secuencia de comandos no valida")
		}
	}
}

func main() {
	Simulador()
}