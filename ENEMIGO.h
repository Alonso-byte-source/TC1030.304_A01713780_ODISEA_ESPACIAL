#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <unistd.h>

#include "ENTIDAD.h"
#include "NAVE.h"

class ENEMIGO : public ENTIDAD{
    private: 
        int corazones, vida;
        bool disparando;
        int cooldown;
    public:
        ENEMIGO(int, int, int, int);
        void mover(class NAVE &N);
        void pintar();
        void borrar();
        int vid();
        bool puedeDisparar();
};

ENEMIGO::ENEMIGO(int _x, int _y, int _corazones, int _vida) 
    : ENTIDAD(_x, _y), corazones(_corazones), vida(_vida) {
        cooldown = 0;
        disparando = false;
    }

void ENEMIGO::pintar(){
    gotoxy(x, y); printf("%c%c%c", 170, 219, 169);
    gotoxy(x, y+1); printf(" %c", 209);
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

int ENEMIGO::vid(){
    return vida;
}

bool ENEMIGO::puedeDisparar(){
    return disparando && cooldown == 1;
}

#endif