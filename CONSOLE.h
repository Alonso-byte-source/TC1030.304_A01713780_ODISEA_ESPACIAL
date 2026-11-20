/**
 * CONSOLE.h: funciones para manipular la consola (Windows y Linux/Mac).
 *
 * Contiene funciones para posicionar el cursor, ocultarlo, dibujar los
 * límites del área de juego, detectar entradas del teclado y pausar
 * la ejecución. Son funciones "inline" sueltas (sin clase), así se pueden
 * llamar directo: gotoxy(x, y), SleepMs(30), kbhit(), getch()...
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <cstdlib>

#ifdef _WIN32

#include <windows.h>
#include <conio.h> // getch() y kbhit() ya vienen aquí en Windows

/**
 * gotoxy posiciona el cursor en una coordenada específica.
 *
 * @param x coordenada horizontal.
 * @param y coordenada vertical.
 */
inline void gotoxy(int x, int y){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

/**
 * OcultarCursor oculta el cursor de la consola.
 */
inline void OcultarCursor(){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

/**
 * MostrarCursor vuelve a mostrar el cursor (para menús y captura de texto).
 */
inline void MostrarCursor(){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 10;
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(hCon, &cci);
}

/**
 * SleepMs pausa la ejecución durante los milisegundos indicados.
 */
inline void SleepMs(int ms){
    Sleep(ms);
}

#else // Linux / Mac

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// Las secuencias ANSI empiezan en (1,1), por eso se suma 1 para que
// las coordenadas coincidan con las de Windows (que empiezan en 0,0).
inline void gotoxy(int x, int y){
    printf("\033[%d;%dH", y + 1, x + 1);
}

inline void OcultarCursor(){
    printf("\033[?25l");
    fflush(stdout);
}

inline void MostrarCursor(){
    printf("\033[?25h");
    fflush(stdout);
}

// fflush es necesario porque en Linux stdout está en buffer y,
// sin él, el juego no se dibujaría hasta imprimir un salto de línea.
inline void SleepMs(int ms){
    fflush(stdout);
    usleep(ms * 1000);
}

/**
 * getch lee una tecla sin necesidad de presionar Enter.
 *
 * @return código ASCII de la tecla capturada.
 */
inline int getch(){
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
 * kbhit verifica si hay una tecla disponible sin detener el programa.
 *
 * @return 1 si hay una tecla disponible, 0 en caso contrario.
 */
inline int kbhit(){
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
    clearerr(stdin); // Sin esto, el flag EOF se queda activo y kbhit deja de funcionar
    return 0;
}

#endif

/**
 * limpiarPantalla borra todo el contenido de la consola.
 */
inline void limpiarPantalla(){
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

/**
 * vaciarTeclado descarta las teclas pendientes (por ejemplo las que se
 * presionaron durante el juego) antes de pedir texto al usuario.
 */
inline void vaciarTeclado(){
    while(kbhit()) getch();
}

/**
 * pintarLimites dibuja el área de juego.
 */
inline void pintarLimites(){
    for(int i = 2; i < 78; i++){
        gotoxy(i, 3);  printf("_");
        gotoxy(i, 25); printf("_");
    }
    for(int i = 4; i < 26; i++){
        gotoxy(2, i);  printf("|");
        gotoxy(77, i); printf("|");
    }
}

#endif
