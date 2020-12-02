#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include "include.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

bool colocadora(char** gameMatrix, int** numberMatrix, int x, int y){

    bool confirmation = false;
    //guardando el valor de la matriz de numeros en la posicion especificada
    char placeholder = numberMatrix[x][y];

    //Verificando si en la matriz de juego no haya un numero o un guion (ya haya sido descubierto)
    if( gameMatrix[x][y] != 'X'){
        cout<<"Esta casilla ya esta volteada o ya fue adivinada, ingrese otras coordenadas."<<endl;
        return false;
    }

    //Aqui ya nos aseguramos que la matriz de juego si tiene una X en esa coordenada, por ende, si puede cambiarse
    //Se castea el valor int conseguido a un char
    char tarjeta = '0' + placeholder;
    //El valor casteado se guarda en la matriz de juego
    gameMatrix[x][y] = tarjeta ;

    return true;
}

void comparadora(char** gameMatrix, int x1, int y1, int x2, int y2){
        
    //Se guardan las tarjetas en variables
    char pos1 = gameMatrix[x1][y1];
    char pos2 = gameMatrix[x2][y2];

    //Ambas posiciones contiene valores que no son pareja
    if(pos1 != pos2){
        //Se regresan ambas posiciones a X ya que se pierde el turno 
        gameMatrix[x1][y1] = 'X';
        gameMatrix[x2][y2] = 'X';
        cout<<endl<<"No eran pareja!!"<<endl;
        return;
    }else{
        gameMatrix[x1][y1] = '-';
        gameMatrix[x2][y2] = '-';
        cout<<endl<<"Eran pareja!! Bien hecho!"<<endl;
        return;
    }
}

void mostrandoCartas(char** gameMatrix){
    //Mostrando la matriz modificada
    for (int i = 0; i < 4; i++){
        cout<<endl;
            for (int j = 0; j < 4; j++)
            {
                cout<< " | "<< gameMatrix[j][i] << " | ";
            }
        }
    return;
}

bool gameChanger(char** gameMatrix){
    bool win = false;

    for (int i = 0; i < 4 ; i++){
            for (int j = 0; j < 4; j++)
            {
                //Si algo dentro de la matriz no es un guion, significa que todavia hay trajetas sin adivinar/voltear
                if (gameMatrix[j][i] != '-'){
                        return win;
                }
            }
        }
    //En este caso, todo esta vacio (solo guiones) y se dice que ha ganado
    win = true;

return win;
}

void turnoFunction(char** gameMatrix, int** numberMatrix, int& puntaje){
int x1=0;
int x2=0;
int y1=0;
int y2=0;
bool confirmation;

//loop para asegurarse que se metan coordenadas correctas
do{
    cout<<endl<<"Ingrese sus coordenadas de x: ";
    cin>>x1;
    cout<<"Ingrese sus coordenadas de y: ";
    cin>>y1;
    confirmation = colocadora(gameMatrix, numberMatrix, x1, y1);
}while (!confirmation);


//Mostrando la matriz modificada por primera vez
mostrandoCartas(gameMatrix);

//loop que se asegura que se metan correctamente las coordenadas
do{
    cout<<endl<<"Ingrese sus coordenadas de x: ";
    cin>>x2;
    cout<<"Ingrese sus coordenadas de y: ";
    cin>>y2;
    confirmation = colocadora(gameMatrix, numberMatrix, x2, y2);
}while (!confirmation);


//Mostrando la matriz modificada por segunda vez
mostrandoCartas(gameMatrix);

//Llamando funcion que comparara ambas tarjetas escogidas
comparadora(gameMatrix, x1, y1, x2, y2);

//Mostrando la matriz modificada por tercera vez
mostrandoCartas(gameMatrix);

//Verificando si la matriz esta completamente llena de guiones
bool gamefinished = gameChanger(gameMatrix);
cout<<endl<<"La matriz esta completa? "<<gamefinished<<endl;
//Si la funcion nos devuelve false, no esta completa
if(!gamefinished){
    //Se le suma uno al puntaje
    puntaje -= 10;
    cout<<"Su puntaje original es: "<<puntaje<<endl;
    //Se vuelve a jugar otro turno
    turnoFunction(gameMatrix, numberMatrix, puntaje);
    return;
}


//Si es verdadero, pues ya gano y pues ya puede retornar, debido a que el puntaje se mando por referencia y se modifica hasta afuera.
    return;
}

int main(void){

//Creando la matriz
    int** matrix = new int*[4];

    for (int i = 0; i < 4; i++){
            matrix[i] = new int[4];
    }

//Llenando la matriz
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
        {
            if(j%2==0){
                matrix[j][i] = 4;
            }else{
                matrix[j][i] = 5;
            }
        }
    }

//Creando la matriz Char
    char** matrixchar = new char*[4];

    for (int i = 0; i < 4; i++){
            matrixchar[i] = new char[4];
    }

//Llenando la matriz
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
        {
            matrixchar[j][i] = 'X';
        }
    }

int puntaje= 1000;
cout<<"Su puntaje original es: "<<puntaje<<endl;

turnoFunction(matrixchar, matrix, puntaje);

cout<<"Su puntaje original es: "<<puntaje<<endl;
cout<<"GAME OVER";

    return 0;
}