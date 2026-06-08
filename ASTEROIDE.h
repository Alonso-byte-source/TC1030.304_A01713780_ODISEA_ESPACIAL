/**
 * Proyecto Odisea Espacial clase ASTEROIDE
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1
 * 
 * La clase ASTEROIDE representa un objeto que tiene el propósito de dañar al objeto
 * NAVE  a través de colisionar con él 
 */
#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include "ENTIDAD.h" // Clase madre
#include "NAVE.h" // Recibe 
#include "CONSOLE.h" // Clase auxiliar

//Declaración de clase ASTEROIDE que hereda de ENTIDAD
class ASTEROIDE : public ENTIDAD{
    // Declaración de métodos que va a tener el objeto
    public:
        ASTEROIDE(int, int);
        void pintar() override;
        void borrar() override;
        void mover() override;
        void choque(NAVE&);
};

/** 
* Constructor donde recibe valores para llenar las variables de instacia
* 
* @param int x1: posicón en x inicial deL asteoirde int y1: posición inicial en y 
* del asteroide
* @return
*/
ASTEROIDE::ASTEROIDE(int x1, int y1): ENTIDAD(x1, y1) {}

/**
 * pintar imprime el objeto asteroide en consola
 * 
 * Esta función pinta el objeto ASTEROIDE con caracteres del teclado, se puede modificar
 * con la forma que mejor te guste para el objeto ASTEORIDE
 * 
 * @param 
 * @return
 */
void ASTEROIDE::pintar(){
    gotoxy(x, y); printf("O");
}

/**
 * borrar borra el objeto ASTEROIDE
 * 
 * Esta función imprime espacios en blanco en las coordenadas del objeto ASTEROIDE
 * para borrarlo
 * 
 * @param 
 * @return
 */
void ASTEROIDE::borrar(){
    gotoxy(x, y); printf(" ");
}

/**
 * mover mueve el objeto ASTEROIDE
 * 
 * Esta función mueve el objeto asteroide hacia abajo, si el asteroide sale de
 * los límites de la pantalla lo posiciona de nuevo hasta arriba en una posición random 
 * en x
 * 
 * @param 
 * @return
 */
void ASTEROIDE::mover(){
    borrar();
    y++;
    // Se verifica si el asteroide sobrepaso el límite de la pantalla
    if(y > 24){
        x = rand() % 71 + 4;
        y = 4;
    }
    pintar();
}

/**
 * choque verfica si la posición del asteroide y la nave coinciden
 * 
 * Esta función recibe la referencia de un objeto NAVE para verificar si las coordenadas 
 * coinciden para afectar a la nave con la colisión
 * 
 * @param 
 * @return
 */
void ASTEROIDE::choque(NAVE& N){
    if(x >= N.getX() && x < N.getX()+6 && y >= N.getY() && y <= N.getY()+2){
        N.recibirDanio();
        N.borrar();
        N.pintar();
        N.pintarSalud();
        x = rand() % 71 + 4;
        y = 4;
    }
}

#endif