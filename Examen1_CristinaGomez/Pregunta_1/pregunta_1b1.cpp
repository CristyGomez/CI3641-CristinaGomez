//Cristina Gómez
//19-10266
//Examen 1
//Pregunta 1b1: Programa que rote una cadena w k veces a la izquierda 

#include <iostream>

using namespace std;
//función recursiva que rota una cadena w k veces a la izquierda
string rotar_recursiva(string w, int k) {
    if (k == 0 || w.empty()) {
        return w;
    }

    char a = w[0];
    string x = w.substr(1);
    return rotar_recursiva(x + a, k - 1);
}


int main() {
    string cadena;
    int k;
    
    //Solicita una cadena de caracteres 
    cout << "Ingrese una cadena: ";
    getline(cin, cadena);
    //Solicita el numero de rotaciones
    cout << "Ingrese el numero de rotaciones: ";
    cin >> k;
    //Imprime la cadena original y la cadena rotada
    cout << "Cadena original: " << cadena << endl;
    cout << "rotar_recursiva(\"" << cadena << "\", " << k << ") = \"" 
         << rotar_recursiva(cadena, k) << "\"" << endl;
    
    return 0;
}