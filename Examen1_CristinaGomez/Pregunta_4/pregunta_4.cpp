//Cristina Gómez
//19-10266
//Examen 1
//Pregunta 4: Modulo de operaciones con vectores en 3D

#include <iostream>
#include <cmath>
using namespace std;

class Vector3D {
public:
    double x, y, z;

    //Constructor
    Vector3D(double x = 0, double y = 0, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    //Suma de vectores
    Vector3D suma(const Vector3D& otro) const {
        return Vector3D(x + otro.x, y + otro.y, z + otro.z);
    }
    
    //Resta de vectores
    Vector3D resta(const Vector3D& otro) const {
        return Vector3D(x - otro.x, y - otro.y, z - otro.z);
    }
    
    //Producto cruz
    Vector3D producto_cruz(const Vector3D& otro) const {
        return Vector3D(
            y * otro.z - z * otro.y,
            z * otro.x - x * otro.z,
            x * otro.y - y * otro.x
        );
    }
    
    //Producto punto
    double producto_punto(const Vector3D& otro) const {
        return x * otro.x + y * otro.y + z * otro.z;
    }
    
    //Norma
    double norma() const {
        return sqrt(x * x + y * y + z * z);
    }
    
    //Operaciones con escalares
    Vector3D suma_escalar(double n) const {
        return Vector3D(x + n, y + n, z + n);
    }
    
    Vector3D resta_escalar(double n) const {
        return Vector3D(x - n, y - n, z - n);
    }
    
    Vector3D multiplica_escalar(double n) const {
        return Vector3D(x * n, y * n, z * n);
    }
    
    //Comparacion de si son iguales dos vectores
    bool es_igual(const Vector3D& otro) const {
        return x == otro.x && y == otro.y && z == otro.z;
    }
    
    //Ver si es el vector cero
    bool es_cero() const {
        return x == 0 && y == 0 && z == 0;
    }
    
    void imprimir() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
};