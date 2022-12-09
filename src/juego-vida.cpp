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
const double PROPORCION_INICIO = 0.2;

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
 *       del (PROPORCION_INICIO * 100)%.
 */
void iniciaTablero(bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas) {
    for (unsigned i = 0; i < unsigned(numFilas); i++){
        for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
            tablero[i][j] = (double(rand()) / RAND_MAX) <= PROPORCION_INICIO;
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
void imprimeTablero(const bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas) {
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
 * Post: Recorre todas las celdas de la matriz tablero y devuelve el número
 *       acumulado de celdas que contienen true
 */
unsigned cuentaVivas(const bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas) {
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
 *        0 <= fila < numFilas
 *        0 <= columna < numColumnas 
 *       
 * Post: Calcula el número de celdas de tablero que son adyacentes a la
 *       celda (fila,columna) y cuyo valor es true
 */
unsigned vecinas(const bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas, const int fila,
                const int columna) {
        // Inicializa contador de células vivas
        unsigned vivas = 0;
        // Declara variables donde inicia y finaliza la fila/columna de vecinas
        int inicioFila, finFila, inicioColumna, finColumna;
        // Si estoy en fila 0 no hay fila anterior
        inicioFila = fila == 0 ? 0 : fila - 1;
        // Si estoy en última fila, no hay fila posterior
        finFila = fila == numFilas - 1 ? fila : fila + 1;
        // Si estoy en columna 0 no ha columna anterior
        inicioColumna = columna == 0 ? 0 : columna - 1;
        // Si estoy en última columna, no hay columna posterior
        finColumna = columna == numColumnas - 1 ? columna : columna + 1;
        for (int i = inicioFila; i <= finFila; i++) {
            for (int j = inicioColumna; j <= finColumna; j++) {
                if(i == fila) {
                    // Si estoy en la fila de la celda seleccionada, no suma en columna
                    if (j != columna) {
                        // Solo suma si estoy en columna anterior o posterior
                        vivas += tablero[i][j];
                    } 
                } else {
                // Si no estoy en la fila de la celda seleccionada, suma tres celdas adyacentes
                    vivas += tablero[i][j];
                }
            }
        }
        return vivas;
    }

/*
 * Pre:   generacionAnterior es una matriz de booleanos con MAX_FILAS x MAX_COLUMNAS
 *        0 < numFilas <= MAX_FILAS
 *        0 < numColumnas <= MAX_COLUMNAS
 *        generacionActual es una matriz de booleanos con MAX_FILAS x MAX_COLUMNAS
 *       
 * Post: Copia el contenido de generacionActual en generacionAnterior
 */
void copiaGeneracionActual(bool generacionAnterior[][MAX_COLUMNAS], const bool generacionActual[][MAX_COLUMNAS],
                        const int numFilas, const int numColumnas) {
    for (unsigned i = 0; i < unsigned(numFilas); i++){
        for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
            generacionAnterior[i][j] = generacionActual[i][j];
        }
    }
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
    // Variable para almacenar el número de vecinas vivas de cada celda
    unsigned vecinasVivas = 0;
    // Declara tablero adicional para guardar la nueva generación
    bool siguienteTablero[MAX_FILAS][MAX_COLUMNAS] = {false};
    // Recorre en dos bucles anidados todos las celdas del tablero
    for (unsigned i = 0; i < unsigned(numFilas); i++){
        for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
            // Calcula y almacena el número de células vivas adyacentes a la celda actual
            vecinasVivas = vecinas(tablero, numFilas, numColumnas, i, j);
            if (tablero[i][j]) { // En la celda actual hay una célula viva
                if (vecinasVivas < 2) {
                    // En siguiente generación muere por inanición
                    siguienteTablero[i][j] = false; 
                } else if (vecinasVivas < 4) {
                    // En siguiente generación sobrevive al tener 2 o 3 vecinas vivas
                    siguienteTablero[i][j] = true;
                } else {
                    // En siguiente generación muere por superpoblación
                    siguienteTablero[i][j] = false;
                }
            } else {
                // En esta generación esta celda está vacía
                if (vecinasVivas == 3) {
                    // Nace una nueva célula si tiene tres vecinas vivas
                    siguienteTablero[i][j] = true;
                }
            }
        }
    }
    copiaGeneracionActual(tablero, siguienteTablero, numFilas, numColumnas);
}

/*
 * Pre:  tablero es una matriz de booleanos con MAX_FILAS x MAX_COLUMNAS
 *        0 < numFilas <= MAX_FILAS
 *        0 < numColumnas <= MAX_COLUMNAS
 *       generaciones es el número de generaciones a simular
 *       la Generación 0 ha sido creada aleatoriamente y mostrada
 *       
 * Post: Realiza la simulación del juego de la vida el número de veces
 *       representado por generaciones. Imprime el resultado de cada
 *       nueva generación.
 */
void simulaGeneraciones(bool tablero[][MAX_COLUMNAS], const int numFilas, const int numColumnas,
                        const int generaciones){
    unsigned g = 1;
    while (g <= unsigned(generaciones) && cuentaVivas(tablero, numFilas, numColumnas)) {
        subirCursor(numFilas + 1);
        cout << "Generación " << g  << endl;
        avanzaGeneracion(tablero, numFilas, numColumnas);
        imprimeTablero(tablero, numFilas, numColumnas);
        g++;
    }
}
int main() {
    // srand(time(NULL));
    // Posibles valores de una celda del tablero:
    // false: Vacía
    // true: Célula viva

    // Declara matriz de MAX_FILAS x MAX_COLUMNAS
    // e inicializa como celdas vacías
    bool tablero[MAX_FILAS][MAX_COLUMNAS] = {false};

    // Declara variables para datos introducidos por usuario
    // son declarados como int, ya que puede introducir números negativos
    // que son ignorados y debe vovler a salir el mensaje pidiendo el dato
    int numFilas, numColumnas, generaciones;

    // Pide datos al usuario
    pideDatos(numFilas, numColumnas, generaciones);

    // Inicializa el tablero 
    iniciaTablero(tablero, numFilas, numColumnas);

    // Imprime la generación 0
    borrarPantalla();
    cout << "Generación 0" << endl;
    imprimeTablero(tablero, numFilas, numColumnas);
    
    // Simula el número de generaciones introducido o hasta que se extigue la colonia
    simulaGeneraciones(tablero, numFilas, numColumnas, generaciones);

    // Almaceno el total de vivas después de la última simulación
    unsigned vivasResultantes = cuentaVivas(tablero, numFilas, numColumnas);

    if (vivasResultantes) {
        // La simulación ha terminado y queda alguna célula viva
        cout << "Sobreviven " << vivasResultantes << " células" << endl;
        // Para mostrar el número de vecinas vivas en cada celda:
        // retirar comentarios hasta la línea 304
                    // unsigned resultado[numFilas][numColumnas] = {0};
                    // for (unsigned i = 0; i < unsigned(numFilas); i++){
                    //     for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
                    //         resultado[i][j]= vecinas(tablero, numFilas, numColumnas, i, j);
                    //     }
                    // }
                    // for (unsigned i = 0; i < unsigned(numFilas); i++){
                    //     for (unsigned j = 0; j < unsigned(numColumnas); j++) { 
                    //         cout << setw(2) << resultado[i][j];
                    //     }
                    //     cout << endl;
                    // }
    } else {
        // No ha sobrevivido ninguna célula
        cout << "Colonia Extinguida" << endl;
    }
    return 0;
}