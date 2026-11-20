/**
 * Proyecto Odisea Espacial - programa principal
 * Alonso Vega Reséndiz
 * A01713780
 *
 * Menú principal: Jugar / Ver ranking / Salir.
 * Al terminar una partida se pide el nombre y se guarda en ranking.csv.
 * En "Ver ranking" se puede ordenar por distintos atributos, elegir el
 * algoritmo de ordenamiento y filtrar los datos.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "JUEGO.h"
#include "RANKING.h"

using namespace std;

const string ARCHIVO = "ranking.csv";

/** leerLinea muestra un mensaje y lee una línea completa. */
string leerLinea(const string& mensaje){
    cout << mensaje;
    string s;
    if(!getline(cin, s)) s = "";
    return s;
}

/** leerEntero lee un número entero; si no es válido regresa -1. */
int leerEntero(const string& mensaje){
    string s = leerLinea(mensaje);
    try{
        return stoi(s);
    }
    catch(...){
        return -1;
    }
}

void pausa(){
    leerLinea("\nPresiona Enter para continuar...");
}

/** jugarPartida corre el juego y guarda el resultado en el ranking. */
void jugarPartida(RANKING& ranking){
    JUEGO juego;
    // El ranking está ordenado por puntos: el primero es el récord a superar
    string nombreRecord = "";
    int puntosRecord = 0;
    ranking.primero(nombreRecord, puntosRecord);
    juego.setRecord(nombreRecord, puntosRecord);
    juego.iniciar();

    MostrarCursor();
    vaciarTeclado(); // Descarta las teclas que quedaron del juego
    limpiarPantalla();

    cout << "========== GAME OVER ==========\n\n";
    cout << "Puntos:               " << juego.getPuntos() << "\n";
    cout << "Asteroides destruidos: " << juego.getAsteroides() << "\n";
    cout << "Enemigos derrotados:   " << juego.getEnemigos() << "\n";
    cout << "Tiempo (segundos):     " << juego.getDuracion() << "\n\n";

    string nombre = leerLinea("Tu nombre: ");
    REGISTRO r(nombre, juego.getPuntos(), juego.getAsteroides(), juego.getEnemigos(), juego.getDuracion());
    int pos = ranking.insertarOrdenado(r); // Entra directo a su lugar, sin reordenar todo
    if(ranking.anexar(r, ARCHIVO)){
        cout << "\nPartida guardada en " << ARCHIVO << ".\n";
    }
    else{
        cout << "\nNo se pudo escribir en " << ARCHIVO << ".\n";
    }

    cout << "\nQuedaste en el lugar #" << pos << " de " << ranking.tamanio() << ".\n";
    if(pos == 1) cout << "¡NUEVO RECORD!\n";
    cout << "\n--- TOP 5 ---\n";
    ranking.top(5).mostrar();
    pausa();
}

/** pedirCriterio muestra los atributos y regresa el elegido (0 si no es válido). */
int pedirCriterio(){
    cout << "\n  Ordenar por:\n";
    cout << "   1) Puntos (mayor a menor)\n";
    cout << "   2) Nombre (A-Z)\n";
    cout << "   3) Asteroides destruidos\n";
    cout << "   4) Enemigos derrotados\n";
    cout << "   5) Duracion de la partida\n";
    int c = leerEntero("  Opcion: ");
    return (c >= 1 && c <= 5) ? c : 0;
}

/** pedirAlgoritmo muestra los algoritmos y regresa el elegido (0 si no es válido). */
int pedirAlgoritmo(){
    cout << "\n  Algoritmo:\n";
    cout << "   1) Burbuja\n";
    cout << "   2) Insercion\n";
    cout << "   3) Merge sort\n";
    int a = leerEntero("  Opcion: ");
    return (a >= 1 && a <= 3) ? a : 0;
}

const char* NOMBRES_CRITERIO[] = {"", "puntos", "nombre", "asteroides", "enemigos", "duracion"};
const char* NOMBRES_ALGORITMO[] = {"", "burbuja", "insercion", "merge sort"};

/**
 * menuRanking permite ver el ranking, ordenarlo y filtrarlo.
 * Trabaja sobre una "vista" (copia): los filtros no borran datos del ranking real.
 */
void menuRanking(RANKING& ranking){
    RANKING vista = ranking; // El ranking ya está ordenado por puntos
    string info = "Todas las partidas, ordenadas por puntos.";

    while(true){
        limpiarPantalla();
        cout << "============== RANKING ==============\n";
        cout << info << "  (" << vista.tamanio() << " registros)\n\n";
        vista.mostrar();

        cout << "\n 1) Ordenar\n";
        cout << " 2) Filtrar: puntos minimos\n";
        cout << " 3) Filtrar: nombre de jugador\n";
        cout << " 4) Filtrar: top N (del orden actual)\n";
        cout << " 5) Restablecer (quitar filtros)\n";
        cout << " 6) Agregar datos de prueba (solo en memoria)\n";
        cout << " 0) Volver\n";
        if(!cin) return;
        int op = leerEntero("Opcion: ");
        if(!cin) return;

        if(op == 0){
            return;
        }
        else if(op == 1){
            int c = pedirCriterio();
            if(c == 0){ info = "Criterio no válido."; continue; }
            int a = pedirAlgoritmo();
            if(a == 0){ info = "Algoritmo no válido."; continue; }
            vista.ordenar((CRITERIO)c, (ALGORITMO)a);
            info = string("Ordenado por ") + NOMBRES_CRITERIO[c] + " con " + NOMBRES_ALGORITMO[a] +
                   " (" + to_string(vista.getComparaciones()) + " comparaciones).";
        }
        else if(op == 2){
            int min = leerEntero("  Puntos minimos: ");
            if(min < 0){ info = "Valor no valido."; continue; }
            vista = vista.filtrarPorPuntos(min);
            info = "Filtro: " + to_string(min) + " puntos o más.";
        }
        else if(op == 3){
            string texto = leerLinea("  Nombre (o parte): ");
            vista = vista.filtrarPorNombre(texto);
            info = "Filtro: jugadores que contienen \"" + texto + "\".";
        }
        else if(op == 4){
            int n = leerEntero("  Cuantos (N): ");
            if(n <= 0){ info = "Valor no valido."; continue; }
            vista = vista.top(n);
            info = "Primeros " + to_string(n) + " del orden actual.";
        }
        else if(op == 5){
            vista = ranking;
            info = "Todas las partidas, ordenadas por puntos.";
        }
        else if(op == 6){
            int n = leerEntero("  Cuantos registros de prueba: ");
            if(n <= 0 || n > 5000){ info = "Usa un valor entre 1 y 5000."; continue; }
            vista.generarPrueba(n);
            info = to_string(n) + " registros de prueba agregados (se pierden al restablecer).";
        }
        else{
            info = "Opción no valida.";
        }
    }
}

int main(){
    srand(time(nullptr));
    RANKING ranking;
    int cargados = ranking.cargar(ARCHIVO);
    ranking.ordenar(POR_PUNTOS, MERGE); // Se ordena una sola vez; después se inserta en su lugar

    while(true){
        limpiarPantalla();
        cout << "======= ODISEA ESPACIAL =======\n\n";
        cout << "Registros cargados: " << cargados << "\n\n";
        cout << " 1) Jugar\n";
        cout << " 2) Ver ranking\n";
        cout << " 3) Salir\n";
        int op = leerEntero("Opcion: ");
        if(!cin) break;

        if(op == 1){
            jugarPartida(ranking);
            cargados = ranking.tamanio();
        }
        else if(op == 2){
            menuRanking(ranking);
        }
        else if(op == 3){
            break;
        }
    }
    cout << "\nSee you later alligator!\n";
    return 0;
}
