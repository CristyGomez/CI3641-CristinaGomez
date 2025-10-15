//Cristina Gómez
//19-10266
//Examen 1
//Test de la pregunta 3

#include <iostream>
#include <cassert>
#include "pregunta3.h"

using namespace std;

void test_creacion_sistema() {
    cout << "Test 1: Creación del sistema" << endl;
    BuddySystem sistema(64);
    sistema.mostrar();
    cout << "=> Sistema creado correctamente\n" << endl;
}

void test_reserva_basica() {
    cout << "Test 2: Reserva básica" << endl;
    BuddySystem sistema(64);
    sistema.reservar(10, "proceso1");
    sistema.mostrar();
    cout << "=> Reserva básica funcionando\n" << endl;
}

void test_liberacion() {
    cout << "Test 3: Liberación de memoria" << endl;
    BuddySystem sistema(64);
    sistema.reservar(10, "proceso1");
    sistema.liberar("proceso1");
    sistema.mostrar();
    cout << "=> Liberación funcionando\n" << endl;
}

void test_fusion_automatica() {
    cout << "Test 4: Fusión automática de bloques" << endl;
    BuddySystem sistema(64);
    
    // Reservar y liberar bloques que deberian fusionarse
    sistema.reservar(8, "A");
    sistema.reservar(8, "B");
    sistema.liberar("A");
    sistema.liberar("B");
    
    sistema.mostrar();
    cout << "=> Fusión automática funcionando\n" << endl;
}

void test_reserva_multiple() {
    cout << "Test 5: Múltiples reservas" << endl;
    BuddySystem sistema(64);
    
    sistema.reservar(4, "small1");
    sistema.reservar(16, "medium1");
    sistema.reservar(32, "large1");
    
    sistema.mostrar();
    cout << "=> Múltiples reservas funcionando\n" << endl;
}

void test_nombre_duplicado() {
    cout << "Test 6: Error por nombre duplicado" << endl;
    BuddySystem sistema(64);
    sistema.reservar(8, "proceso1");
    
    try {
        sistema.reservar(8, "proceso1");
        assert(false && "Debería haber lanzado excepción");
    } catch (const exception& e) {
        cout << "=> Correctamente detectado: " << e.what() << "\n" << endl;
    }
}

void test_liberar_inexistente() {
    cout << "Test 7: Error al liberar bloque que no existe" << endl;
    BuddySystem sistema(64);
    
    try {
        sistema.liberar("hola");
        assert(false && "Debería haber lanzado excepción");
    } catch (const exception& e) {
        cout << "=> Correctamente detectado: " << e.what() << "\n" << endl;
    }
}

void test_memoria_insuficiente() {
    cout << "Test 8: Error por memoria insuficiente" << endl;
    BuddySystem sistema(64);
    
    try {
        sistema.reservar(100, "adios");
        assert(false && "Debería haber lanzado excepción");
    } catch (const exception& e) {
        cout << "=> Correctamente detectado: " << e.what() << "\n" << endl;
    }
}

void test_cantidad_invalida() {
    cout << "Test 9: Error por cantidad inválida" << endl;
    BuddySystem sistema(64);
    
    try {
        sistema.reservar(0, "cant_cero");
        assert(false && "Debería haber lanzado excepción");
    } catch (const exception& e) {
        cout << "=> Correctamente detectado: " << e.what() << "\n" << endl;
    }
    
    try {
        sistema.reservar(-5, "cant_negativa");
        assert(false && "Debería haber lanzado excepción");
    } catch (const exception& e) {
        cout << "=> Correctamente detectado: " << e.what() << "\n" << endl;
    }
}

void test_tamano_no_potencia_de_2() {
    cout << "Test 10: Error por tamaño no potencia de 2" << endl;
    
    try {
        BuddySystem sistema(60);  // 60 no es potencia de 2
        assert(false && "Debería haber lanzado excepción");
    } catch (const exception& e) {
        cout << "=> Correctamente detectado: " << e.what() << "\n" << endl;
    }
}

void test_completo() {
    cout << "Test 11: Escenario completo" << endl;
    BuddySystem sistema(128);
    
    // Fase 1: Reservas
    sistema.reservar(8, "P1");
    sistema.reservar(16, "P2");
    sistema.reservar(4, "P3");
    sistema.reservar(32, "P4");
    
    // Fase 2: Liberaciones parciales
    sistema.liberar("P1");
    sistema.liberar("P3");
    
    // Fase 3: Más reservas
    sistema.reservar(12, "P5");  // Debería tomar 16
    sistema.reservar(2, "P6");   // Debería tomar 2
    
    sistema.mostrar();
    cout << "=> Escenario completo funcionando\n" << endl;
}

int main() {
    cout << " INICIANDO TEST " << endl;
    
    test_creacion_sistema();
    test_reserva_basica();
    test_liberacion();
    test_fusion_automatica();
    test_reserva_multiple();
    test_nombre_duplicado();
    test_liberar_inexistente();
    test_memoria_insuficiente();
    test_cantidad_invalida();
    test_tamano_no_potencia_de_2();
    test_completo();
    
    cout << "Fin del test, todas la pruebas pasaron correctamente" << endl;
    return 0;
}