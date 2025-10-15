//Cristina Gómez
//19-10266
//Examen 1
//Pregunta 1b2: Programa que calcule A × A^T, donde A es una matriz cuadrada de dimensión N x N

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    
    cout << "Ingrese la dimension N de la matriz cuadrada (N x N): ";
    cin >> N;
    
    vector<vector<int>> A(N, vector<int>(N));
    
    //Solicitamos los elementos de la matriz A
    cout << "\nIngrese los elementos de la matriz A:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> A[i][j];
        }
    }
    
    //Calcular A × A^T 
    vector<vector<int>> resultado(N, vector<int>(N, 0));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                //(A × A^T)[i][j] = Sumatoria de A[i][k] × A^T[k][j] = Sumatoria de A[i][k] × A[j][k]
                resultado[i][j] += A[i][k] * A[j][k];
            }
        }
    }
    
    //Imprime la matriz original
    cout << "\nMatriz A original:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    //Imprime la matriz resultado
    cout << "\nResultado de A x A^T:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << resultado[i][j] << "\t";
        }
        cout << endl;
    }
    
    return 0;
}