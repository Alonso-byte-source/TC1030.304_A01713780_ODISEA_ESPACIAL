#ifndef BALA_H
#define BALA_H

#include "NAVE.h"
#include "CONSOLE.h"

enum TipoBala{
    JUGADOR,
    VILLANO
};

class BALA : public ENTIDAD{
    private:
    int direccion;
    TipoBala tipo;
    public:
        BALA(int, int, int, TipoBala);
        void mover();
        bool fuera();
};

BALA::BALA(int x1, int y1, int direccion1, TipoBala tipo1) : ENTIDAD(x1, y1), direccion(direccion1), tipo(tipo1) {}

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
    if(y == 4) return TRUE;
    return FALSE;
}

#endif