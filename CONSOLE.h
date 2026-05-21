#ifndef CONSOLE_H
#define CONSOLE_H

#include<stdio.h>
#include<Windows.h>

class CONSOLE{
    public:
        static void gotoxy();
        static void OcultarCursor();
        static void pintar_limites();
};

static void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

static void OcultarCursor(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

static void pintar_limites(){
    for(int i = 2; i < 78; i++){
        gotoxy(i, 3); printf("%c", 205);
        gotoxy(i, 25); printf("%c", 205);
    }
    for(int i = 4; i < 25; i++){
        gotoxy(2, i); printf("%c", 186);
        gotoxy(77, i); printf("%c", 186);
    }
    gotoxy(2, 3); printf("%c", 201);
    gotoxy(2, 25); printf("%c", 200);
    gotoxy(77, 3); printf("%c", 187);
    gotoxy(77, 25); printf("%c", 188);
}

#endif