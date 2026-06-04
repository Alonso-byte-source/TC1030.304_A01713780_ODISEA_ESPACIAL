/**
 * La clase CONSOLE proporciona FUNCIONES para manipular la consola.
 *
 * Contiene funciones para posicionar el cursor, ocultarlo,
 * dibujar los límites del área de juego, detectar entradas
 * del teclado y controlar pausas en la ejecución del programa.
 */

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


/**
 * gotoxy posiciona el cursor en una coordenada específica.
 *
 * Mueve el cursor de la consola a la posición indicada por
 * las coordenadas x e y para permitir la impresión de texto
 * en una ubicación determinada.
 *
 * @param x coordenada horizontal.
 * @param y coordenada vertical.
 * @return
 */

static void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

/**
 * OcultarCursor oculta el cursor de la consola.
 *
 * Desactiva la visualización del cursor para mejorar la
 * apariencia gráfica durante la ejecución del juego.
 *
 * @param
 * @return
 */

static void OcultarCursor(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    _CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

/**
 * SleepMs pausa temporalmente la ejecución del programa.
 *
 * Detiene la ejecución durante la cantidad de milisegundos
 * especificada para controlar la velocidad de actualización
 * del juego.
 *
 * @param ms tiempo de espera en milisegundos.
 * @return
 */


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


/**
 * getch obtiene una tecla presionada por el usuario.
 *
 * Lee una tecla desde el teclado sin necesidad de que
 * el usuario presione Enter.
 *
 * @param
 * @return código ASCII de la tecla capturada.
 */

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

/**
 * kbhit verifica si existe una tecla disponible.
 *
 * Comprueba si el usuario ha presionado alguna tecla
 * sin detener la ejecución normal del programa.
 *
 * @param
 * @return 1 si existe una tecla disponible, 0 en caso contrario.
 */

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

/**
 * pintarLimites dibuja el área de juego.
 *
 * Imprime los bordes superior, inferior y laterales que
 * delimitan la zona donde se desarrollará la partida.
 *
 * @param
 * @return
 */
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

