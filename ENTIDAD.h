#ifndef ENTIDAD_H
#define ENTIDAD_H

class ENTIDAD{
    protected:
        int x, y;
    public:
        ENTIDAD(int, int);
        virtual void mover() = 0;
        int getX();
        int getY();
};

ENTIDAD::ENTIDAD(int x1, int y1): x(x1), y(y1) {}

int ENTIDAD::getX(){
    return x;
}

int ENTIDAD::getY(){
    return y;
}

#endif