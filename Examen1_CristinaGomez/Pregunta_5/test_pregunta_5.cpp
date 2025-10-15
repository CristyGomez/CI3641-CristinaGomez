//Cristina Gómez
//19-10266
//Examen 1
//Test de la pregunta 5

#define TESTS
#include <iostream>
#include <cassert>
#include <string>
#include "pregunta5.h"

using namespace std;

void testDefinirPrograma() {
    cout << "=== Test: Definir Programa ===" << endl;
    SimuladorT sim;
    
    bool resultado1 = sim.definirPrograma("hola", "Python");
    assert(resultado1 == true);
    cout << "=> Programa definido correctamente\n" << endl;
    
    bool resultado2 = sim.definirPrograma("hola", "Java");
    assert(resultado2 == false);
    cout << "=> Duplicado evitado correctamente\n" << endl;
    
    bool resultado3 = sim.definirPrograma("adios", "Java");
    assert(resultado3 == true);
    cout << "=> Segundo programa definido correctamente\n" << endl;
}

void testDefinirInterprete() {
    cout << "\n=== Test: Definir Intérprete ===" << endl;
    SimuladorT sim;
    
    bool resultado1 = sim.definirInterprete("LOCAL", "Python");
    assert(resultado1 == true);
    cout << "=> Intérprete definido correctamente\n" << endl;
    
    bool resultado2 = sim.definirInterprete("LOCAL", "Python");
    assert(resultado2 == false);
    cout << "=> Duplicado evitado correctamente\n" << endl;
    
    bool resultado3 = sim.definirInterprete("Python", "Ruby");
    assert(resultado3 == true);
    cout << "=> Cadena de intérpretes creada\n" << endl;
}

void testDefinirTraductor() {
    cout << "\n=== Test: Definir Traductor ===" << endl;
    SimuladorT sim;
    
    bool resultado1 = sim.definirTraductor("Python", "Java", "Python");
    assert(resultado1 == true);
    cout << "=> Traductor definido correctamente\n" << endl;
    
    bool resultado2 = sim.definirTraductor("Python", "Java", "Python");
    assert(resultado2 == false);
    cout << "=> Traductor duplicado detectado\n" << endl;
    
}

void testEjecutableDirecto() {
    cout << "\n=== Test: Ejecutable Directo ===" << endl;
    SimuladorT sim;
    
    // Programa + Interprete
    sim.definirPrograma("app", "Python");
    sim.definirInterprete("LOCAL", "Python");
    
    bool resultado = sim.esEjecutable("app");
    assert(resultado == true);
    cout << "=> Programa con intérprete directo es ejecutable\n" << endl;
}

void testEjecutableCadenaInterpretes() {
    cout << "\n=== Test: Cadena de Intérpretes ===" << endl;
    SimuladorT sim;
    
    // Ruby -> Python -> LOCAL
    sim.definirPrograma("Esmeralda", "Ruby");
    sim.definirInterprete("Python", "Ruby");
    sim.definirInterprete("LOCAL", "Python");
    
    bool resultado = sim.esEjecutable("Esmeralda");
    assert(resultado == true);
    cout << "=> Programa con cadena de intérpretes es ejecutable\n" << endl;
}

void testEjecutableConTraductor() {
    cout << "\n=== Test: Ejecutable con Traductor ===" << endl;
    SimuladorT sim;
    
    // Java -(traductor)-> Python -(interprete)-> LOCAL
    sim.definirPrograma("usb", "Java");
    sim.definirTraductor("Python", "Java", "Python");
    sim.definirInterprete("LOCAL", "Python");
    
    bool resultado = sim.esEjecutable("usb");
    assert(resultado == true);
    cout << "=> Programa con traductor es ejecutable\n" << endl;
}

void testNoEjecutable() {
    cout << "\n=== Test: No Ejecutable ===" << endl;
    SimuladorT sim;
    
    sim.definirPrograma("secreto", "Haskell");
    
    bool resultado = sim.esEjecutable("secreto");
    assert(resultado == false);
    cout << "=> Programa sin soporte NO es ejecutable\n" << endl;
}

void testProgramaInexistente() {
    cout << "\n=== Test: No existe el programa ===" << endl;
    SimuladorT sim;
    
    bool resultado = sim.esEjecutable("fantasma");
    assert(resultado == false);
    cout << "=> Detecta que no existe el programa correctamente\n" << endl;
}

void testCicloInfinito() {
    cout << "\n=== Test: Prevención de Ciclos ===" << endl;
    SimuladorT sim;
    
    // Ciclo A -> B -> A
    sim.definirPrograma("ciclo", "A");
    sim.definirInterprete("B", "A");
    sim.definirInterprete("A", "B");  // Esto crea un ciclo
    
    //No debe colgarse en ciclo infinito
    bool resultado = sim.esEjecutable("ciclo");
    assert(resultado == false);
    cout << "=> Ciclo infinito prevenido correctamente\n" << endl;
}

void testCasoComplejo() {
    cout << "\n=== Test: Caso Complejo ===" << endl;
    SimuladorT sim;
    
    // multiples rutas
    sim.definirPrograma("complejo", "Rust");
    sim.definirInterprete("LOCAL", "C");
    sim.definirInterprete("C", "C++");
    sim.definirTraductor("C++", "Rust", "C++");
    sim.definirTraductor("Python", "Rust", "Python");
    sim.definirInterprete("LOCAL", "Python");
    
    //Debe encontrar alguna ruta valida
    bool resultado = sim.esEjecutable("complejo");
    assert(resultado == true);
    cout << "=> Caso complejo resuelto correctamente\n" << endl;
}

void testComandosProcesamiento() {
    cout << "\n=== Test: Procesamiento de Comandos ===" << endl;
    SimuladorT sim;
    //comandos validos
    cout << "Probando comandos DEFINIR..." << endl;
    
    //Estos comandos no deberian generar errores
    sim.procesarComando("DEFINIR PROGRAMA test1 Python");
    sim.procesarComando("DEFINIR INTERPRETE LOCAL Python");
    sim.procesarComando("DEFINIR TRADUCTOR C Java C");
    sim.procesarComando("EJECUTABLE test1");
    
    cout << "=> Comandos procesados sin errores\n" << endl;
    
    //comandos invalidos
    cout << "Probando comandos invalidos..." << endl;
    sim.procesarComando("DEFINIR PROGRAMA");  // Faltan argumentos
    sim.procesarComando("DEFINIR ALIEN x y"); // Tipo desconocido
    sim.procesarComando("EJECUTABLE");        // Faltan argumentos
    
    cout << "=> Comandos invalidos manejados correctamente\n" << endl;
}

void ejecutarTodasLasPruebas() {
    cout << "INICIANDO PRUEBAS UNITARIAS\n" << endl;
    
    try {
        testDefinirPrograma();
        testDefinirInterprete();
        testDefinirTraductor();
        testEjecutableDirecto();
        testEjecutableCadenaInterpretes();
        testEjecutableConTraductor();
        testNoEjecutable();
        testProgramaInexistente();
        testCicloInfinito();
        testCasoComplejo();
        testComandosProcesamiento();
        
        cout << "\nFin del test, todas las pruebas fueron exitosas" << endl;
        
    } catch (const exception& e) {
        cout << "\nERROR en prueba: " << e.what() << endl;
    }
}

int main() {
    ejecutarTodasLasPruebas();
    return 0;
}