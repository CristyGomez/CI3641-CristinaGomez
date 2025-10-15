//Cristina Gómez
//19-10266
//Examen 1
//Archivo .cpp de la pregunta 5

#include "pregunta5.h"

bool SimuladorT::puedeEjecutarEnLenguaje(const string& lenguaje, set<string> visitados) {
    // Evitar ciclos infinitos
    if (visitados.find(lenguaje) != visitados.end()) {
        cout << "ERROR: Ciclo detectado al intentar ejecutar en lenguaje '" << lenguaje << "'" << endl;
        return false;
    }
    
    // Caso base: el lenguaje es LOCAL
    if (lenguaje == lenguaje_local) {
        return true;
    }
    
    visitados.insert(lenguaje);
    
    // Buscar interpretes que puedan ejecutar este lenguaje
    for (const auto& interprete : interpretes) {
        if (interprete.first.second == lenguaje) {
            // Verificar si podemos ejecutar el lenguaje base del interprete
            if (puedeEjecutarEnLenguaje(interprete.first.first, visitados)) {
                return true;
            }
        }
    }
    
    // Buscar traductores que puedan traducir este lenguaje
    for (const auto& traductor : traductores) {
        const auto& clave = traductor.first;
        if (get<1>(clave) == lenguaje) {
            // Verificar si podemos ejecutar el lenguaje destino y el base del traductor
            if (puedeEjecutarEnLenguaje(get<2>(clave), visitados) &&
                puedeEjecutarEnLenguaje(get<0>(clave), visitados)) {
                return true;
            }
        }
    }
    
    return false;
}

// Define un nuevo programa con su lenguaje asociado
bool SimuladorT::definirPrograma(const string& nombre, const string& lenguaje) {
    //verifica si este nombre ya existe
    if (programas.find(nombre) != programas.end()) {
        cout << "ERROR: Ya existe un programa con el nombre '" << nombre << "'" << endl;
        return false;
    }
    //si no existe, lo agrega
    programas[nombre] = lenguaje;
    cout << "Programa '" << nombre << "' definido en lenguaje '" << lenguaje << "'" << endl;
    return true;
}
// Define un nuevo interprete
bool SimuladorT::definirInterprete(const string& lenguaje_base, const string& lenguaje) {
    auto clave = make_pair(lenguaje_base, lenguaje);
    //verifica si este interprete ya existe
    if (interpretes.find(clave) != interpretes.end()) {
        cout << "ERROR: Ya existe un interprete para '" << lenguaje << "' en '" << lenguaje_base << "'" << endl;
        return false;
    }
    
    interpretes[clave] = true;
    cout << "Interprete definido: '" << lenguaje_base << "' -> '" << lenguaje << "'" << endl;
    return true;
}
// Define un nuevo traductor
bool SimuladorT::definirTraductor(const string& lenguaje_base, const string& lenguaje_origen, const string& lenguaje_destino) {
    auto clave = make_tuple(lenguaje_base, lenguaje_origen, lenguaje_destino);
    //verifica si este traductor ya existe
    if (traductores.find(clave) != traductores.end()) {
        cout << "ERROR: Ya existe un traductor de '" << lenguaje_origen << "' a '" << lenguaje_destino << "' en '" << lenguaje_base << "'" << endl;
        return false;
    }
    
    traductores[clave] = true;
    cout << "Traductor definido: '" << lenguaje_base << "' traduce '" << lenguaje_origen << "' -> '" << lenguaje_destino << "'" << endl;
    return true;
}
// Verifica si un programa es ejecutable
bool SimuladorT::esEjecutable(const string& nombre_programa) {
    //verifica si el programa existe
    if (programas.find(nombre_programa) == programas.end()) {
        cout << "ERROR: No existe un programa con el nombre '" << nombre_programa << "'" << endl;
        return false;
    }
    //obtiene el lenguaje del programa
    string lenguaje_objetivo = programas[nombre_programa];
    set<string> visitados;
    return puedeEjecutarEnLenguaje(lenguaje_objetivo, visitados);
}
// Procesa un comando ingresado por el usuario
void SimuladorT::procesarComando(const string& comando) {
    vector<string> partes;
    stringstream entrada(comando);
    string palabra;
    
    while (entrada >> palabra) {
        partes.push_back(palabra);
    }
    
    if (partes.empty()) {
        return;
    }
    
    string accion = partes[0];
    // Procesar accionees
    if (accion == "DEFINIR") {
        if (partes.size() < 2) {
            cout << "ERROR: Formato incorrecto. Uso: DEFINIR <tipo> [<argumentos>]" << endl;
            return;
        }
        
        string tipo = partes[1];
        
        if (tipo == "PROGRAMA") {
            if (partes.size() != 4) {
                cout << "ERROR: Formato incorrecto. Uso: DEFINIR PROGRAMA <nombre> <lenguaje>" << endl;
            } else {
                definirPrograma(partes[2], partes[3]);
            }
        } else if (tipo == "INTERPRETE") {
            if (partes.size() != 4) {
                cout << "ERROR: Formato incorrecto. Uso: DEFINIR INTERPRETE <lenguaje_base> <lenguaje>" << endl;
            } else {
                definirInterprete(partes[2], partes[3]);
            }
        } else if (tipo == "TRADUCTOR") {
            if (partes.size() != 5) {
                cout << "ERROR: Formato incorrecto. Uso: DEFINIR TRADUCTOR <lenguaje_base> <lenguaje_origen> <lenguaje_destino>" << endl;
            } else {
                definirTraductor(partes[2], partes[3], partes[4]);
            }
        } else {
            cout << "ERROR: Tipo desconocido '" << tipo << "'" << endl;
        }
        
    } else if (accion == "EJECUTABLE") {
        if (partes.size() != 2) {
            cout << "ERROR: Formato incorrecto. Uso: EJECUTABLE <nombre>" << endl;
        } else {
            bool resultado = esEjecutable(partes[1]);
            if (resultado) {
                cout << "SI: El programa '" << partes[1] << "' puede ejecutarse" << endl;
            } else {
                cout << "NO: El programa '" << partes[1] << "' NO puede ejecutarse" << endl;
            }
        }
        
    } else if (accion == "SALIR") {
        cout << "Saliendo del simulador..." << endl;
        exit(0);
        
    } else {
        cout << "ERROR: Accion desconocida '" << accion << "'" << endl;
    }
}

void SimuladorT::ejecutar() {
    cout << "=== Simulador de Programas, Interpretes y Traductores ===" << endl;
    cout << "Comandos disponibles:" << endl;
    cout << "  DEFINIR PROGRAMA <nombre> <lenguaje>" << endl;
    cout << "  DEFINIR INTERPRETE <lenguaje_base> <lenguaje>" << endl;
    cout << "  DEFINIR TRADUCTOR <lenguaje_base> <lenguaje_origen> <lenguaje_destino>" << endl;
    cout << "  EJECUTABLE <nombre>" << endl;
    cout << "  SALIR" << endl;
    cout << endl;
    
    // Bucle principal de entrada de comandos
    string comando;
    while (true) {
        cout << "> ";
        getline(cin, comando);
        procesarComando(comando);
        cout << endl;
    }
}