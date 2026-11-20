/**
 * Proyecto Odisea Espacial clase ASTEROIDE
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1.1
 *
 * La clase ASTEROIDE representa un objeto que tiene el propósito de dañar
 * a la NAVE a través de colisionar con ella.
 */
#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include <cstdlib> // rand
#include "ENTIDAD.h" // Clase madre
#include "NAVE.h"
#include "CONSOLE.h" // Clase auxiliar

//Declaración de clase ASTEROIDE que hereda de ENTIDAD
class ASTEROIDE : public ENTIDAD{
    public:
        ASTEROIDE(int, int);
        void pintar() override;
        void borrar() override;
        void mover() override;
        void choque(NAVE&);
};

/**
 * Constructor
 *
 * @param x1 posición inicial en x, y1 posición inicial en y
 */
ASTEROIDE::ASTEROIDE(int x1, int y1): ENTIDAD(x1, y1) {}

/** pintar imprime el ASTEROIDE en consola. */
void ASTEROIDE::pintar(){
    gotoxy(x, y); printf("O");
}

/** borrar imprime un espacio en las coordenadas del ASTEROIDE. */
void ASTEROIDE::borrar(){
    gotoxy(x, y); printf(" ");
}

/**
 * mover baja el ASTEROIDE una posición; si sale de la pantalla lo
 * reposiciona arriba en una x aleatoria.
 */
void ASTEROIDE::mover(){
    borrar();
    y++;
    if(y > 24){
        x = rand() % 71 + 4;
        y = 4;
    }
    pintar();
}

/**
 * choque verifica si el ASTEROIDE coincide con la NAVE. Si es así, la
 * NAVE recibe daño y el asteroide reaparece arriba.
 */
void ASTEROIDE::choque(NAVE& N){
    if(x >= N.getX() && x < N.getX() + NAVE::ANCHO &&
       y >= N.getY() && y < N.getY() + NAVE::ALTO){
        N.recibirDanio();
        N.borrar();
        N.pintar();
        N.pintarSalud();
        x = rand() % 71 + 4;
        y = 4;
    }
}

#endif
