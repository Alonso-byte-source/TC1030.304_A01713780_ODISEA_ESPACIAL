#ifndef AST_H
#define AST_H 

#include "ENTIDAD.h"
#include "CONSOLE.h"
#include "NAVE.h"

class AST : public ENTIDAD{
    public:
        AST(int, int);
        void pintar();
        void mover();
        void choque(class NAVE &N);
};

AST::AST(int _x, int _y) : ENTIDAD(_x, _y){}

void AST::pintar(){
    gotoxy(x, y); printf("%c", 233);
}

void AST::mover(){
    gotoxy(x, y); printf(" ");
    y++;
    if(y > 24){
        x = rand() % 71 + 4;
        y = 4;
    }
    pintar();
}

void AST::choque(class NAVE &N){
    if(x >= N.X() && x < N.X()+6 && y >= N.Y() && y <= N.Y()+2){
        N.COR();
        N.borrar();
        N.pintar();
        N.pintar_corazones();
        x = rand() % 71 + 4;
        y = 4;
    }
}


#endif