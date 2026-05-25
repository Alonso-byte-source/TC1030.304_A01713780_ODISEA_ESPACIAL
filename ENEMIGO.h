#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <unistd.h>

#include "ENTIDAD.h"
#include "NAVE.h"

class ENEMIGO : public ENTIDAD{
    private: 
        int vida;
        bool disparando, vivo;
        int cooldown;
    public:
        ENEMIGO(int, int, int, bool);
        void mover(class NAVE &N);
        void pintar();
        void borrar();
        void cor();
        int vid();
        bool puedeDisparar();
        void morir();
        bool estaVivo();
};

ENEMIGO::ENEMIGO(int _x, int _y, int _vida, bool _vivo) 
    : ENTIDAD(_x, _y), vida(_vida), vivo(_vivo) {
        cooldown = 0;
        disparando = false;
    }

void ENEMIGO::pintar(){
    gotoxy(x, y); printf(" %c%c%c ", 170, 219, 169);
    gotoxy(x, y+1); printf("  %c  ", 209);
}

void ENEMIGO::borrar(){
    gotoxy(x, y); printf("        ");
    gotoxy(x, y+1); printf("        ");
}

void ENEMIGO::mover(class NAVE &N){
    borrar();
    if(disparando){

        cooldown++;

        if(cooldown >= 30){
            disparando = false;
            cooldown = 0;
        }
    }
    else{
        if(x < N.X()){
            x++;
        }
        else if(x > N.X()){
            x--;
        }
        if(abs(x - N.X()) <= 1){
            disparando = true;
        }
    }
    pintar();
}

void ENEMIGO::cor(){
    vida--;
}

int ENEMIGO::vid(){
    return vida;
}

bool ENEMIGO::puedeDisparar(){
    return disparando && cooldown == 1;
}

void ENEMIGO::morir(){

    borrar();

    gotoxy(x, y);
    printf("***");

    gotoxy(x, y+1);
    printf("***");

    Sleep(200);

    borrar();
    vivo = false;
}

bool ENEMIGO::estaVivo(){
    return vivo;
}

#endif