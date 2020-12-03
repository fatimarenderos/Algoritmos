#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cctype>
#include <string>
using namespace std;

string funName()
{
    string nombre;
    cout << "Ingrese su nombre: ";
    cin >> nombre;
    return nombre;
}

void mostrandoCartas(char** gameMatrix, int size);

int aleatorio_en_rango(int minimo, int maximo)
{
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}
int NumRandom(int n)
{
    int numero = rand() % n;
    return numero;
}
struct Node
{
    int number;
    string cadena;
    Node *next;
    Node *prev;
};

void insertarInicio(Node **list, int new_number, string cadena)
{
    Node *new_node = new Node();
    new_node->number = new_number;
    new_node->cadena = cadena;
    new_node->next = (*list);
    new_node->prev = NULL;

    if ((*list) != NULL)
        (*list)->prev = new_node;

    (*list) = new_node;
}

void insertarFinal(Node **list, int new_number, string cadena)
{
    Node *new_node = new Node();
    Node *last = *list;
    new_node->number = new_number;
    new_node->cadena = cadena;
    new_node->next = NULL;

    if (*list == NULL)
    {
        new_node->prev = NULL;
        *list = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
    return;
}

void deleteNode(Node **list, Node *del)
{
    if (*list == NULL || del == NULL)
        return;

    if (*list == del)
        *list = del->next;

    if (del->next != NULL)
        del->next->prev = del->prev;

    if (del->prev != NULL)
        del->prev->next = del->next;

    free(del);
    return;
}

Node *findNodeByNumber(Node **list, int number)
{
    Node *last = *list;

    while (last)
    {
        if (last->number == number)
        {
            return last;
        }
        last = last->next;
    }

    return NULL;
}

Node *findNodeByString(Node **list, string cadena)
{
    Node *last = *list;

    while (last)
    {
        if (last->cadena == cadena)
        {
            return last;
        }
        last = last->next;
    }

    return NULL;
}

void deleteNodeAux(Node **list, int number)
{
    Node *nodoBorrar = findNodeByNumber(list, number);
    deleteNode(list, nodoBorrar);
}

void showList(Node *node)
{
    Node *last;
    cout << "\nMostrando list hacia adelante \n";
    while (node != NULL)
    {
        cout << " " << node->number << " ";
        last = node;
        node = node->next;
    }

    cout << "\nMostrando list hacia atras \n";
    while (last != NULL)
    {
        cout << " " << last->number << " ";
        last = last->prev;
    }
}

void swap(Node *a, Node *b)
{
    Node t = *a;
    a->number = b->number;
    a->cadena = b->cadena;
    b->number = t.number;
    b->cadena = t.cadena;
}

Node *findNodeByPosition(Node *node, int position)
{
    Node *last, *aux = node;
    int currentIndex = 0;
    while (aux->next != NULL && currentIndex < position)
    {
        aux = aux->next;
        currentIndex++;
    }
    return aux;
}

int partition(Node **list, int low, int high)
{
    Node *last = *list;
    Node *pivot = findNodeByPosition(last, high);
    int i = (low - 1), result;
    for (int j = low; j <= high - 1; j++)
    {
        Node *current = findNodeByPosition(last, j);
        char *p = &current->cadena[0];
        char *m = &pivot->cadena[0];
        result = strcmp(p, m);
        if (result > 0)
        {
            i++;
            Node *auxI = findNodeByPosition(last, i);
            Node *auxJ = findNodeByPosition(last, j);
            swap(auxI, auxJ);
        }
    }
    Node *auxH = findNodeByPosition(last, i + 1);
    swap(auxH, pivot);
    return (i + 1);
}

void quickSort(Node **list, int low, int high)
{
    if (low < high)
    {
        int pi = partition(list, low, high);
        quickSort(list, low, pi - 1);
        quickSort(list, pi + 1, high);
    }
}

void truncate(Node **list)
{
    Node *node = *list;
    int cont = 0;
    while (node != NULL)
    {
        cont++;
        if (cont > 10)
        {
            deleteNode(list, node);
        }
        node = node->next;
    }
}

void readCSV(Node **list)
{
    fstream fin;

    fin.open("data.csv", ios::in);

    vector<string> row;
    string line, word;

    while (!fin.eof())
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        int currentNumber = atoi(&row[1][0]);
        insertarFinal(list, currentNumber, row[0]);
    }
}

void createCSV(Node **list)
{
    fstream fout;
    fout.open("data.csv", ios::out | ios::app);

    Node *node = *list;

    while (node != NULL)
    {
        fout << node->cadena << ", " << node->number << "\n";
        node = node->next;
    }
}

char **funLLenarMatrixChar(int nivel)
{
    int sizeMatrix;

    switch (nivel)
    {
    case 1:
        sizeMatrix = 4;
        break;
    case 2:
        sizeMatrix = 6;
        break;
    case 3:
        sizeMatrix = 8;
        break;
    default:
        break;
    }
    // DEFINIENDO COOR DE MATRIZ 4X4 Y REORDENANDOLOS

    int listcoordenadas[16][2] =
        {
            {0, 0},{0, 1},{0, 2},{0, 3},
            {1, 0},{1, 1},{1, 2},{1, 3},
            {2, 0},{2, 1},{2, 2},{2, 3},
            {3, 0},{3, 1},{3, 2},{3, 3},
        };

    int listcoordenadas6[36][2] =
        {
           {0, 0},{0, 1},{0, 2},{0, 3},{0, 4},{0, 5},
            {1, 0},{1, 1},{1, 2},{1, 3},{1, 4},{1, 5},
            {2, 0},{2, 1},{2, 2},{2, 3},{2, 4},{2, 5},
            {3, 0},{3, 1},{3, 2},{3, 3},{3, 4},{3, 5},
            {4, 0},{4, 1},{4, 2},{4, 3},{4, 4},{4, 5},
            {5, 0},{5, 1},{5, 2},{5, 3},{5, 4},{5, 5},
        };

    int listcoordenadas8[64][2] =
        {
            {0, 0},{0, 1},{0, 2},{0, 3},{0, 4},{0, 5},{0, 6},{0, 7},
            {1, 0},{1, 1},{1, 2},{1, 3},{1, 4},{1, 5},{1, 6},{1, 7},
            {2, 0},{2, 1},{2, 2},{2, 3},{2, 4},{2, 5},{2, 6},{2, 7},
            {3, 0},{3, 1},{3, 2},{3, 3},{3, 4},{3, 5},{3, 6},{3, 7},
            {4, 0},{4, 1},{4, 2},{4, 3},{4, 4},{4, 5},{4, 6},{4, 7},
            {5, 0},{5, 1},{5, 2},{5, 3},{5, 4},{5, 5},{5, 6},{5, 7},
            {6, 0},{6, 1},{6, 2},{6, 3},{6, 4},{6, 5},{6, 6},{6, 7},
            {7, 0},{7, 1},{7, 2},{7, 3},{7, 4},{7, 5},{7, 6},{7, 7},

        };

    /*
    for (int i = 0; i < sizeMatrix * sizeMatrix; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            switch (sizeMatrix)
            {
            case 4:
                cout << listcoordenadas[i][j] << " ";
                break;
            case 6:
                cout << listcoordenadas6[i][j] << " ";
                break;
            case 8:
                cout << listcoordenadas[i][j] << " ";
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
    cout << endl;
*/
    srand(getpid());

    for (int i = 0; i < sizeMatrix * sizeMatrix; i++)
    {
        int indiceAleatorio, temporalx, temporaly;

        switch (sizeMatrix)
        {
        case 4:
            indiceAleatorio = NumRandom(sizeMatrix * sizeMatrix);
            // Intercambiar el actual con un elemento del índice aleatorio
            temporalx = listcoordenadas[i][0];
            temporaly = listcoordenadas[i][1];

            listcoordenadas[i][0] = listcoordenadas[indiceAleatorio][0];
            listcoordenadas[i][1] = listcoordenadas[indiceAleatorio][1];
            listcoordenadas[indiceAleatorio][0] = temporalx;
            listcoordenadas[indiceAleatorio][1] = temporaly;
            break;
        case 6:
            indiceAleatorio = NumRandom(sizeMatrix * sizeMatrix);
            // Intercambiar el actual con un elemento del índice aleatorio
            temporalx = listcoordenadas6[i][0];
            temporaly = listcoordenadas6[i][1];

            listcoordenadas6[i][0] = listcoordenadas6[indiceAleatorio][0];
            listcoordenadas6[i][1] = listcoordenadas6[indiceAleatorio][1];
            listcoordenadas6[indiceAleatorio][0] = temporalx;
            listcoordenadas6[indiceAleatorio][1] = temporaly;
            break;
        case 8:
            indiceAleatorio = NumRandom(sizeMatrix * sizeMatrix);
            // Intercambiar el actual con un elemento del índice aleatorio
            temporalx = listcoordenadas8[i][0];
            temporaly = listcoordenadas8[i][1];

            listcoordenadas8[i][0] = listcoordenadas8[indiceAleatorio][0];
            listcoordenadas8[i][1] = listcoordenadas8[indiceAleatorio][1];
            listcoordenadas8[indiceAleatorio][0] = temporalx;
            listcoordenadas8[indiceAleatorio][1] = temporaly;
            break;
        default:
            break;
        }
    }

    /* for (int i = 0; i < sizeMatrix * sizeMatrix; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            switch (sizeMatrix)
            {
            case 4:
                cout << listcoordenadas[i][j] << " ";
                break;
            case 6:
                cout << listcoordenadas6[i][j] << " ";
                break;
            case 8:
                cout << listcoordenadas8[i][j] << " ";
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
    cout << endl;

    */

    // INICIALIZANDO LISTA DE PAREJAS EN MEMORIA
    int intNumPares = sizeMatrix * sizeMatrix / 2;

    int listNumRandom[intNumPares];

    srand(time(0));

    for (int i = 0; i < intNumPares; i++)
    {
        listNumRandom[i] = aleatorio_en_rango(33, 100);
        //cout << listNumRandom[i] << " ";
    }
    cout << endl;

    // DEFINIENDO COOR DE MATRIZ 4X4 Y REORDENANDOLOS

    char **MatrixMemory = new char *[sizeMatrix];

    for (int i = 0; i < sizeMatrix; i++)
    {
        MatrixMemory[i] = new char[sizeMatrix];

        for (int j = 0; j < sizeMatrix; j++)
        {
            MatrixMemory[i][j] = 'X';
            //cout << MatrixMemory[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;

    // LLENANDO MATRIZ DE JUEGO
    int contCoor = 0;

    for (int i = 0; i < sizeMatrix * sizeMatrix; i++)
    {
        switch (sizeMatrix)
        {
        case 4:
            if (contCoor == intNumPares)
            {
                contCoor = 0;
                MatrixMemory[listcoordenadas[i][0]][listcoordenadas[i][1]] = (char)listNumRandom[contCoor];
                contCoor++;
            }
            else
            {
                MatrixMemory[listcoordenadas[i][0]][listcoordenadas[i][1]] = (char)listNumRandom[contCoor];
                contCoor++;
            }
            break;
        case 6:
            if (contCoor == intNumPares)
            {
                contCoor = 0;
                MatrixMemory[listcoordenadas6[i][0]][listcoordenadas6[i][1]] = (char)listNumRandom[contCoor];
                contCoor++;
            }
            else
            {
                MatrixMemory[listcoordenadas6[i][0]][listcoordenadas6[i][1]] = (char)listNumRandom[contCoor];
                contCoor++;
            }
            break;
        case 8:
            if (contCoor == intNumPares)
            {
                contCoor = 0;
                MatrixMemory[listcoordenadas8[i][0]][listcoordenadas8[i][1]] = (char)listNumRandom[contCoor];
                contCoor++;
            }
            else
            {
                MatrixMemory[listcoordenadas8[i][0]][listcoordenadas8[i][1]] = (char)listNumRandom[contCoor];
                contCoor++;
            }
            break;
        default:
            break;
        }
    }

    /*
    for (int i = 0; i < sizeMatrix; i++)
    {
        for (int j = 0; j < sizeMatrix; j++)
        {

            cout << MatrixMemory[i][j] << " ";
        }
        cout << endl;
    }
*/

    return MatrixMemory;
}

char **funLLenarMatrixInt(int nivel)
{

    int sizeMatrix;

    switch (nivel)
    {
    case 1:
        sizeMatrix = 4;
        break;
    case 2:
        sizeMatrix = 6;
        break;
    case 3:
        sizeMatrix = 8;
        break;
    default:
        break;
    }

    char **MatrixPlay = new char *[sizeMatrix];

    for (int i = 0; i < sizeMatrix; i++)
    {
        MatrixPlay[i] = new char[sizeMatrix];

        for (int j = 0; j < sizeMatrix; j++)
        {
            MatrixPlay[i][j] = 'X';
            //cout << MatrixPlay[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;

    //mostrandoCartas(MatrixPlay, sizeMatrix);

    return MatrixPlay;
}

//Logica de turno de jugador
bool colocadora(char** gameMatrix, char** numberMatrix, string newX, string newY, int size){

    bool confirmation = false;

    //Haciendo la asignacion de true/false dependiendo de si el primer digito del string tomado en un numero o un caracter
    //Esto eliminara las letras y los negativos de una sola vez
    bool letterX = isdigit(newX.at(0));
    bool letterY = isdigit(newY.at(0));

    //Verificando si las coordenadas no son letras o negativos
    if( !letterX || !letterY ){
        cout<<"Por favor ingrese valores de (x,y) que no sean letras ni negativos! Se admiten solo numeros positivos"<<endl;
        return false;
    }

    //Al pasar a aqui, nos aseguramos que no hay letras ni negativos validados
    //Casteando las coordenadas string a int, ya que podemos recibir uno o varios numeros
    int x = stoi(newX);
    int y = stoi(newY);


        //Verificando si las coordenadas son valores dentro de los limites de la matriz
    if( x>=size || y>=size || x<0 || y<0 ){
        cout<<"Por favor ingrese valores de (x,y) que no sobre pasen los limites de la matriz"<<endl;
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
    //char tarjeta = '0' + placeholder;

    //El valor char se guarda en la matriz de juego en la posicion deseada
    gameMatrix[x][y] = placeholder ;

    return true;
}

void comparadora(char** gameMatrix, string newx1, string newy1, string newx2, string newy2){

    //Parseando los char a int para poder usarlos como coordenadas de matrices (se le resta 48 por que ascii comienza desde el 48)
    int x1 = stoi(newx1);
    int x2 = stoi(newx2);
    int y1 = stoi(newy1);
    int y2 = stoi(newy2);

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

void turnoFunction(char** gameMatrix, char** numberMatrix, int& puntaje, int size){
//Creacion de variables
string x1;
string x2;
string y1;
string y2;
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
