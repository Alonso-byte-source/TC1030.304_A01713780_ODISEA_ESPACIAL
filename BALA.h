/**
 * Proyecto Odisea Espacial clase BALA
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1
 * 
 * La clase NAVE representa el objeto que utiliza el objeto NAVE y el objeto ENEMIGO para
 * hacer daño o destruir asteroides 
 */

#ifndef BALA_H
#define BALA_H

#include "ENTIDAD.h"
#include "CONSOLE.h" // Clase auxiliar

//Declaración de clase BALA que hereda de ENTIDAD
class BALA : public ENTIDAD{
    // Declaración de variables privadas de instacia
    private:
        int direccion; // Variable para definir hacia donde se mueve el objeto BALA
    // Declaración de métodos que va a tener el objeto
    public:
        BALA(int, int, int);
        bool fuera();
        // Métodos sobreescritos de la clase ENTIDAD
        void mover() override;
        void pintar() override;
        void borrar() override;
};

/** 
* Constructor donde recibe valores para llenar las variables de instacia
* 
* @param int x1: posicón en x inicial de la bala, int y1: posición inicial en y 
* de la bala, int direccion1: direccion hacia donde se movera la bala 
* @return
*/
BALA::BALA(int x1, int y1, int direccion1): ENTIDAD(x1, y1), direccion(direccion1) {} 

/**
 * pintar imprime el objeto BALA en consola
 * 
 * Esta función pinta el objeto BALA con caracteres del teclado, se puede modificar
 * con la forma que mejor te guste para el objeto BALA
 * 
 * @param 
 * @return
 */
void BALA::pintar(){
    gotoxy(x, y); printf("*");
}

/**
 * borrar borra el objeto BALA
 * 
 * Esta función imprime espacios en blanco en las coordenadas del objeto BAL
 * para borrarlo
 * 
 * @param 
 * @return
 */
void BALA::borrar(){
    gotoxy(x, y); printf(" ");
}

/**
 * mover mueve el objeto NAVE
 * 
 * Esta función utiliza la dirección recibida en el constructorpara definir si el
 * objeto BALA se mueve hacia arriba o hacia abajo
 * 
 * @param 
 * @return
 */
void BALA::mover(){
    borrar();
    if(direccion < 0){
        y--;
    }
    else if (direccion > 0)
    {
        y++;
    }
    pintar();
}

/**
 * fuera detecta si el objeto BALA sale de los límites de la pantalla del juego. 
 * 
 * @param 
 * @return
 */
bool BALA::fuera(){
    if(direccion < 0 && y <= 4)
        return true;

    if(direccion > 0 && y >= 24)
        return true;

    return false;
}

#endif