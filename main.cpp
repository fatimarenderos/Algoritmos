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
        puntaje = 1800;
        break;
    case 2:
        sizeMatrix = 6;
        puntaje = 2800;
        break;
    case 3:
        sizeMatrix = 8;
        puntaje: 4200;
        break;
    default:
        break;
    }

    mostrandoCartas(MatrixMemory, sizeMatrix);

    turnoFunction(MatrixPlay, MatrixMemory, puntaje, sizeMatrix);

    cout<<endl<<"GAME OVER"<<endl;
    cout<<endl<<"Su puntaje final es: "<<puntaje<<endl;

    /*
    int score = 1;
    insertarFinal(&inicio, score, name);
    quickSort(&inicio, 0, 9);
    showList(inicio);
    createCSV(&inicio);
    showList(inicio);
    */
}