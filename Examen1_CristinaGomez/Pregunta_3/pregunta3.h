//Cristina Gómez
//19-10266
//Examen 1
//Archivo .h de la pregunta 3


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>

class BuddySystem {
private:
    int size;
    std::map<int, std::vector<int>> bloque_libre;
    std::map<std::string, std::pair<int, int>> asig;

    int sig_potencia(int n);
    int buscar_bloque_libre(int min);
    void dividir(int size_actual, int size_deseado);
    void fusionar(int pos, int size);

public:
    BuddySystem(int size);
    void reservar(int cantidad, const std::string& nombre);
    void liberar(const std::string& nombre);
    void mostrar();
};
