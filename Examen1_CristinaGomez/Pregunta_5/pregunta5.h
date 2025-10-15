//Cristina Gómez
//19-10266
//Examen 1
//Archivo .h de la pregunta 5

#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <tuple>

using namespace std;

class SimuladorT {
private:
    map<string, string> programas;
    map<pair<string, string>, bool> interpretes;
    map<tuple<string, string, string>, bool> traductores;
    const string lenguaje_local = "LOCAL";

    bool puedeEjecutarEnLenguaje(const string& lenguaje, set<string> visitados);

public:
    bool definirPrograma(const string& nombre, const string& lenguaje);
    bool definirInterprete(const string& lenguaje_base, const string& lenguaje);
    bool definirTraductor(const string& lenguaje_base, const string& lenguaje_origen, const string& lenguaje_destino);
    bool esEjecutable(const string& nombre_programa);
    void procesarComando(const string& comando);
    void ejecutar();
};

#endif