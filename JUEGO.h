/**
 * Proyecto Odisea Espacial clase JUEGO
 * Alonso Vega Reséndiz
 * A01713780
 * 03/06/2026
 * version : 1.1
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

#include <string>
#include <cstdlib>
#include <ctime>

// Bibliotecas de objetos a usar
#include "LISTA.h"
#include "ENTIDAD.h"
#include "NAVE.h"
#include "ENEMIGO.h"
#include "BALA.h"
#include "ASTEROIDE.h"
#include "CONSOLE.h"

using namespace std;

//Declaración de clase JUEGO
class JUEGO{
    // OJO: el orden de declaración es el mismo que usa el constructor
    private:
        int cont; // Contador para controlar la aparición del enemigo
        int puntos;
        int asteroidesDestruidos; // Estadísticas para el ranking
        int enemigosDerrotados;
        int duracion; // Segundos que duró la partida
        time_t inicio;
        int record; // Mejor puntuación del ranking (para mostrarla en pantalla)
        string nombreRecord;
        bool gameOver;
        NAVE N;
        ENEMIGO E;
        LISTA<ASTEROIDE*> A; // Asteroides
        LISTA<BALA*> B;      // Balas del jugador
        LISTA<BALA*> BE;     // Balas del enemigo
        LISTA<ENTIDAD*> entidades; // Punteros a la clase abstracta ENTIDAD
        void Input();
        void Update();
        void Render();
        void actualizarBalasJugador();
        void actualizarBalasEnemigo();
        void actualizarAsteroides();
        void colisiones();
    public:
        JUEGO();
        ~JUEGO();
        void iniciar();
        int getPuntos() const;
        int getAsteroides() const;
        int getEnemigos() const;
        int getDuracion() const;
        void setRecord(const string&, int);
};

/**
 * JUEGO inicializa la nave, el enemigo, el contador, la puntuación y el
 * estado de la partida. También establece la nave como objetivo del enemigo.
 */
JUEGO::JUEGO() : cont(0), puntos(0), asteroidesDestruidos(0), enemigosDerrotados(0),
                 duracion(0), inicio(0), record(0), nombreRecord(""), gameOver(false), N(37,20,3,3), E(37, 4, 6, true){
    E.setObjetivo(&N);
    entidades.agregar(&N);
    entidades.agregar(&E);
}

/** ~JUEGO libera la memoria dinámica de asteroides y balas. */
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
    A.limpiar();
    B.limpiar();
    BE.limpiar();
}

/**
 * iniciar configura la consola, dibuja los límites, genera los asteroides
 * iniciales y mantiene el ciclo principal mientras la partida continúe.
 */
void JUEGO::iniciar(){
    srand(time(nullptr)); // Sin esto los "aleatorios" son los mismos en cada partida
    inicio = time(nullptr);
    limpiarPantalla();
    OcultarCursor();
    pintarLimites();
    N.pintar();

    // Crea 3 asteroides y los añade a la lista de asteroides
    for(int i=0; i<3; i++){
        A.agregar(new ASTEROIDE(rand()%75 + 3, rand()%5 + 4));
    }

    // Ciclo principal del juego
    while(!gameOver){
        Input();  // Lee la entrada del teclado
        Update(); // Actualiza el estado de los objetos
        Render(); // Dibuja los objetos
        SleepMs(30);
    }
    duracion = (int)difftime(time(nullptr), inicio);
}

/** Getters con las estadísticas de la partida (para crear el REGISTRO). */
int JUEGO::getPuntos() const { return puntos; }
int JUEGO::getAsteroides() const { return asteroidesDestruidos; }
int JUEGO::getEnemigos() const { return enemigosDerrotados; }
int JUEGO::getDuracion() const { return duracion; }

/**
 * setRecord recibe el mejor puntaje del ranking (el primero de la lista
 * ordenada) para mostrarlo durante la partida.
 */
void JUEGO::setRecord(const string& nombre, int puntosRecord){
    nombreRecord = nombre;
    record = puntosRecord;
}

/** Input detecta las teclas, mueve la nave y genera balas al disparar. */
void JUEGO::Input(){
    if(!kbhit()) return;
    char tecla = getch();
    if(tecla == ' '){
        B.agregar(new BALA(N.getX() + 2, N.getY() - 1, -1)); // Bala del jugador
    }
    N.setTecla(tecla);
    N.mover();
}

/**
 * Update actualiza balas, asteroides, colisiones y comportamiento del
 * enemigo, y verifica si el jugador perdió todas sus vidas.
 */
void JUEGO::Update(){
    // El enemigo aparece cuando cont llega a 20. Se procesa primero para que
    // su bala nueva se mueva una sola vez por frame, como las demás.
    if(cont >= 20 && E.estaVivo()){
        E.mover();
        if(E.puedeDisparar()){
            BE.agregar(new BALA(E.getX() + 2, E.getY() + ENEMIGO::ALTO, 1)); // Bala del enemigo
        }
    }

    actualizarBalasJugador();
    actualizarBalasEnemigo();
    actualizarAsteroides();
    colisiones();

    N.verificarMuerte();
    if(N.getVida() <= 0){
        gameOver = true;
    }
}

/** Render dibuja la puntuación, la nave, la salud, el enemigo y los asteroides. */
void JUEGO::Render(){
    // Línea de récord: avisa cuando el jugador supera al primer lugar del ranking
    char linea[64];
    if(puntos > record)  snprintf(linea, sizeof(linea), "** NUEVO RECORD! **");
    else                 snprintf(linea, sizeof(linea), "Record: %s (%d)", nombreRecord.c_str(), record);
    gotoxy(4,1); printf("%-40s", linea);
    gotoxy(4,2); printf("Puntos %d ", puntos);
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
        a->pintar();
    }
}

/** actualizarAsteroides mueve los asteroides y revisa choques con la nave. */
void JUEGO::actualizarAsteroides(){
    for(auto a : A){
        a->mover();
        a->choque(N);
    }
}

/** actualizarBalasJugador mueve las balas del jugador y elimina las que salen. */
void JUEGO::actualizarBalasJugador(){
    for(auto it = B.begin(); it != B.end(); ){
        (*it)->mover();

        if((*it)->fuera()){
            gotoxy((*it)->getX(), (*it)->getY()); printf(" ");
            delete *it;
            it = B.eliminar(it);
        }
        else{
            it++;
        }
    }
}

/**
 * actualizarBalasEnemigo mueve las balas enemigas, detecta impactos contra
 * la nave y elimina las que salen de la pantalla o impactan.
 */
void JUEGO::actualizarBalasEnemigo(){
    for(auto it = BE.begin(); it != BE.end(); ){
        (*it)->mover();
        bool borrar = false;
        if((*it)->fuera()){
            gotoxy((*it)->getX(), (*it)->getY()); printf(" ");
            borrar = true;
        }
        else if((*it)->getX() >= N.getX() && (*it)->getX() < N.getX() + NAVE::ANCHO &&
                (*it)->getY() >= N.getY() && (*it)->getY() < N.getY() + NAVE::ALTO){
            N.recibirDanio();
            borrar = true;
        }
        if(borrar){
            delete *it;
            it = BE.eliminar(it);
        }
        else{
            it++;
        }
    }
}

/**
 * colisiones detecta choques entre balas y asteroides, y entre balas y
 * enemigo. Actualiza la puntuación y elimina los objetos destruidos.
 */
void JUEGO::colisiones(){
    for(auto itA = A.begin(); itA != A.end(); ){
        bool eliminado = false;
        for(auto itB = B.begin(); itB != B.end(); ){
            if((*itA)->getX() == (*itB)->getX() && ((*itA)->getY() == (*itB)->getY() || (*itA)->getY()+1 == (*itB)->getY())){
                gotoxy((*itB)->getX(), (*itB)->getY()); printf(" ");
                delete *itB;
                itB = B.eliminar(itB);
                A.agregar(new ASTEROIDE(rand()%75 + 3, 4));
                gotoxy((*itA)->getX(), (*itA)->getY()); printf(" ");
                delete *itA;
                itA = A.eliminar(itA);
                puntos += 5;
                cont += 5;
                asteroidesDestruidos++;
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
            if((*it)->getX() >= E.getX() && (*it)->getX() < E.getX() + ENEMIGO::ANCHO &&
               (*it)->getY() >= E.getY() && (*it)->getY() < E.getY() + ENEMIGO::ALTO){
                E.recibirDanio();
                gotoxy((*it)->getX(), (*it)->getY()); printf(" ");
                delete *it;
                it = B.eliminar(it);
                if(E.getVida() <= 0){
                    E.morir();
                    puntos += 5;
                    cont = 0;
                    enemigosDerrotados++;
                    E.reaparecer(); // Queda listo para la siguiente oleada (aparece al llegar cont a 20)
                    break;
                }
            }
            else{
                it++;
            }
        }
    }
}

#endif
