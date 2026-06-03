#ifndef BALA_H
#define BALA_H

#include "ENTIDAD.h"
#include "CONSOLE.h"

class BALA : public ENTIDAD{
    private:
        int direccion;
    public:
        BALA(int, int, int);
        void mover() override;
        void pintar() override;
        void borrar() override;
        bool fuera();
};

BALA::BALA(int x1, int y1, int direccion1): ENTIDAD(x1, y1), direccion(direccion1) {} 

void BALA::pintar(){
    gotoxy(x, y); printf("*");
}

void BALA::borrar(){
    gotoxy(x, y); printf(" ");
}

void BALA::mover(){
    borrar();
    if(direccion < 0){
        y--;
    }
    else if (direccion > 0)
    {
        y++;
    }
    pintar();
}

bool BALA::fuera(){
    if(direccion < 0 && y <= 4)
        return true;

    if(direccion > 0 && y >= 24)
        return true;

    return false;
}

#endif