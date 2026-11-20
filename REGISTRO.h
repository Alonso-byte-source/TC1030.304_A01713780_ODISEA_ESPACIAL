/**
 * Proyecto Odisea Espacial clase REGISTRO
 * Alonso Vega Reséndiz
 * A01713780
 * version : 1
 *
 * La clase REGISTRO guarda los datos de UNA partida terminada. No hereda de
 * ENTIDAD porque no se mueve ni se pinta: solo almacena información que
 * luego RANKING puede cargar, ordenar, filtrar y desplegar.
 */

#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class REGISTRO{
    private:
        string nombre;
        int puntos, asteroides, enemigos, duracion; // duracion en segundos
    public:
        REGISTRO(string, int, int, int, int);
        string getNombre() const;
        int getPuntos() const;
        int getAsteroides() const;
        int getEnemigos() const;
        int getDuracion() const;
        string aCSV() const;
        void mostrar(int pos) const;
        static void encabezado();
};

/**
 * Constructor. Limpia el nombre para que nunca rompa el formato CSV
 * (sin comas ni saltos de línea), lo recorta a 14 caracteres y, si queda
 * vacío, lo cambia por "Anonimo".
 *
 * @param n nombre, p puntos, a asteroides destruidos, e enemigos derrotados,
 * d duración de la partida en segundos
 */
REGISTRO::REGISTRO(string n, int p, int a, int e, int d)
    : puntos(p), asteroides(a), enemigos(e), duracion(d){
    for(size_t i = 0; i < n.size(); i++){
        if(n[i] == ',' || n[i] == '\n' || n[i] == '\r') n[i] = ' ';
    }
    // Quita espacios al inicio y al final
    size_t ini = n.find_first_not_of(' ');
    size_t fin = n.find_last_not_of(' ');
    n = (ini == string::npos) ? "" : n.substr(ini, fin - ini + 1);
    if(n.size() > 14) n = n.substr(0, 14);
    if(n.empty()) n = "Anonimo";
    nombre = n;
}

string REGISTRO::getNombre() const { return nombre; }
int REGISTRO::getPuntos() const { return puntos; }
int REGISTRO::getAsteroides() const { return asteroides; }
int REGISTRO::getEnemigos() const { return enemigos; }
int REGISTRO::getDuracion() const { return duracion; }

/** aCSV regresa el registro como una línea: nombre,puntos,asteroides,enemigos,duracion */
string REGISTRO::aCSV() const{
    return nombre + "," + to_string(puntos) + "," + to_string(asteroides) + "," +
           to_string(enemigos) + "," + to_string(duracion);
}

/** encabezado imprime los títulos de la tabla (mismos anchos que mostrar). */
void REGISTRO::encabezado(){
    cout << right << setw(3) << "#" << "  "
         << left  << setw(14) << "NOMBRE"
         << right << setw(8) << "PUNTOS"
         << setw(6) << "AST"
         << setw(6) << "ENEM"
         << setw(10) << "TIEMPO(s)" << "\n";
    cout << string(47, '-') << "\n";
}

/** mostrar imprime el registro como una fila de la tabla. */
void REGISTRO::mostrar(int pos) const{
    cout << right << setw(3) << pos << "  "
         << left  << setw(14) << nombre
         << right << setw(8) << puntos
         << setw(6) << asteroides
         << setw(6) << enemigos
         << setw(10) << duracion << "\n";
}

#endif
