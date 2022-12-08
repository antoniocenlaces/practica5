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

/*
 * Pre:  ---
 * Post: Tras ejecutar este procedimiento, negativiza la imagen 
 *       guardada en la variable img de tipo Imagen.
 */
void negativiza(Imagen& img) {
     for (unsigned i = 0; i < img.alto; i++) {
            for (unsigned j = 0; j < img.ancho; j++) {
                img.pixels[i][j].rojo = 255 - img.pixels[i][j].rojo;
                img.pixels[i][j].verde = 255 - img.pixels[i][j].verde;
                img.pixels[i][j].azul = 255 - img.pixels[i][j].azul;
            }
        }
}

/*
 * Pre:  ---
 * Post: Tras ejecutar este procedimiento, rota 180º la imagen 
 *       guardada en la variable img de tipo Imagen.
 */
void rota(Imagen& img) {
    // Uso copiaPixel para guardar el pixel original que voy a cambiar
    Pixel copiaPixel;
    
    // El bucle recorre la imagen, en altura, hasta la línea media
    // Funciona por ser alto un múltiplo de 4 
    for (unsigned i = 0; i < img.alto / 2; i++) {
        for (unsigned j = 0; j < img.ancho; j++) {
            // Almaceno el pixel que voy a cambiar
            copiaPixel = img.pixels[i][j];
            // Cambio el pixel de la posición donde estoy por el rotado 180º
            img.pixels[i][j] = img.pixels[img.alto - 1 - i][img.ancho - 1 - j];
            // En el rotado almaceno la posición donde estoy
            img.pixels[img.alto - 1 - i][img.ancho - 1 - j] = copiaPixel;
        }
    }
    
}

int main() {
    static Imagen img;
    string nombreFichero = "datos/prog1.bmp";
    /* 
     * Deberás completar el código aquí para pedir el nombre del fichero y
     * completar la interacción con el usuario.
     */
    string ficheroLectura;
    cout << "Dime el nombre del fichero de imagen (.bmp) a leer: ";
    cin >> ficheroLectura;
    char accion;
    cout << "¿Que acción deseas realizar sobre el fichero de imagen?" << endl;
    cout << "\"N\" para Negativizar; \"R\" para Girar la imagen 180º: ";
    do {
        cin >> accion;
        accion = toupper(accion);
    } while (accion != 'N' && accion !='R');

    string ficheroEscritura;
    cout << "Dime el nombre del fichero de imagen (.bmp) donde escribir: ";
    cin >> ficheroEscritura;

    if (leerImagen(ficheroLectura, img)) {
        /*
         * Aquí irá el código que manipule las imágenes según lo solicitado en
         * el enunciado de la práctica. Lo ideal es que haya invocaciones a
         * funciones que realicen esas manipulaciones.
         */
        switch (accion) {
            case 'N':
                negativiza(img);
                break;
            case 'R':
                rota(img);
                break;
        } 
        guardarImagen(ficheroEscritura, img);
        return 0;
    }
    else {
        return 1;
    }
}