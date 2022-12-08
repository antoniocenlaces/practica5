/******************************************************************************\
 * Programación 1. Práctica 5
 * Autores: Miguel Ángel Latre y Rafael Tolosana
 * Modificado por: Antonio José González Almela
 * Ultima revisión: 21 de noviembre de 2020
 * Resumen: Fichero de implementación del módulo principal del programa que 
 *          manipula imágenes BMP en la 5ª práctica.
 * Nota: El código de este programa está repartido en varios módulos.
 *       Para compilarlo, hay que ejecutar el comando
 *           make bmp
 *       o, en Windows,
 *           mingw32-make bmp
 *       o ejecutar la tarea "Compilar «bmp»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/bmp
 *       o, en Windows,
 *           bin\bmp.exe
 *       o ejecutar la tarea "Ejecutar «bmp»" de VSC.
\******************************************************************************/
#include <iostream>
#include <string>
#include "imagen-bmp.hpp"
using namespace std;

/* 
 * Programa de ejemplo que lee la imagen «datos/prog1.bmp» y genera la imagen
 * «datos/imagen-generada.bmp». Compílalo y ejecútalo una vez para comprobar que
 * genera la imagen «datos/imagen-generada.bmp» y que esta se puede visualizar
 * en Visual Studio Code.
 * Después modifica la función «main» (incluyendo esta especificación) para
 * resolver el problema solicitado en la tarea 2 de la práctica.
 */
int main() {
    static Imagen img;
    string nombreFichero = "datos/prog1.bmp";
    /* 
     * Deberás completar el código aquí para pedir el nombre del fichero y
     * completar la interacción con el usuario.
     */
   
    if (leerImagen(nombreFichero, img)) {
        /*
         * Aquí irá el código que manipule las imágenes según lo solicitado en
         * el enunciado de la práctica. Lo ideal es que haya invocaciones a
         * funciones que realicen esas manipulaciones.
         */
        guardarImagen("datos/imagen-generada.bmp", img);
        return 0;
    }
    else {
        return 1;
    }
}