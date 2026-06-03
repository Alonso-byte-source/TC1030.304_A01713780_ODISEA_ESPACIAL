#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include "ENTIDAD.h"
#include "NAVE.h"
#include "CONSOLE.h"

class ASTEROIDE : public ENTIDAD{
    public:
        ASTEROIDE(int, int);
        void pintar();
        void mover();
        void choque(NAVE&);
};

ASTEROIDE::ASTEROIDE(int x1, int y1): ENTIDAD(x1, y1) {}

void ASTEROIDE::pintar(){
    gotoxy(x, y); printf("%c", 233);
}

void ASTEROIDE::mover(){
    gotoxy(x, y); printf(" ");
    y++;
    if(y > 24){
        x = rand() % 71 + 4;
        y = 4;
    }
    pintar();
}

void ASTEROIDE::choque(NAVE& N){
    if(x >= N.getX() && x < N.getX()+6 && y >= N.getY() && y <= N.getY()+2){
        N.recibirDanio();
        N.borrar();
        N.pintar();
        N.pintarSalud();
        x = rand() % 71 + 4;
        y = 4;
    }
}

#endif