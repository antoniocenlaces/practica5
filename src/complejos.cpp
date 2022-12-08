/******************************************************************************\
 * Programación 1. Práctica 5
 * Autor: Antonio José González Almela
 * Ultima revisión: 22/11/2022
 * Resumen: Fichero de implementación del módulo principal del programa que 
 *          trabaja con números complejos.
 * Nota: El código de este programa no está repartido en varios módulos, por lo
 *       que se puede utilizar la extensión Code Runner de VSC para ejecutarlo.
 *       No obstante, se ha configurado el fichero «Makefile» para poder 
 *       compilarlo y se han definido tareas de VSC para compilarlo, ejecutarlo 
 *       y depurarlo.
 *       Para compilarlo, se puede ejecutar el comando
 *           make complejos
 *       o, en Windows,
 *           mingw32-make complejos
 *       o ejecutar la tarea "Compilar «complejos»" de VSC
 * 
 *       Para ejecutarlo, una vez compilado, se puede ejecutar el comando
 *           bin/complejos
 *       o, en Windows,
 *           bin\complejos.exe
 *       o ejecutar la tarea "Ejecutar «complejos»" de VSC
 *       o compilarlo y ejecutarlo con la extensión Code Runner (Ctrl+Alt+N).
\******************************************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
// #include <ctime>
// <ctime> debe usarse para mejorar la aleatoriedad de srand
#include <cstdlib>
#include <iomanip>

using namespace std;

const unsigned NUM_COMPLEJOS = 5;
const unsigned PRECISON = 2;

struct Complejo { 
    double a, b;
};
/* Pre: x e y son dos números reales cumpliendo x < y
*  Post: Genera un número real R aleatorio cumpiendo x <= R <= y
*/
double aleatorio(const double x, const double y) {
    double generado = (double(rand()) / RAND_MAX) * (y - x) + x;
    return generado;
}

/* Pre: 
*  Post: Pide dos números reales (x e y) al usuario. Devuelve por referencia
*  los números leidos si cumplen que x < y
*/
void pideDatos(double& x, double& y) {
    do {
        cout << "Introduce los límites del intervalo (x < y): ";
        cin >> x >> y;
    } while(x >= y);
}

/* Pre: 
*  Post: Genera aleatorimente los componentes de un vector de complejos con
*  NUM_COMPLEJOS elementos y cumpliendo que tanto su parte real como imaginaria
*  están entre x e y, con x < y
*/
void generaVectorAleatorio(const double x, const double y, Complejo vectorComplejo[NUM_COMPLEJOS]) {
    for (unsigned i = 0; i < NUM_COMPLEJOS; i++) {
        vectorComplejo[i] = { aleatorio(x, y), aleatorio(x, y)};
    }
}

/* Pre: 
*  Post: Escribe por pantalla un núemro complejo
*/
void imprimeComplejo(const Complejo numero) {
     cout << fixed << setprecision(PRECISON) << numero.a 
          << showpos << numero.b << "i" << noshowpos;
          // (numero.b >= 0 ? "+" : "")
}

/* Pre: 
*  Post: Escribe por pantalla todos los componentes de un vector
*  de complejos con NUM_COMPLEJOS elementos
*/
void imprimeVector(const Complejo vectorComplejo[NUM_COMPLEJOS]) {
     cout << "Números complejos generados: " << endl;
    for (unsigned i = 0; i < NUM_COMPLEJOS - 1; i++) {
        imprimeComplejo(vectorComplejo[i]);
        cout << ", ";
    }
    imprimeComplejo(vectorComplejo[NUM_COMPLEJOS - 1]);
    cout << endl;
}

/* Pre: Recibe un número de tipo Complejo
*  Post: Calcula el módulo del número complejo representado
*/
double modulo(const Complejo numero) {
    return sqrt(pow(numero.a, 2) + pow(numero.b, 2));
}

/* Pre: Recibe un vector de tipo Complejo con al menos un componente
*  Post: Encuentra la posición en vectorComplejo del elemento
*  con mayor módulo
*/
unsigned posMaxModulo(const Complejo vectorComplejo[NUM_COMPLEJOS]) {
    unsigned posicionMax = 0;
    double max = modulo(vectorComplejo[0]);
    for (unsigned i = 1; i < NUM_COMPLEJOS; i++) {
        double moduloActual = modulo(vectorComplejo[i]);
        if (moduloActual > max) {
            posicionMax = i;
            max=moduloActual;
        }
    }
    return posicionMax;
}

/* Pre: Recibe un vector de tipo Complejo con al menos un componente
*  Post: Encuentra la posición en vectorComplejo del elemento
*  con menor módulo
*/
unsigned posMinModulo(const Complejo vectorComplejo[NUM_COMPLEJOS]) {
    unsigned posicionMin = 0;
    double min = modulo(vectorComplejo[0]);
    for (unsigned i = 1; i < NUM_COMPLEJOS; i++) {
        double moduloActual = modulo(vectorComplejo[i]);
        if (moduloActual < min) {
            posicionMin = i;
            min=moduloActual;
        }
    }
    return posicionMin;
}

/* Pre: Recibe un vector de tipo Complejo con al menos un componente
*  Post: Calcula y devuelve como Complejo la suma de todos los
*  componentes del vector recibido
*/
Complejo suma(const Complejo vectorComplejo[NUM_COMPLEJOS]) {
    double sumaA, sumaB = 0;
    
    for (unsigned i = 0; i < NUM_COMPLEJOS; i++) {
        sumaA += vectorComplejo[i].a;
        sumaB += vectorComplejo[i].b;
    }
    return {sumaA, sumaB};
}

int main() {
    // Para mejorar el rendimiento del algoritmo srand quitar comentario
    // a la línea a continuación, además de #include <ctime>
    // srand(time(NULL));

    double x, y;
    Complejo vectorComplejo[NUM_COMPLEJOS];

    pideDatos(x, y);
    cout << endl;

    generaVectorAleatorio(x, y, vectorComplejo);

    imprimeVector(vectorComplejo);
    cout << endl;

    cout << "Números complejos de mayor y menor módulo, respectivamente: " << endl;
    imprimeComplejo( vectorComplejo[ posMaxModulo(vectorComplejo) ] );
    cout << " y ";
    imprimeComplejo( vectorComplejo[ posMinModulo(vectorComplejo) ] );
    cout << endl << endl;

    cout << "Suma:" << endl;
    imprimeComplejo(suma(vectorComplejo));  
    cout << endl;

    return 0;
}
