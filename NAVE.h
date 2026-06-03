#ifndef NAVE_H
#define NAVE_H

#include "ENTIDAD.h"
#include "CONSOLE.h"
#include <conio.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80


class NAVE : public ENTIDAD{
    private:
        int corazones, vida;
        char boton;
    public: 
        NAVE(int, int, int, int);
        void recibirDanio();
        void pintar() override;
        void mover() override;
        void borrar() override;
        void pintarSalud();
        void morir();
        int getVida();
        void setTecla(char);
};

NAVE::NAVE(int x1, int y1, int corazones1, int vida1): ENTIDAD(x1, y1), corazones(corazones1), vida(vida1), boton(' ') {}

void NAVE::recibirDanio(){
    corazones --;
}

void NAVE::setTecla(char tecla){
    boton = tecla;
}

void NAVE::mover(){
    borrar();
    if(boton == 'a' && x > 3) x--;
    if(boton == 'd' && x+6 < 77) x++;
    if(boton == 'w' && y > 4) y--;
    if(boton == 's' && y+3 < 25) y++;
    pintar();
}

void NAVE::pintar(){
    gotoxy(x, y);   printf("  ^");
    gotoxy(x, y+1); printf(" <0>");
    gotoxy(x, y+2); printf("A^ ^A");
}

void NAVE::borrar(){
    gotoxy(x, y);   printf("       ");
    gotoxy(x, y+1); printf("       ");
    gotoxy(x, y+2); printf("       ");
}

void NAVE::pintarSalud(){
    gotoxy(50,2); printf("VIDAS %d", vida);
    gotoxy(64, 2); printf("SALUD");
    gotoxy(70, 2); printf("      ");
    for(int i = 0; i < corazones; i++){
        gotoxy(70+i, 2); printf("*");
    }
}

void NAVE::morir(){
    if(corazones == 0){
        borrar();
        gotoxy(x, y);   printf("   **   ");
        gotoxy(x, y+1); printf("  ****  ");
        gotoxy(x, y+2); printf("   **   ");
        Sleep(200);

        borrar();
        gotoxy(x, y);   printf(" * ** * ");
        gotoxy(x, y+1); printf("  ****  ");
        gotoxy(x, y+2); printf(" * ** * ");
        Sleep(200);

        borrar();
        vida--;
        corazones = 3;
        pintarSalud();
        pintar();
    }
}

int NAVE::getVida(){
    return vida;
}
#endif