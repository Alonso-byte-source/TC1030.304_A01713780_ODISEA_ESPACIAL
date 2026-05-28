#ifndef NAVE_H
#define NAVE_H 

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#include "ENTIDAD.h"
#include "CONSOLE.h"
#include "BALA.h"
#include <list>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

class NAVE : public ENTIDAD{
    private:
        int corazones, vida;
    public:
        NAVE(int, int, int, int);
        void mover();
        int getVida();
        void recibirDanio();
        void pintar();
        void borrar();
        void pintar_corazones();
        void morir();
};

NAVE::NAVE(int x1, int y1, int corazones1, int vida1)
    : ENTIDAD(x1, y1), corazones(corazones1), vida(vida1){}

int NAVE::getVida(){
    return vida;
}

void NAVE::recibirDanio(){
    corazones--;
}

void NAVE::pintar(){
    gotoxy(x, y); printf("  %c", 94);
    gotoxy(x, y+1); printf(" %c%c%c",60, 207, 62);
    gotoxy(x, y+2); printf("%c%c %c%c", 65, 193, 193, 65);
}

void NAVE::borrar(){
    gotoxy(x, y); printf("        ");
    gotoxy(x, y+1); printf("        ");
    gotoxy(x, y+2); printf("        ");
}

void NAVE::mover(){
    if(kbhit()){
        char tecla = getch();
        borrar();
        if(tecla == IZQUIERDA && x > 3) x--;
        if(tecla == DERECHA && x+6 < 77) x++;
        if(tecla == ARRIBA && y > 4) y--;
        if(tecla == ABAJO && y+3 < 25) y++;
        if(tecla == 'e')corazones--;
        pintar();
        pintar_corazones();
    }
}

void NAVE::pintar_corazones(){
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
        pintar_corazones();
        pintar();
    }
}

#endif