#ifndef ENTIDAD_H
#define ENTIDAD_H 

#include "CONSOLE.h"

class ENTIDAD{
    protected:
        int x, y;
    public:
        ENTIDAD();
        ENTIDAD(int, int);
        int X();
        int Y();
        void mover();
        void pintar();
};

ENTIDAD::ENTIDAD(int _x, int _y): x(_x), y(_y){}

int ENTIDAD::X(){
    return x;
}

int ENTIDAD::Y(){
    return y;
}

#endif