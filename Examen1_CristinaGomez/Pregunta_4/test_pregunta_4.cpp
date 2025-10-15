//Cristina Gómez
//19-10266
//Examen 1
//Test de la pregunta 4: Modulo de operaciones con vectores en 3D

#include <iostream>
#include <cassert>
#include <cmath>
#include "pregunta_4.cpp"

void test_constructor() {
    std::cout << "Testing constructor... ";
    Vector3D v1;
    assert(v1.x == 0 && v1.y == 0 && v1.z == 0);
    
    Vector3D v2(1, 2, 3);
    assert(v2.x == 1 && v2.y == 2 && v2.z == 3);
    
    Vector3D v3(4.5, -2.3, 7.8);
    assert(v3.x == 4.5 && v3.y == -2.3 && v3.z == 7.8);
    std::cout << "PASSED" << std::endl;
}

void test_suma() {
    std::cout << "Testing suma... ";
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    Vector3D resultado = v1.suma(v2);
    
    assert(resultado.x == 5);
    assert(resultado.y == 7);
    assert(resultado.z == 9);
    
    std::cout << "PASSED" << std::endl;
}

void test_resta() {
    std::cout << "Testing resta... ";
    Vector3D v1(5, 7, 9);
    Vector3D v2(1, 2, 3);
    Vector3D resultado = v1.resta(v2);
    
    assert(resultado.x == 4);
    assert(resultado.y == 5);
    assert(resultado.z == 6);
    
    // Resta consigo mismo
    Vector3D resultado2 = v1.resta(v1);
    assert(resultado2.es_cero());
    std::cout << "PASSED" << std::endl;
}

void test_producto_cruz() {
    std::cout << "Testing producto cruz... ";
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    Vector3D resultado = v1.producto_cruz(v2);
    
    assert(resultado.x == -3);
    assert(resultado.y == 6);
    assert(resultado.z == -3);
    
    // Producto cruz consigo mismo (debe ser cero)
    Vector3D resultado2 = v1.producto_cruz(v1);
    assert(resultado2.es_cero());
    std::cout << "PASSED" << std::endl;
}

void test_producto_punto() {
    std::cout << "Testing producto punto... ";
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    double resultado = v1.producto_punto(v2);
    
    assert(resultado == 32);
    std::cout << "PASSED" << std::endl;
}

void test_norma() {
    std::cout << "Testing norma... ";
    Vector3D v1(1, 2, 3);
    Vector3D v2(0, 0, 0);
    Vector3D v3(2, 7, 1);
    Vector3D v4(1, 8, 3);
    
    double norma_v1 = v1.norma();
    double norma_v2 = v2.norma();
    double norma_v3 = v3.norma();
    double norma_v4 = v4.norma();
    
    assert(fabs(norma_v1 - 3.741657) < 0.0001);
    assert(norma_v2 == 0);
    assert(fabs(norma_v3 - 7.34846) < 0.0001);
    assert(fabs(norma_v4 - 8.60232) < 0.0001);
    std::cout << "PASSED" << std::endl;
}

void test_operaciones_escalares() {
    std::cout << "Testing operaciones con escalares... ";
    Vector3D v1(2, 4, 6);
    
    // Suma escalar
    Vector3D suma = v1.suma_escalar(3);
    assert(suma.x == 5 && suma.y == 7 && suma.z == 9);
    
    // Resta escalar
    Vector3D resta = v1.resta_escalar(1);
    assert(resta.x == 1 && resta.y == 3 && resta.z == 5);
    
    // Multiplicación escalar
    Vector3D mult = v1.multiplica_escalar(2);
    assert(mult.x == 4 && mult.y == 8 && mult.z == 12);
    
    // Multiplicación por cero
    Vector3D cero = v1.multiplica_escalar(0);
    assert(cero.es_cero());
    std::cout << "PASSED" << std::endl;
}

void test_comparacion() {
    std::cout << "Testing comparación... ";
    Vector3D v1(1, 2, 3);
    Vector3D v2(1, 2, 3);
    Vector3D v3(4, 5, 6);
    
    assert(v1.es_igual(v2));
    assert(!v1.es_igual(v3));
    std::cout << "PASSED" << std::endl;
}

void test_expresiones_del_enunciado() {
    std::cout << "Testing expresiones del enunciado... ";
    Vector3D a(1, 2, 3);
    Vector3D b(4, 5, 6);
    Vector3D c(7, 8, 9);
    
    // b + c
    Vector3D resultado1 = b.suma(c);
    Vector3D esperado1(11, 13, 15);
    assert(resultado1.es_igual(esperado1));
    
    // a * b + c (producto cruz + suma)
    Vector3D producto_cruz = a.producto_cruz(b);
    Vector3D resultado2 = producto_cruz.suma(c);
    // a × b = (-3, 6, -3) + (7, 8, 9) = (4, 14, 6)
    Vector3D esperado2(4, 14, 6);
    assert(resultado2.es_igual(esperado2));
    
    // (b + b) * (c - a)
    Vector3D suma_b = b.suma(b);
    Vector3D resta_ca = c.resta(a);
    Vector3D resultado3 = suma_b.producto_cruz(resta_ca);
    // b + b = (8, 10, 12), c - a = (6, 6, 6)
    // (8, 10, 12) × (6, 6, 6) = (10*6 - 12*6, 12*6 - 8*6, 8*6 - 10*6) = (-12, 24, -12)
    Vector3D esperado3(-12, 24, -12);
    assert(resultado3.es_igual(esperado3));
    
    // a % (c * b)
    Vector3D c_cruz_b = c.producto_cruz(b);
    double resultado4 = a.producto_punto(c_cruz_b);
    // c × b = (8*6 - 9*5, 9*4 - 7*6, 7*5 - 8*4) = (3, -6, 3)
    // a · (3, -6, 3) = 1*3 + 2*(-6) + 3*3 = 3 - 12 + 9 = 0
    assert(resultado4 == 0);
    
    std::cout << "PASSED" << std::endl;
}

void test_operaciones_escalares_enunciado() {
    std::cout << "Testing operaciones con escalares del enunciado... ";
    Vector3D a(1, 2, 3);
    Vector3D b(4, 5, 6);
    Vector3D c(7, 8, 9);
    
    // Caso 1: b + 3
    Vector3D resultado1 = b.suma_escalar(3);
    Vector3D esperado1(7, 8, 9);
    assert(resultado1.es_igual(esperado1));
    
    // Caso 2: a * 3 + &b
    Vector3D mult_escalar = a.multiplica_escalar(3.0);
    double norma_b = b.norma();
    Vector3D resultado2 = mult_escalar.suma_escalar(norma_b);
    // a * 3 = (3, 6, 9)
    // norma_b = 8.77496
    // resultado = (3+8.77496, 6+8.77496, 9+8.77496) = (11.775, 14.775, 17.775)
    Vector3D esperado2(3 + norma_b, 6 + norma_b, 9 + norma_b);
    assert(fabs(resultado2.x - esperado2.x) < 0.0001);
    assert(fabs(resultado2.y - esperado2.y) < 0.0001);
    assert(fabs(resultado2.z - esperado2.z) < 0.0001);
    
    // Caso 3: (b + b) * (c % a)
    // b + b = (8, 10, 12)
    Vector3D suma_bb = b.suma(b);
    // c % a = 7*1 + 8*2 + 9*3 = 50
    double producto_punto = c.producto_punto(a);
    // (8, 10, 12) * 50
    Vector3D resultado3 = suma_bb.multiplica_escalar(producto_punto);
    // (8*50, 10*50, 12*50)
    Vector3D esperado3(400, 500, 600);
    assert(resultado3.es_igual(esperado3));
    
    std::cout << "PASSED" << std::endl;
}

int main() {
    std::cout << "=== INICIANDO PRUEBAS UNITARIAS VECTOR3D ===" << std::endl;
    
    test_constructor();
    test_suma();
    test_resta();
    test_producto_cruz();
    test_producto_punto();
    test_norma();
    test_operaciones_escalares();
    test_comparacion();
    test_expresiones_del_enunciado();
    test_operaciones_escalares_enunciado();
    
    std::cout << "=============================================" << std::endl;
    std::cout << "Fin del test, todas las pruebas pasaron" << std::endl;
    
    return 0;
}