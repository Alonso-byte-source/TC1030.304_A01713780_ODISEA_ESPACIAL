#ifndef JUEGO_H
#define JUEGO_H

#include <list>
#include<stdlib.h>
#include <unistd.h>

#include "ENTIDAD.h"
#include "NAVE.h"
#include "AST.h"
#include "BALA.h"
#include "CONSOLE.h"

#include "ENEMIGO.h"


using namespace std;

class JUEGO{
    private:
       NAVE N;
       ENEMIGO E;
       list<AST*> A; 
       list<BALA*> B;
       list<BALA*> BE;
       int puntos;
       bool gameOver;
    public:
        JUEGO();
        void iniciar();
};

JUEGO::JUEGO() : N(37,20,3,3), E(37, 4, 3, 1), puntos(0), gameOver(false){}

void JUEGO::iniciar(){
    OcultarCursor();
    pintar_limites();
    N.pintar();
    N.pintar_corazones();

    list<AST*>::iterator itA;
    for(int i=0; i<4; i++){
        A.push_back(new AST(rand()%75 +3, rand()%5 + 4));
    }

    list<BALA*>::iterator it;
    list<BALA*>::iterator ite;

    while(!gameOver){
        gotoxy(4, 2); printf("Puntos %d", puntos);
        if(kbhit()){
            char tecla = getch();
            if(tecla == 'a')
            B.push_back(new BALA(N.X() + 2, N.Y() - 1, -1, JUGADOR));
        }

        for(it = B.begin(); it != B.end(); it++){
            (*it)->mover();
            if((*it)->fuera()){
                gotoxy((*it)->X(), (*it)->Y()); printf(" ");
                delete(*it);
                it = B.erase(it);
            }
        }

        for(itA = A.begin(); itA != A.end(); itA++){
            (*itA)->mover();
            (*itA)->choque(N);
        }

        for(itA = A.begin(); itA != A.end(); itA++){
            for(it = B.begin(); it != B.end(); it++){
                if((*itA)->X() == (*it)->X() && ((*itA)->Y()+1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() )){
                    gotoxy((*it)->X(), (*it)->Y()); printf(" ");
                    delete(*it);
                    it = B.erase(it);

                    A.push_back(new AST(rand()%75 + 3, 4));
                    gotoxy((*itA)->X(), (*itA)->Y()); printf(" ");
                    delete(*itA);
                    itA = A.erase(itA);
                    puntos += 5;
                }
            }
        }
        if(puntos >= 5 && E.estaVivo()){

            E.mover(N);
            E.pintar();

            for(it = B.begin(); it != B.end(); ){

                if(
                    (*it)->X() >= E.X() &&
                    (*it)->X() <= E.X()+4 &&

                    (*it)->Y() >= E.Y() &&
                    (*it)->Y() <= E.Y()+1
                ){

                    E.recibirDanio();

                    gotoxy((*it)->X(), (*it)->Y());
                    printf(" ");

                    delete(*it);

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

            if(E.puedeDisparar()){
                BE.push_back(
                    new BALA(
                        E.X()+1,
                        E.Y()+2,
                        1,
                        VILLANO
                    )
                );
            }

            for(ite = BE.begin(); ite != BE.end(); ){
                (*ite)->mover();
                bool borrar = false;
                if((*ite)->fuera()){
                    borrar = true;
                }
                else if(
                    (*ite)->X() >= N.X() &&
                    (*ite)->X() <= N.X()+5 &&

                    (*ite)->Y() >= N.Y() &&
                    (*ite)->Y() <= N.Y()+2
                ){
                    N.recibirDanio();
                    N.pintar_corazones();
                    borrar = true;
                }

                if(borrar){
                    gotoxy((*ite)->X(), (*ite)->Y());
                    printf(" ");
                    delete(*ite);
                    ite = BE.erase(ite);
                }
                else{
                    ite++;
                }
            }
        }
        if(N.getVida() == 0) gameOver = TRUE;
        N.morir();
        N.mover();
        Sleep(30);
    }
} 

#endif
