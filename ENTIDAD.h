#ifndef ENTIDAD_H
#define ENTIDAD_H

class ENTIDAD{
    protected:
        int x, y;
    public:
        ENTIDAD(int, int);
        int getX();
        int getY();
        virtual void mover() = 0;
        virtual void pintar() = 0;
        virtual void borrar() = 0;
        virtual ~ENTIDAD() = default;
};

ENTIDAD::ENTIDAD(int x1, int y1): x(x1), y(y1) {}

int ENTIDAD::getX(){
    return x;
}

int ENTIDAD::getY(){
    return y;
}

#endif