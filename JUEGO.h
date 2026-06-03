#ifndef JUEGO_H
#define JUEGO_H

#include <list>
#include<stdlib.h>
#include <unistd.h>

#include "ENTIDAD.h"
#include "NAVE.h"
#include "ENEMIGO.h"
#include "BALA.h"
#include "ASTEROIDE.h"
#include "CONSOLE.h"

using namespace std;

class JUEGO{ 
    private:
        NAVE N;
        ENEMIGO E;
        list<ASTEROIDE*> A; 
        list<BALA*> B;
        list<BALA*> BE;
        int puntos;
        bool gameOver;
        void Input();
        void Update();
        void Render();
        void actualizarBalasJugador();
        void actualizarBalasEnemigo(); 
        void actualizarAsteroides();
        void colisiones();
    public:
        JUEGO();
        void iniciar();
};

JUEGO::JUEGO() : N(37,20,3,3), E(37, 4, 3, 1), puntos(0), gameOver(false){
    E.setObjetivo(&N);
}

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

void JUEGO::Input(){
    if(!kbhit()) return;
    char tecla = getch();
    if(tecla == ' '){
        B.push_back(new BALA(N.getX() + 2, N.getY() - 1, -1));
    }
    N.setTecla(tecla);
    N.mover();
}

void JUEGO::Update(){
    actualizarBalasJugador();
    actualizarBalasEnemigo();
    actualizarAsteroides();
    colisiones();

    if(puntos >= 5 && E.estaVivo()){
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

void JUEGO::Render(){
    gotoxy(4, 2); printf("Puntos %d ", puntos);
    N.pintar();
    N.pintarSalud();
    if(puntos >= 5 && E.estaVivo()){
        E.pintar();
    }
    for(auto a : A) a->pintar();
}


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

void JUEGO::actualizarBalasEnemigo(){

    for(auto it = BE.begin(); it != BE.end(); ){

        (*it)->mover();

        bool borrar = false;

        if((*it)->fuera()){
            gotoxy((*it)->getX(), (*it)->getY()); printf(" ");
            borrar = true;
        }
        else if((*it)->getX() >= N.getX() &&
                (*it)->getX() <= N.getX()+5 &&
                (*it)->getY() >= N.getY() &&
                (*it)->getY() <= N.getY()+2){
            N.recibirDanio();
            borrar = true;
        }

        if(borrar){
            delete *it;
            it = BE.erase(it);
        } else{
            it++;
        }
    }
}

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

    if(puntos >= 5 && E.estaVivo()){

        for(auto it = B.begin(); it != B.end(); ){

            if(
                (*it)->getX() >= E.getX() &&
                (*it)->getX() <= E.getX()+4 &&
                (*it)->getY() >= E.getY() &&
                (*it)->getY() <= E.getY()+1
            ){

                E.recibirDanio();

                delete *it;
                it = B.erase(it);

                if(E.getVida() <= 0){
                    E.morir();
                    puntos += 20;
                }
            }
            else{
                it++;
            }
        }
    }
}

#endif