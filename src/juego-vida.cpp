/******************************************************************************\
 * Programación 1. Práctica 5
 * Autor: Antonio José González Almela
 * Ultima revisión: 22/11/2022
 * Resumen: Fichero de implementación del módulo principal del programa del 
 *          Juego de la vida en la 5.ª práctica.
 * Nota: El programa completo está contenido en este fichero, por lo que puede 
 *       compilarse y ejecutarse con la extensión Code Runner de Visual Studio 
 *       Code.
 *       No obstante, se ha configurado el fichero «Makefile» para poder 
 *       compilarlo y se han definido tareas de VSC para compilarlo, ejecutarlo 
 *       y depurarlo.
 *       Para compilarlo, se puede ejecutar el comando
 *           make juego-vida
 *       o, en Windows,
 *           mingw32-make juego-vida
 *       o ejecutar la tarea "Compilar «juego-vida»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/juego-vida
 *       o, en Windows,
 *           bin\juego-vida.exe
 *       o ejecutar la tarea "Ejecutar «juego-vida»" de VSC.
\******************************************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

const unsigned MAX_FILAS = 50;
const unsigned MAX_COLUMNAS = 50;

/*
 * Pre:  ---
 * Post: Borra la parte visible del terminal y mueve el cursor a la primera
 *       fila y la primera columna, de forma que la siguiente instrucción de 
 *       escritura en pantalla escriba desde el inicio de la parte visible del
 *       terminal.
 */
void borrarPantalla() {
    cout << "\033[2J";
}

/*
 * Pre:  ---
 * Post: Sube el cursor de escritura del terminal «lineas» líneas, sin borrar
 *       el contenido que ya esté escrito en el terminal.
 */
void subirCursor(const unsigned lineas) {
    cout << "\033[" << lineas << "A";
}

/*
 * Pre:  ---
 * Post: Pide al usuario los datos para desarrollar el juego de la vida.
 * Número de filas mayor que 0 y menor o igual que MAX_FILAS
 * Número de columnas mayor que 0 y menor o igual que MAX_COLUMNAS
 * Número de generaciones a simular mayor que 0
 */
void pideDatos(int& numFilas, int& numColumnas, int& generaciones ) {
    
    do {
        cout << "Número de filas: ";
        cin >> numFilas;
    } while(numFilas < 0 || numFilas > int(MAX_FILAS));

    do {
        cout << "Número de Columnas: ";
        cin >> numColumnas;
    } while(numColumnas <= 0 || numColumnas > int(MAX_COLUMNAS));

    do {
        cout << "Número de generaciones: ";
        cin >> generaciones;
    } while(generaciones < 0);

}

/*
 * Pre:  tablero es una matriz de booleanos con MAX_FILAS x MAX_COLUMNAS
 *        0 < numFilas <= MAX_FILAS
 *        0 < numColumnas <= MAX_COLUMNAS
 *       
 * Post: Genera un tablero de numFilas x numColumnas en la matriz
 *       tablero y llena las celdas con células de forma aleatoria,
 *       cumpliendo que la probabilidad de una celda contener una célula es
 *       del 20%.
 */
void iniciaTablero(bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas) {
    for (unsigned i = 0; i < unsigned(numFilas); i++){
        for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
            tablero[i][j] = (double(rand()) / RAND_MAX) <= 0.2;
        }
    }
}

/*
 * Pre:  tablero es una matriz de booleanos con MAX_FILAS x MAX_COLUMNAS
 *        0 < numFilas <= MAX_FILAS
 *        0 < numColumnas <= MAX_COLUMNAS
 *       
 * Post: Muestra en pantalla el contenido de tablero de numFilas x numColumnas
 *       cuando el contenido de la celda es 'true' escribe '*'
 *       cuando el contenido de la celda es 'false' escribe ' '
 */
void imprimeTablero(bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas) {
     for (unsigned i = 0; i < unsigned(numFilas); i++){
        for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
            cout << setw(2) << (tablero[i][j] ? '*' : ' ');
        }
        cout << endl;
    }
}

/*
 * Pre:  tablero es una matriz de booleanos con MAX_FILAS x MAX_COLUMNAS
 *        0 < numFilas <= MAX_FILAS
 *        0 < numColumnas <= MAX_COLUMNAS
 *       
 * Post: Muestra en pantalla el contenido de tablero de numFilas x numColumnas
 *       cuando el contenido de la celda es 'true' escribe '*'
 *       cuando el contenido de la celda es 'false' escribe ' '
 */
unsigned cuentaVivas(bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas) {
    unsigned vivas = 0;
    for (unsigned i = 0; i < unsigned(numFilas); i++){
        for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
            vivas += tablero[i][j];
        }
    }
    return vivas;
}

/*
 * Pre:  tablero es una matriz de booleanos con MAX_FILAS x MAX_COLUMNAS
 *        0 < numFilas <= MAX_FILAS
 *        0 < numColumnas <= MAX_COLUMNAS
 *       
 * Post: Aplica las reglas del juego de la vida a todas las celdas de tablero
 *       para avanzar a la siguiente generación
 */
void avanzaGeneracion(bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas) {
 for (unsigned i = 0; i < 1000000; i++){
    int a;
    a = i - 1;}
}

int main() {
    srand(time(NULL));
    // Posibles valores de una celda del tablero:
    // false: Vacía
    // true: Célula viva
    // Declara matriz de MAX_FILAS x MAX_COLUMNAS
    // e inicializa como celdas vacías
    bool tablero[MAX_FILAS][MAX_COLUMNAS] = {false};

    int numFilas, numColumnas, generaciones;
    pideDatos(numFilas, numColumnas, generaciones);

    iniciaTablero(tablero, numFilas, numColumnas);

    borrarPantalla();
    cout << "Generación 0" << endl;
    imprimeTablero(tablero, numFilas, numColumnas);
    
    for (unsigned g = 1; g <= unsigned(generaciones); g++) {
        subirCursor(numFilas + 1);
        cout << "Generación " << g  << endl;
        imprimeTablero(tablero, numFilas, numColumnas);
        avanzaGeneracion(tablero, numFilas, numColumnas);
    }
    
    return 0;
}

// cout << "Hay " << cuentaVivas(tablero, numFilas, numColumnas) << " vivas" << endl;
//     cout << "que es un " << (double(cuentaVivas(tablero, numFilas, numColumnas))/(numFilas*numColumnas)*100) << "%" << endl;