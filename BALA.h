#ifndef BALA_H
#define BALA_H

#include "ENTIDAD.h"
#include "CONSOLE.h"

class BALA : public ENTIDAD{
    private:
        int direccion;
    public:
        BALA(int, int, int);
        void mover();
        bool fuera();
};

BALA::BALA(int x1, int y1, int direccion1): ENTIDAD(x1, y1), direccion(direccion1) {} 

void BALA::mover(){
    gotoxy(x, y); printf(" ");
    if(direccion < 0){
        y--;
    }
    else if (direccion > 0)
    {
        y++;
    }
    gotoxy(x, y); printf("%c", 249);
}

bool BALA::fuera(){

    if(direccion < 0 && y <= 4)
        return true;

    if(direccion > 0 && y >= 24)
        return true;

    return false;
}

#endif