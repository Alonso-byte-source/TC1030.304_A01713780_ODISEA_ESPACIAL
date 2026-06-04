/**
 * Proyecto Odisea Espacial clase Juego
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1
 * 
 * La clase JUEGO administra la lógica principal del videojuego.
 *
 * Coordina la interacción entre la nave del jugador, el enemigo,
 * los asteroides y las balas. Controla la entrada del usuario,
 * la actualización de estados, las colisiones, la puntuación
 * y el ciclo principal de ejecución de la partida.
 */

#ifndef JUEGO_H
#define JUEGO_H

#include <list>
#include<stdlib.h>
#include <unistd.h>


// Bibilotecas de objetos a usar
#include "ENTIDAD.h"
#include "NAVE.h"
#include "ENEMIGO.h"
#include "BALA.h"
#include "ASTEROIDE.h"
#include "CONSOLE.h"

using namespace std;

class JUEGO{ 
    // Declaración de variables métodos privados de instacia
    private:
        int cont; // Contador para controlar la aparición del enemigo
        int puntos;
        bool gameOver;
        NAVE N; // Se crea un objeto NAVE
        ENEMIGO E; // Se crea un onjeto ENEMIGO
        list<ASTEROIDE*> A; // Lista con punteros a objetos ASTEROIDE
        list<BALA*> B; // Lista con punteros a objetos BALA (para el jugador)
        list<BALA*> BE; // Lista con punteros a objetos ASTEROIDE (para el enemigo)
        list<ENTIDAD*> entidades; // Lista con punteros a objetos de la clase abstracta ENTIDAD
        void Input();
        void Update();
        void Render();
        void actualizarBalasJugador();
        void actualizarBalasEnemigo(); 
        void actualizarAsteroides();
        void colisiones();
    // Declaración de constructor y destructor por default, así como métodos públicos
    public:
        JUEGO();
        ~JUEGO();
        void iniciar();
};

/**
 * JUEGO crea una nueva instancia del juego.
 *
 * Inicializa la nave del jugador, el enemigo, un contador, la puntuación y el estado
 * de la partida. También establece la nave como objetivo del enemigo.
 *
 * @param
 * @return
 */

JUEGO::JUEGO() : N(37,20,3,3), E(37, 4, 3, 1), cont(0), puntos(0), gameOver(false){
    E.setObjetivo(&N);
    entidades.push_back(&N);
    entidades.push_back(&E);
}

/**
 * ~JUEGO libera la memoria dinámica utilizada.
 *
 * Recorre las listas de asteroides y balas eliminando los objetos
 * almacenados dinámicamente para evitar fugas de memoria.
 *
 * @param
 * @return
 */

JUEGO::~JUEGO(){
    for(auto a : A){
        delete a;
    }
    for(auto b : B){
        delete b;
    }
    for(auto be : BE){
        delete be;
    }
    A.clear();
    B.clear();
    BE.clear();
}



/**
 * iniciar ejecuta el ciclo principal del juego.
 *
 * Configura la consola, dibuja los límites, genera los asteroides
 * iniciales y mantiene el ciclo principal mientras la partida
 * continúe activa.
 *
 * @param
 * @return
 */

void JUEGO::iniciar(){
    OcultarCursor();
    pintarLimites();
    N.pintar();

    for(int i=0; i<4; i++){
        A.push_back(new ASTEROIDE(rand()%75 +3, rand()%5 + 4));
    }

    while(!gameOver){
        Input();
        Update();
        Render();
        SleepMs(30);
    }
}


/**
 * Input procesa la entrada del usuario.
 *
 * Detecta las teclas presionadas por el jugador, actualiza el
 * movimiento de la nave y genera balas cuando se realiza un disparo.
 *
 * @param
 * @return
 */

void JUEGO::Input(){
    if(!kbhit()) return;
    char tecla = getch();
    if(tecla == ' '){
        B.push_back(new BALA(N.getX() + 2, N.getY() - 1, -1));
    }
    N.setTecla(tecla);
    N.mover();
}

/**
 * Update actualiza el estado del juego.
 *
 * Coordina la actualización de balas, asteroides, colisiones,
 * comportamiento del enemigo y verifica si el jugador ha perdido
 * todas sus vidas.
 *
 * @param
 * @return
 */

void JUEGO::Update(){
    actualizarBalasJugador();
    actualizarBalasEnemigo();
    actualizarAsteroides();
    colisiones();

    // Si se consiguen 5 puntos aparece un enemigo
    if(cont >= 20 && E.estaVivo()){
        E.mover();
        if(E.puedeDisparar()){
            BE.push_back(new BALA(E.getX()+1, E.getY()+2, 1));
        }
        actualizarBalasEnemigo();
    }

    N.morir();
    if(N.getVida() <= 0){
        gameOver = true;
    }
}

/**
 * Render dibuja los elementos visibles del juego.
 *
 * Actualiza la información mostrada en pantalla, incluyendo
 * la puntuación, la nave, la barra de salud, el enemigo y
 * los asteroides presentes en la partida.
 *
 * @param
 * @return
 */

void JUEGO::Render(){

    gotoxy(4,2);
    printf("Puntos %d ", puntos);

    for(auto e : entidades){

        if(e == &E){
            if(cont >= 20 && E.estaVivo())
                e->pintar();
        }
        else{
            e->pintar();
        }
    }

    N.pintarSalud();

    for(auto a : A){
        ENTIDAD* e = a;
        e->pintar();
    }
}

/**
 * actualizarAsteroides actualiza los asteroides activos.
 *
 * Recorre todos los asteroides, actualiza su posición y verifica
 * posibles colisiones con la nave del jugador.
 *
 * @param
 * @return
 */

void JUEGO::actualizarAsteroides(){
    for(auto it = A.begin(); it != A.end(); ){
        (*it)->mover();
        (*it)->choque(N);

        if(false){ 
            delete *it;
            it = A.erase(it);   } else {
            it++;
        }
    }
}

/**
 * actualizarBalasJugador mueve las balas del jugador.
 *
 * Recorre todas las balas disparadas por la nave, actualiza
 * su posición y elimina aquellas que salen de los límites
 * del área de juego.
 *
 * @param
 * @return
 */

void JUEGO::actualizarBalasJugador(){

    for(auto it = B.begin(); it != B.end(); ){

        (*it)->mover();

        if((*it)->fuera()){
            gotoxy((*it)->getX(), (*it)->getY()); printf(" ");
            delete *it;
            it = B.erase(it);
        }
        else{
            it++;
        }
    }
}

/**
 * actualizarBalasEnemigo mueve las balas enemigas.
 *
 * Actualiza la posición de cada bala disparada por el enemigo,
 * detecta impactos contra la nave y elimina las balas que salen
 * de la pantalla o colisionan con el jugador.
 *
 * @param
 * @return
 */

void JUEGO::actualizarBalasEnemigo(){

    for(auto it = BE.begin(); it != BE.end(); ){

        (*it)->mover();

        bool borrar = false;

        if((*it)->fuera()){
            gotoxy((*it)->getX(), (*it)->getY()); printf(" ");
            borrar = true;
        }
        else if((*it)->getX() >= N.getX() && (*it)->getX() <= N.getX()+5 && (*it)->getY() >= N.getY() &&(*it)->getY() <= N.getY()+2){
            N.recibirDanio();
            borrar = true;
        }

        if(borrar){
            delete *it;
            it = BE.erase(it);
        } 
        else{
            it++;
        }
    }
}

/**
 * colisiones verifica las interacciones entre objetos.
 *
 * Detecta colisiones entre balas y asteroides, así como entre
 * balas y el enemigo. Actualiza la puntuación, elimina objetos
 * destruidos y gestiona el daño recibido por el enemigo.
 *
 * @param
 * @return
 */

void JUEGO::colisiones(){

    for(auto itA = A.begin(); itA != A.end(); ){

        bool eliminado = false;

        for(auto itB = B.begin(); itB != B.end(); ){
            if((*itA)->getX() == (*itB)->getX() && ((*itA)->getY() == (*itB)->getY() || (*itA)->getY()+1 == (*itB)->getY())){
                gotoxy((*itB)->getX(), (*itB)->getY()); printf(" ");
                delete *itB;
                itB = B.erase(itB);

                A.push_back(new ASTEROIDE(rand()%75 + 3, 4));
                gotoxy((*itA)->getX(), (*itA)->getY()); printf(" ");
                delete *itA;
                itA = A.erase(itA);

                puntos += 5;
                cont += 5;
                eliminado = true;
                break;
            } 
            else{
                itB++;
            }
        }

        if(!eliminado){
            itA++;
        }
    }

    if(cont >= 20 && E.estaVivo()){
        for(auto it = B.begin(); it != B.end(); ){
            if((*it)->getX() >= E.getX() && (*it)->getX() <= E.getX()+4 && (*it)->getY() >= E.getY() && (*it)->getY() <= E.getY()+1){
                E.recibirDanio();
                delete *it;
                it = B.erase(it);

                if(E.getVida() <= 0){
                    E.morir();
                    puntos += 5;
                    cont = 0;
                }
            }
            else{
                it++;
            }
        }
    }
}

#endif