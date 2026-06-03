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
    public: 
        NAVE(int, int, int, int);
        void recibirDanio();
        void pintar();
        void mover() override;
        void borrar();
        void pintarSalud();
        void morir();
        int getVida();
};

NAVE::NAVE(int x1, int y1, int corazones1, int vida1): ENTIDAD(x1, y1), corazones(corazones1), vida(vida1) {}

void NAVE::recibirDanio(){
    corazones --;
}

void NAVE::mover(){
    if(kbhit()){
        char tecla = getch();
        borrar();
        if(tecla == 'a' && x > 3) x--;
        if(tecla == 'd' && x+6 < 77) x++;
        if(tecla == 'w' && y > 4) y--;
        if(tecla == 's' && y+3 < 25) y++;
        pintar();
    }
}

void NAVE::pintar(){
    gotoxy(x, y);   printf("  %c", 94);
    gotoxy(x, y+1); printf(" %c%c%c",60, 207, 62);
    gotoxy(x, y+2); printf("%c%c %c%c", 65, 193, 193, 65);
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