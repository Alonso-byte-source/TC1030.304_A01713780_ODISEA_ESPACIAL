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
    TipoBala Tipo;
    public:
        BALA(int, int, int, TipoBala);
        void mover();
        bool fuera();
};

BALA::BALA(int _x, int _y, int dir, TipoBala tipo) : ENTIDAD(_x, _y), direccion(dir), Tipo(tipo) {}

void BALA::mover(){
    gotoxy(x, y); printf(" ");
    if(direccion < 0){
        y--;
    }
    else if(direccion > 0)
    {
        y++;
    }
    gotoxy(x, y); printf("%c", 249);
}

bool BALA::fuera(){
    return (y <= 4 || y >= 24);
}

#endif