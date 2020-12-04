#include <iostream>
#include <cstdlib>
#include <ctime>
#include "include.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main(int argc, char const *argv[])
{
    Node *inicio = NULL;
    int nivel = 0, sizeMatrix;
    int puntaje =0;

    string name = funName();

    cout << "Menu" << endl
         << "1. Nivel facil " << endl
         << "2. Nivel intermedio " << endl
         << "3. Nivel dificil " << endl
         << "Ingrese el nivel de complejidad: " << endl;

    cin >> nivel;
    cout<<endl;

    char **MatrixPlay = funLLenarMatrixInt(nivel);
    char **MatrixMemory = funLLenarMatrixChar(nivel);

   switch (nivel)
    {
    case 1:
        sizeMatrix = 4;
        puntaje = 10000;
        break;
    case 2:
        sizeMatrix = 6;
        puntaje = 30000;
        break;
    case 3:
        sizeMatrix = 8;
        puntaje = 50000;
        break;
    default:
        break;
    }

    //Esto es un comodin por si el jugador quiere ver la matriz inicial
    //mostrandoCartas(MatrixMemory, sizeMatrix);

    turnoFunction(MatrixPlay, MatrixMemory, puntaje, sizeMatrix);

    cout<<endl<<"GAME OVER"<<endl;
    cout<<endl<<"Su puntaje final es: "<<puntaje<<endl;

    
    readCSV(&inicio);
    insertarFinal(&inicio, puntaje, name);
    quickSort(&inicio, 0, 100);
    truncate(&inicio);
    showList(inicio);
    createCSV(&inicio);

    return 0;
}
