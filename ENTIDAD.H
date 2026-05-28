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

ENTIDAD::ENTIDAD(int x1, int y1): x(x1), y(y1){}

int ENTIDAD::X(){
    return x;
}

int ENTIDAD::Y(){
    return y;
}

#endif