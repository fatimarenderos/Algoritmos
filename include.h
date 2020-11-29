#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

string funName()
{
    string nombre;
    cout << "Ingrese su nombre ";
    cin >> nombre;
    return nombre;
}

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
        listNumRandom[i] = aleatorio_en_rango(33, 175);
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
            cout << MatrixMemory[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

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

int **funLLenarMatrixInt(int nivel)
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

    int **MatrixPlay = new int *[sizeMatrix];

    for (int i = 0; i < sizeMatrix; i++)
    {
        MatrixPlay[i] = new int[sizeMatrix];

        for (int j = 0; j < sizeMatrix; j++)
        {
            MatrixPlay[i][j] = 0;
            cout << MatrixPlay[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return MatrixPlay;
}