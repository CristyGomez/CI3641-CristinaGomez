//Cristina Gómez
//19-10266
//Examen 2
//Pregunta 2: Pruebas unitarias de las funciones de calculo y mostrar de expresiones en prefijo y postfijo

//investigando sobre este lenguaje, GO, descubri que cuenta con una libreria de testing que facilita 
//la creacion de pruebas unitarias para las funciones definidas

package main

import (
	"testing"
)
//TEST PARA CALCULAR PREFIJO
func TestCalcularPrefijo(t *testing.T) {
	tests := []struct {
		input    []string
		expected int
	}{
		{[]string{"+", "3", "4"}, 7},
		{[]string{"-", "5", "2"}, 3},
		{[]string{"+", "*", "3", "4", "5"}, 17},
		{[]string{"/", "10", "2"}, 5},
		{[]string{"+", "2", "*", "3", "4"}, 14},
	}

	for _, test := range tests {
		resultado := calcularPrefijo(test.input)
		if resultado != test.expected {
			t.Errorf("calcularPrefijo(%v) = %d, se esperaba %d", 
				test.input, resultado, test.expected)
		}
	}
}
//TEST PARA CALCULAR POSTFIJO
func TestCalcularPostfijo(t *testing.T) {
	tests := []struct {
		input    []string
		expected int
	}{
		{[]string{"3", "4", "+"}, 7},
		{[]string{"5", "2", "-"}, 3},
		{[]string{"3", "4", "*", "5", "+"}, 17},
		{[]string{"10", "2", "/"}, 5},
		{[]string{"2", "3", "4", "*", "+"}, 14}, // 2 + (3 * 4)
	}

	for _, test := range tests {
		resultado := calcularPostfijo(test.input)
		if resultado != test.expected {
			t.Errorf("calcularPostfijo(%v) = %d, se esperaba %d", 
				test.input, resultado, test.expected)
		}
	}
}
//TEST PARA MOSTRAR PREFIJO
func TestMostrarPrefijo(t *testing.T) {
	tests := []struct {
		input    []string
		expected string
	}{
		{[]string{"+", "3", "4"}, "3 + 4"},
		{[]string{"+", "*", "3", "4", "5"}, "3 * 4 + 5"},
		{[]string{"*", "+", "1", "2", "3"}, "(1 + 2) * 3"},
		{[]string{"-", "+", "1", "2", "3"}, "1 + 2 - 3"},
	}

	for _, test := range tests {
		resultado := mostrarPrefijo(test.input)
		if resultado != test.expected {
			t.Errorf("mostrarPrefijo(%v) = %s, se esperaba %s", 
				test.input, resultado, test.expected)
		}
	}
}
//TEST PARA MOSTRAR POSTFIJO
func TestMostrarPostfijo(t *testing.T) {
	tests := []struct {
		input    []string
		expected string
	}{
		{[]string{"3", "4", "+"}, "3 + 4"},
		{[]string{"3", "4", "*", "5", "+"}, "3 * 4 + 5"},
		{[]string{"1", "2", "+", "3", "*"}, "(1 + 2) * 3"},
		{[]string{"1", "2", "+", "3", "-"}, "1 + 2 - 3"},
	}

	for _, test := range tests {
		resultado := mostrarPostfijo(test.input)
		if resultado != test.expected {
			t.Errorf("mostrarPostfijo(%v) = %s, se esperaba %s", 
				test.input, resultado, test.expected)
		}
	}
}