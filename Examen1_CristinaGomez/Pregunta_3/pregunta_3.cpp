//Cristina Gómez
//19-10266
//Examen 1
//Archivo .cpp de la pregunta 3: Implementación del Buddy System

#include "pregunta3.h"

using namespace std;

//Constructor del Buddy System
BuddySystem::BuddySystem(int size) {
    //Verificar que el tamaño sea potencia de 2
    if (size <= 0 || (size & (size - 1)) != 0) {
        throw invalid_argument("El tamaño de la memoria debe ser potencia de 2");
    }
    this->size = size;
    //Inicializar la lista de bloques libres
    bloque_libre[size] = vector<int>{0};
}

//Calcula la siguiente potencia de 2
int BuddySystem::sig_potencia(int n) {
    return pow(2, ceil(log2(n)));
}

//Busca el bloque libre mas pequeño que pueda cumplir con el tamaño minimo requerido
int BuddySystem::buscar_bloque_libre(int min) {
    for (auto& pair : bloque_libre) {
        int tam = pair.first;
        if (tam >= min && !pair.second.empty()) {
            return tam;
        }
    }
    return -1; //No se encontro ningun bloque adecuado
}

//Divide recursivamente un bloque hasta alcanzar el tamaño deseado
void BuddySystem::dividir(int size_actual, int size_deseado) {
    while (size_actual > size_deseado) {
        //Toma la primera posicion disponible del bloque actual
        int pos = bloque_libre[size_actual].front();
        bloque_libre[size_actual].erase(bloque_libre[size_actual].begin());
        
        int mitad = size_actual / 2;
        //Agregar ambos a la lista de bloques libres del nuevo tamaño
        bloque_libre[mitad].push_back(pos);
        bloque_libre[mitad].push_back(pos + mitad);
        size_actual = mitad;
    }
}

//Fusiona bloques cuando ambos estan libres
void BuddySystem::fusionar(int pos, int size) {
    int buddy = pos ^ size;
    auto& lista = bloque_libre[size];
    
    //Buscar si el buddy esta en la lista de bloques libres
    bool buddy_encontrado = false;
    for (auto it = lista.begin(); it != lista.end(); ) {
        if (*it == buddy) {
            it = lista.erase(it);
            buddy_encontrado = true;
            break;
        } else {
            ++it;
        }
    }
    
    //Eliminar la posicion actual de la lista de bloques libres
    for (auto it = lista.begin(); it != lista.end(); ) {
        if (*it == pos) {
            it = lista.erase(it);
            break;
        } else {
            ++it;
        }
    }
    
    //Si se encontro el buddy, fusionar y continuar recursivamente
    if (buddy_encontrado) {
        int nuevo_pos = min(pos, buddy);
        fusionar(nuevo_pos, size * 2);
    } else {
        //Si no hay buddy libre, simplemente agrega el bloque a la lista
        bloque_libre[size].push_back(pos);
    }
}

//Reserva un bloque de memoria del tamaño y el nombre dado
void BuddySystem::reservar(int cantidad, const string& nombre) {
    //Validaciones de entrada
    if (asig.find(nombre) != asig.end()) {
        throw runtime_error("El nombre '" + nombre + "' ya está reservado");
    }
    if (cantidad <= 0) {
        throw runtime_error("Cantidad inválida");
    }
    if (nombre.empty()) {
        throw runtime_error("El nombre no puede estar vacío");
    }

    //Calcular el tamaño de bloque necesario (potencia de 2)
    int bloque = sig_potencia(cantidad);
    //Buscar un bloque libre que pueda cumplir con la solicitud
    int size_actual = buscar_bloque_libre(bloque);
    
    if (size_actual == -1) {
        throw runtime_error("No hay memoria suficiente");
    }
    
    //Dividir el bloque encontrado hasta alcanzar el tamaño necesario
    dividir(size_actual, bloque);
    int pos = bloque_libre[bloque].front();
    bloque_libre[bloque].erase(bloque_libre[bloque].begin());
    asig[nombre] = make_pair(pos, bloque);
    
    cout << " El bloque '" << nombre << "' se reservo con " << bloque 
         << " unidades en la posición [" << pos << "].\n" << endl;
}

//Libera un bloque de memoria previamente reservado
void BuddySystem::liberar(const string& nombre) {
    //Verificar que el bloque exista
    if (asig.find(nombre) == asig.end()) {
        throw runtime_error("No existe el bloque '" + nombre + "' reservado");
    }
    
    //Obtener posicion y tamaño del bloque a liberar
    auto [pos, bloque] = asig[nombre];
    asig.erase(nombre);
    //Agregar el bloque liberado a la lista de bloques libres
    bloque_libre[bloque].push_back(pos);
    fusionar(pos, bloque);
    
    cout << "Bloque '" << nombre << "' liberado." << endl;
}

//Muestra el estado actual de la memoria
void BuddySystem::mostrar() {
    cout << "\n=Estado de Memoria=" << endl;
    cout << "Bloques libres: (ej: 4: [4] quiere decir 4 unidades libres en la posición 4, [] quiere decir que no hay espacio en ese bloque de memoria)" << endl;
    for (auto& pair : bloque_libre) {
        cout << "  " << pair.first << ": [";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            cout << pair.second[i];
            if (i < pair.second.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << "Bloques reservados:" << endl;
    for (auto& pair : asig) {
        cout << "  " << pair.first << ": posición " << pair.second.first 
             << ", tamaño " << pair.second.second << endl;
    }
    cout << "\n" << endl;
}