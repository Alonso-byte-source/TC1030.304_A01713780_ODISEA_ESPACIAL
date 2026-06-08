/**
 * Proyecto Odisea Espacial clase ENEMIGO
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1
 * 
 * La clase ENEMIGO representa un objeto que tiene el propósito de dañar al objeto
 * NAVE controlado por el usuario, desde que aparece puede acceder a las coordenadas de
 * la NAVE para atacar 
 */
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "ENTIDAD.h" // Clase madre
#include "NAVE.h" // La clase ENEMIGo recibe la referencia de un objeto tipo NAVE
#include "CONSOLE.h" // Clase auxiliar

//Declaración de clase ENEMIGO que hereda de ENTIDAD
class ENEMIGO : public ENTIDAD{
    // Declaración de variables privadas de instacia
    private:
        int vida,cooldown;
        bool disparando, vivo;
        NAVE* objetivo; // Objetivo es una variable de tipo puntero a NAVE
    // Declaración de métodos que va a tener el objeto
    public:
        ENEMIGO(int, int, int, bool);
        void recibirDanio();
        bool puedeDisparar();
        void morir();
        bool estaVivo();
        int getVida();
        void setObjetivo(NAVE* n); // Función que recibe la dirección de memoria del objeto NAVE
        // Métodos sobreescritos de la clase ENTIDAD
        void mover() override;
        void pintar() override;
        void borrar() override;
};

/** 
* Constructor donde recibe valores para llenar las variables de instacia
* 
* @param int x1: posicón en x inicial del enemigo, int y1: posición inicial en y 
* del enemigo, int vida1: cantidad de vidas del enemigo, bool vivo1: estado del enemigo
* @return
*/
ENEMIGO::ENEMIGO(int x1, int y1, int vida1, bool vivo1)
    : ENTIDAD(x1, y1), vida(vida1), vivo(vivo1), objetivo(nullptr), cooldown(0), disparando(false){}


/**
 * mover mueve el objeto ENEMIGO
 * 
 * Esta función utiliza la variable "objetivo" que guarda un puntero al 
 * objeto NAVE para ver las coordenas de la NAVE y poder moverse a esa posición
 * 
 * @param 
 * @return
 */
void ENEMIGO::mover(){
    if(!objetivo) return; //Verifica si la variable "objetivo" esta vacía
    borrar();
    // Se verifica si el enemigo esta disparando
    if(disparando){
        cooldown++;//Incrementa el contador
        if(cooldown >= 30){ 
            disparando = false; // Cambia el estado de disparando si el contador llega a 30
            cooldown = 0; // Reinicia el contador
        }
    }
    // Si no esta disparando el ENEMIGO se mueve a la posición en x de la NAVE
    else{
        if(x < objetivo->getX()){
            x++;
        }
        else if(x > objetivo->getX()){
            x--;
        }
        // Si la distancia a la NAVE es menor o igual a 1 el estado del enemigo cambia e inicia el contador cooldown de nuevo
        if(abs(x - objetivo->getX()) <= 1){
            disparando = true;
        }
    }
    pintar();
}

/**
 * pintar imprime el objeto enemigo en consola
 * 
 * Esta función pinta el objeto ENEMIGO con caracteres del teclado, se puede modificar
 * con la forma que mejor te guste para el objeto ENEMIGO
 * 
 * @param 
 * @return
 */
void ENEMIGO::pintar(){
    gotoxy(x, y);   printf(" <O>");
    gotoxy(x, y+1); printf("  V");
}

/**
 * borrar borra el objeto ENEMIGO
 * 
 * Esta función imprime espacios en blanco en las coordenadas del objeto NAVE
 * para borrarlo
 * 
 * @param 
 * @return
 */
void ENEMIGO::borrar(){
    gotoxy(x, y);   printf("        ");
    gotoxy(x, y+1); printf("        ");
}

/**
 * recibirDanio disminuye las vidas del ENEMIGO.
 *
 * @param
 * @return
 */
void ENEMIGO::recibirDanio(){
    vida--;
}

/**
 * puedeDisparar indica si el enemigo puede disparar
 *
 * @param
 * @return bool
 */
bool ENEMIGO::puedeDisparar(){
    return cooldown == 1 && disparando;
}

/**
 * morir imprime una animación de muerte
 * 
 * Esta función imprime una simulación de muerte cada que el objeto ENEMIGO pierde
 * todas las vidas
 * @param 
 * @return
 */
void ENEMIGO::morir(){
    borrar();
    gotoxy(x, y);   printf("***");
    gotoxy(x, y+1); printf("***");
    Sleep(200);

    borrar();
    gotoxy(x, y);   printf("* ** *");
    gotoxy(x, y+1); printf("* ** *");
    SleepMs(200);

    borrar();
    vivo = false;
}


bool ENEMIGO::estaVivo(){
    return vivo;
}

/**
 * getVida regresa la vida del objeto ENEMIGO
 * 
 * @param 
 * @return int vida
 */
int ENEMIGO::getVida(){
    return vida;
}

/**
 * setObjetivo recibe un puntero hacia el objeto NAVE
 * 
 * @param NAVE* n
 * @return
 */
void ENEMIGO::setObjetivo(NAVE* n){
    objetivo = n;
}

#endif