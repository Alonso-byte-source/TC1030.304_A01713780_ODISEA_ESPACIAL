/**
 * Proyecto Odisea Espacial clase NAVE
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1
 * 
 * La clase NAVE representa el objeto que el usuario controla, esta clase
 * hereda métodos y atributos de la clase abstracta ENTIDAD e interactúa 
 * con las demás clases a traves de la clase JUEGO 
 */

#ifndef NAVE_H
#define NAVE_H

#include "ENTIDAD.h"
#include "CONSOLE.h" // Clase auxiliar

//Declaración de clase NAVE que hereda de ENTIDAD
class NAVE : public ENTIDAD{
    // Declaración de variables privadas de instacia
    private:
        int corazones, vida;
        char boton; // Variable para guardar la tecla pulsada
    // Declaración de métodos que va a tener el objeto
    public: 
        NAVE(int, int, int, int);
        void recibirDanio();
        void pintarSalud();
        void morir();
        int getVida();
        void setTecla(char);
        // Métodos sobreescritos de la clase ENTIDAD
        void pintar() override;
        void mover() override;
        void borrar() override;
};

/** 
* Constructor donde recibe valores para llenar las variables de instacia
* 
* @param int x1: posicón en x inicial de la nave, int y1: posición inicial en y 
* de la nave, int corazones1: cantidad de corazones por vida, int vida1: cantidad de vidas
* @return
*/
NAVE::NAVE(int x1, int y1, int corazones1, int vida1): ENTIDAD(x1, y1), corazones(corazones1), vida(vida1), boton(' ') {}

/**
 * recibirDanio disminuye los corazones de la nave.
 *
 * @param
 * @return
 */
void NAVE::recibirDanio(){
    corazones --;
}

/**
 * setTecla recibe y guarda una tecla.
 * 
 * Esta función recibe una tecla detectada en la clase JUEGO, la cual es 
 * utilizada para mover el objeto NAVE en la pantalla 
 * 
 * @param char tecla
 * @return
 */
void NAVE::setTecla(char tecla){
    boton = tecla;
}

/**
 * mover mueve el objeto NAVE
 * 
 * Esta función utiliza la tecla guardada en la variable boton para mover el objeto
 * NAVE en las distitas direcciones del plano 2D, restringiendo los moviemientos de
 * acuerdo con las dimesiones de la pantalla del juego
 * 
 * @param 
 * @return
 */
void NAVE::mover(){
    borrar();
    if(boton == 'a' && x > 3) x--;
    if(boton == 'd' && x+6 < 77) x++;
    if(boton == 'w' && y > 4) y--;
    if(boton == 's' && y+3 < 25) y++;
    pintar();
}

/**
 * pintar imprime el objeto NAVE en consola
 * 
 * Esta función pinta el objeto NAVE con caracteres del teclado, se puede modificar
 * con la forma que mejor te guste para el objeto NAVE
 * 
 * @param 
 * @return
 */
void NAVE::pintar(){
    gotoxy(x, y);   printf("  ^");
    gotoxy(x, y+1); printf(" <0>");
    gotoxy(x, y+2); printf("A^ ^A");
}

/**
 * borrar borra el objeto NAVE
 * 
 * Esta función imprime espacios en blanco en las coordenadas del objeto NAVE
 * para borrarlo
 * 
 * @param 
 * @return
 */
void NAVE::borrar(){
    gotoxy(x, y);   printf("       ");
    gotoxy(x, y+1); printf("       ");
    gotoxy(x, y+2); printf("       ");
}

void NAVE::pintarSalud(){
    gotoxy(50,2); printf("VIDAS %d", vida);
    gotoxy(64, 2); printf("SALUD");
    gotoxy(70, 2); printf("      ");
    for(int i = 0; i < corazones; i++){
        gotoxy(70+i, 2); printf("*");
    }
}

/**
 * morir imprime una animación de muerte
 * 
 * Esta función imprime una simulación de muerte cada que el objeto NAVE pierde
 * todos los corazones de una vida
 * @param 
 * @return
 */
void NAVE::morir(){
    if(corazones == 0){
        borrar();
        gotoxy(x, y);   printf("   **   ");
        gotoxy(x, y+1); printf("  ****  ");
        gotoxy(x, y+2); printf("   **   ");
        Sleep(200);

        borrar();
        gotoxy(x, y);   printf(" * ** * ");
        gotoxy(x, y+1); printf("  ****  ");
        gotoxy(x, y+2); printf(" * ** * ");
        Sleep(200);

        borrar();
        vida--;
        corazones = 3;
        pintarSalud();
        pintar();
    }
}

/**
 * getVida regresa la vida del objeto NAVE
 * 
 * @param 
 * @return
 */
int NAVE::getVida(){
    return vida;
}
#endif