#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>

#ifdef _WIN32

#include <Windows.h>
#include <conio.h>

class CONSOLE{
    public:
        static void gotoxy();
        static void OcultarCursor();
        static void pintarLimites();
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

    _CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

static void SleepMs(int ms){
    Sleep(ms);
}


#else
#include <unistd.h>
#include <termios.h>
#include <fcnt1.h>

class CONSOLE{
    public:
        static void gotoxy();
        static void OcultarCursor();
        static void pintarLimites();
        static int getch();
        static void SleepMs(int);
        static int kbhit();
};

static void gotoxy(int x, int y){
    printf("\033[%d;%dH", y, x);
}

static void OcultarCursor(){
    printf("\033[?25l");
}

static void SleepMS(int ms){
    usleep(ms * 1000);
}

static int getch(){
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

static int kbhit(){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#endif

static void pintarLimites(){

    for(int i = 2; i < 78; i++){
        gotoxy(i, 3); printf("_");
        gotoxy(i, 25); printf("_");
    }

    for(int i = 4; i < 26; i++){
        gotoxy(2, i); printf("|");
        gotoxy(77, i); printf("|");
    }
}

#endif

