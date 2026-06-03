#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "ENTIDAD.h"
#include "CONSOLE.h"
#include "NAVE.h"

class ENEMIGO : public ENTIDAD{
    private:
        int vida,cooldown;
        bool disparando, vivo;
        NAVE* objetivo;
    public:
        ENEMIGO(int, int, int, bool);
        void mover() override;
        void pintar();
        void borrar();
        void recibirDanio();
        bool puedeDisparar();
        void morir();
        bool estaVivo();
        int getVida();
        void setObjetivo(NAVE* n);
};

ENEMIGO::ENEMIGO(int x1, int y1, int vida1, bool vivo1)
    : ENTIDAD(x1, y1), vida(vida1), vivo(vivo1), objetivo(nullptr), cooldown(0), disparando(false){}

void ENEMIGO::mover(){
    if(!objetivo) return;
    borrar();
    if(disparando){
        cooldown++;
        if(cooldown >= 30){
            disparando = false;
            cooldown = 0;
        }
    }
    else{
        if(x < objetivo->getX()){
            x++;
        }
        else if(x > objetivo->getX()){
            x--;
        }
        if(abs(x - objetivo->getX()) <= 1){
            disparando = true;
        }
    }
    pintar();
}

void ENEMIGO::pintar(){
    gotoxy(x, y);   printf(" %c%c%c ", 170, 219, 169);
    gotoxy(x, y+1); printf("  %c  ", 209);
}

void ENEMIGO::borrar(){
    gotoxy(x, y);   printf("        ");
    gotoxy(x, y+1); printf("        ");
}

void ENEMIGO::recibirDanio(){
    vida--;
}

bool ENEMIGO::puedeDisparar(){
    return cooldown == 1 && disparando;
}

void ENEMIGO::morir(){
    borrar();
    gotoxy(x, y);   printf("***");
    gotoxy(x, y+1); printf("***");
    Sleep(200);

    borrar();
    gotoxy(x, y);   printf("* ** *");
    gotoxy(x, y+1); printf("* ** *");
    SleepMs(200);

    borrar();
    vivo = false;
}

bool ENEMIGO::estaVivo(){
    return vivo;
}

int ENEMIGO::getVida(){
    return vida;
}

void ENEMIGO::setObjetivo(NAVE* n){
    objetivo = n;
}

#endif