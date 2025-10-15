//Cristina Gómez
//19-10266
//Examen 1
//Pregunta reto 

// para compilara: g++ -o pregunta_reto pregunta_reto.cpp
// para ejecutar: ./pregunta_reto <n>

#include <iostream>
#include <cmath>

using namespace std;

int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <n>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);
    
    double N = (n * n * (n * n - 1)) / 12.0;
    int m = floor(log2(N)) + 1;
    
    cout << fib(m) << endl;
    
    return 0;
}