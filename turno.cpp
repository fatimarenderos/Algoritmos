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

bool colocadora(char** gameMatrix, int** numberMatrix, int x, int y, int size){

    bool confirmation = false;

    //Verificando si las coordenadas son valores dentro de los limites de la matriz
    if( x>=size || y>=size ){
        cout<<"Por favor ingrese valores de (x,y) que no sobre pasen los limites de la matriz"<<endl;
        return false;
    }

    //Verificando si las coordenadas no contienen valores negativos
    if( x<0 || y<0 ){
        cout<<"Por favor ingrese valores de (x,y) que sean positivos y vallidos"<<endl;
        return false;
    }


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
        
    //Se guardan las dos tarjetas en variables
    char pos1 = gameMatrix[x1][y1];
    char pos2 = gameMatrix[x2][y2];

    //Si mbas posiciones contiene valores que no son pareja
    if(pos1 != pos2){
        //Se regresan ambas posiciones a X ya que se pierde el turno y no se hizo progreso
        gameMatrix[x1][y1] = 'X';
        gameMatrix[x2][y2] = 'X';
        cout<<endl<<"No eran pareja!!"<<endl;
        return;
    }else{
        //Se cambian los valores de ambas posiciones por guiones, para denotar que ambas ya fueron adivinadas
        gameMatrix[x1][y1] = '-';
        gameMatrix[x2][y2] = '-';
        cout<<endl<<"Eran pareja!! Bien hecho!"<<endl;
        return;
    }
}

void mostrandoCartas(char** gameMatrix, int size){
    //Mostrando la matriz modificada con un loop que va desde el 0 hasta size-1
    for (int i = 0; i < size; i++){
        cout<<endl;
            for (int j = 0; j < size; j++)
            {
                cout<< " | "<< gameMatrix[j][i] << " | ";
            }
        }
    return;
}

bool gameChanger(char** gameMatrix, int size){
    bool win = false;

    //Se recorre toda la matriz buscando si esta o no completa
    for (int i = 0; i < size ; i++){
            for (int j = 0; j < size; j++)
            {
                //Si algo dentro de la matriz no es un guion, significa que todavia hay trajetas sin adivinar/voltear
                //Por lo que se hace un return con la variable win en falso, para indicar que no esta completa la matriz
                if (gameMatrix[j][i] != '-'){
                        return win;
                }
            }
        }

    //En este caso, todo esta vacio (solo guiones) y se dice que ha ganado
    //Se devuelve la variable win en true, para notar que el juego ya ha terminado
    win = true;

return win;
}

void turnoFunction(char** gameMatrix, int** numberMatrix, int& puntaje, int size){
//Creacion de variables
int x1=0;
int x2=0;
int y1=0;
int y2=0;
bool confirmation;
bool gamefinished;

//loop para asegurarse que se metan coordenadas correctas
do{
    //Ingreso de primeras coordenadas (x,y)
    cout<<endl<<"Ingrese sus coordenadas de x: ";
    cin>>x1;
    cout<<"Ingrese sus coordenadas de y: ";
    cin>>y1;
    //Estamos pasando las coordenadas a la funcion que se encarga de guardar los valores en sus posiciones correspondientes
    //Aparte, mandamos el size para validar que no metan coordenadas que exedan la capacidad de memoria
    confirmation = colocadora(gameMatrix, numberMatrix, x1, y1, size); //Se devuelve un valor booleano, true si todo bien y false si algo anda mal
}while (!confirmation); //Aqui verificamos si las coordenadas ingresadas cumplen todos los criterias que hemos designado


//Mostrando la matriz modificada por primera vez
mostrandoCartas(gameMatrix, size);

//loop que se asegura que se metan correctamente las coordenadas
do{
    //Ingreso de segundas coordenadas (x,y)
    cout<<endl<<"Ingrese sus coordenadas de x: ";
    cin>>x2;
    cout<<"Ingrese sus coordenadas de y: ";
    cin>>y2;
    //Estamos pasando las coordenadas a la funcion que se encarga de guardar los valores en sus posiciones correspondientes
    //Aparte, mandamos el size para validar que no metan coordenadas que exedan la capacidad de memoria
    confirmation = colocadora(gameMatrix, numberMatrix, x2, y2, size); //Se devuelve un valor booleano, true si todo bien y false si algo anda mal
}while (!confirmation); //Aqui verificamos si las coordenadas ingresadas cumplen todos los criterias que hemos designado


//Mostrando la matriz modificada por segunda vez
mostrandoCartas(gameMatrix, size);

//Llamando funcion que comparara ambas tarjetas escogidas con sus coordenadas para ver si son o no pareja
comparadora(gameMatrix, x1, y1, x2, y2);

//Mostrando la matriz modificada por tercera vez
mostrandoCartas(gameMatrix, size);

//Verificando si la matriz esta completamente llena de guiones
gamefinished = gameChanger(gameMatrix, size);

//Si la funcion nos devuelve false, no esta completa
if(!gamefinished){
    //Se le restan 100 al puntaje
    puntaje -= 100;
    //Se vuelve a jugar otro turno con los mismos parametros
    turnoFunction(gameMatrix, numberMatrix, puntaje, size);
    return;
}


//Si es verdadero, pues ya gano y pues ya puede retornar, debido a que el puntaje se mando por referencia y se modifica hasta afuera.
    return;
}

int main(void){

int puntaje= 1800;
int size= 6;

//Creando la matriz
    int** matrix = new int*[size];

    for (int i = 0; i < size; i++){
            matrix[i] = new int[size];
    }

//Llenando la matriz
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++)
        {
            if(j%2==0){
                matrix[j][i] = 4;
            }else{
                matrix[j][i] = 5;
            }
        }
    }

//Creando la matriz Char
    char** matrixchar = new char*[size];

    for (int i = 0; i < size; i++){
            matrixchar[i] = new char[size];
    }

//Llenando la matriz
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++)
        {
            matrixchar[j][i] = 'X';
        }
    }


cout<<"Su puntaje original es: "<<puntaje<<endl;

turnoFunction(matrixchar, matrix, puntaje, size);

cout<<"Su puntaje final es: "<<puntaje<<endl;
cout<<"GAME OVER";

    return 0;
}