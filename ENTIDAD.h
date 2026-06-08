/**
 * Proyecto Odisea Espacial clase ENTIDAD
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1
 * 
 * La clase ENTIDAD funciona como una clae abstracta, de la cual heredan
 * atributos y métodos las clases NAVE, ENEMIGO, ASTEROIDE y BALA 
 */

#ifndef ENTIDAD_H
#define ENTIDAD_H

//Declaración de clase ENTIDAD que es abstracta
class ENTIDAD{
    //Declaración de variables de instancia
    protected:
        int x, y;
    //Declaración de los métodos que va a tener el objeto
    public:
        ENTIDAD(int, int); //Constructor
        int getX();
        int getY();
        //Métodos abstractos que serán sobreescritos 
        virtual void mover() = 0;
        virtual void pintar() = 0;
        virtual void borrar() = 0;
        virtual ~ENTIDAD() = default;//Destructor por default
};

/** 
* Constructor de la clase abstracta
* 
* @param string x1: posicón en x inicial de la nave, y1: posición inicial en y 
* de la nave
* @return
*/
ENTIDAD::ENTIDAD(int x1, int y1): x(x1), y(y1) {}

/**
 * getX regresa la posición en x de las entidades
 *
 *
 * @param
 * @return int con la posición en x
 */
int ENTIDAD::getX(){
    return x;
}

/**
 * getY regresa la posición en y de las entidades
 *
 *
 * @param
 * @return int con la posición en y
 */
int ENTIDAD::getY(){
    return y;
}

#endif