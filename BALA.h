/**
 * Proyecto Odisea Espacial clase BALA
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1.1
 *
 * La clase BALA representa el proyectil que utilizan la NAVE y el ENEMIGO
 * para hacer daño o destruir asteroides.
 */

#ifndef BALA_H
#define BALA_H

#include "ENTIDAD.h"
#include "CONSOLE.h" // Clase auxiliar

//Declaración de clase BALA que hereda de ENTIDAD
class BALA : public ENTIDAD{
    private:
        int direccion; // Define hacia dónde se mueve la BALA (<0 arriba, >0 abajo)
    public:
        BALA(int, int, int);
        bool fuera();
        // Métodos sobreescritos de la clase ENTIDAD
        void mover() override;
        void pintar() override;
        void borrar() override;
};

/**
 * Constructor
 *
 * @param x1 posición inicial en x, y1 posición inicial en y,
 * direccion1 hacia dónde se moverá la bala
 */
BALA::BALA(int x1, int y1, int direccion1): ENTIDAD(x1, y1), direccion(direccion1) {}

/** pintar imprime la BALA en consola. */
void BALA::pintar(){
    gotoxy(x, y); printf("*");
}

/** borrar imprime un espacio en las coordenadas de la BALA. */
void BALA::borrar(){
    gotoxy(x, y); printf(" ");
}

/** mover desplaza la BALA hacia arriba o abajo según su dirección. */
void BALA::mover(){
    borrar();
    if(direccion < 0){
        y--;
    }
    else if(direccion > 0){
        y++;
    }
    pintar();
}

/** fuera detecta si la BALA sale de los límites del área de juego. */
bool BALA::fuera(){
    if(direccion < 0 && y <= 4)
        return true;

    if(direccion > 0 && y >= 24)
        return true;

    return false;
}

#endif
