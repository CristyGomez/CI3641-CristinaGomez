//Cristina Gómez
//19-10266
//Examen 1
//Archivo .cpp principal de la pregunta 3: Simulación del Buddy System

#include <iostream>
#include <string>
#include <sstream>
#include "pregunta3.h"

using namespace std;

int main() {
    //Solicitar al usuario el tamaño total de la memoria
    cout << "\nIngrese el tamaño total de la memoria (potencia de 2):" << endl;
    int tam;
    cin >> tam;
    
    try {
        //Crear una instancia del sistema Buddy con el tamaño especificado
        BuddySystem sistema(tam);

        string entrada;
        cin.ignore(); //Limpiar el buffer de entrada
        
        //Bucle principal del programa
        while (true) {
            //menu de opciones
            cout << "\nAcción: RESERVAR <cant> <nombre> | LIBERAR <nombre> | MOSTRAR | SALIR" << endl;
            cout << "> ";
            //leer comando ingresado por el usuario
            getline(cin, entrada);
             //Convertir la entrada 
            stringstream e(entrada);
            string comando;
            e >> comando;
            
            //Procesar el comando
            try {
                if (comando == "RESERVAR") {
                    //Comando para reservar memoria
                    int cant;
                    string nombre;
                    e >> cant >> nombre;
                    sistema.reservar(cant, nombre); //Llamar reserva
                    
                } else if (comando == "LIBERAR") {
                    //Comando para liberar memoria
                    string nombre;
                    e >> nombre;
                    sistema.liberar(nombre); //Llamar liberación
                    
                } else if (comando == "MOSTRAR") {
                    //Comando para mostrar el estado actual de la memoria
                    sistema.mostrar(); //Llamar mostrar
                    
                } else if (comando == "SALIR") {
                    //Comando para terminar el programa
                    cout << "Finalizando simulación..." << endl;
                    break;
                    
                } else {
                    cout << "Comando no válido." << endl;
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } catch (const exception& e) {
        cout << "Error al inicializar: " << e.what() << endl;
        return 1;
    }
    return 0;
}