/**
 * Proyecto Odisea Espacial clase RANKING
 * Alonso Vega Reséndiz
 * A01713780
 * version : 2
 *
 * La clase RANKING guarda los REGISTRO de las partidas en una lista
 * doblemente enlazada propia (LISTA<REGISTRO>) y concentra las operaciones:
 *   - Cargar y guardar la información en un archivo CSV.
 *   - Ordenar por distintos atributos con los algoritmos de LISTA
 *     (burbuja, inserción y merge sort).
 *   - Mantener el ranking ordenado por puntos: cada partida nueva se inserta
 *     en su lugar (insertarOrdenado), así el primero siempre es el récord.
 *   - Filtrar (puntos mínimos, nombre de jugador, top N) y desplegar tablas.
 */

#ifndef RANKING_H
#define RANKING_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include "LISTA.h"
#include "REGISTRO.h"

using namespace std;

// Atributo por el cual se ordena
enum CRITERIO { POR_PUNTOS = 1, POR_NOMBRE, POR_ASTEROIDES, POR_ENEMIGOS, POR_DURACION };
// Algoritmo de ordenamiento a utilizar
enum ALGORITMO { BURBUJA = 1, INSERCION, MERGE };

class RANKING{
    private:
        LISTA<REGISTRO> registros;
        long comparaciones; // Cuenta las comparaciones del último ordenamiento

        string minusculas(string s) const;
        bool antes(const REGISTRO&, const REGISTRO&, CRITERIO);
    public:
        RANKING();
        // Carga y guardado
        int cargar(const string&);
        bool guardar(const string&) const;
        bool anexar(const REGISTRO&, const string&) const;
        void agregar(const REGISTRO&);
        // Ordenamiento
        void ordenar(CRITERIO, ALGORITMO);
        int insertarOrdenado(const REGISTRO&);
        bool primero(string&, int&) const;
        // Filtros y despliegue
        RANKING filtrarPorPuntos(int) const;
        RANKING filtrarPorNombre(const string&) const;
        RANKING top(int) const;
        void mostrar() const;
        // Utilidades
        int tamanio() const;
        long getComparaciones() const;
        void generarPrueba(int);
};

RANKING::RANKING() : comparaciones(0) {}

int RANKING::tamanio() const { return registros.tamanio(); }
long RANKING::getComparaciones() const { return comparaciones; }

/** agregar añade un registro al final (sin ordenar). */
void RANKING::agregar(const REGISTRO& r){
    registros.agregar(r);
}

/* ===================== CARGA Y GUARDADO ===================== */

/**
 * cargar lee el archivo CSV y crea un REGISTRO por cada línea válida.
 * Si el archivo no existe, el ranking queda vacío (no es un error).
 * Las líneas con formato incorrecto se ignoran. Los registros quedan en el
 * orden del archivo: llama a ordenar() después si los necesitas ordenados.
 *
 * @return cantidad de registros cargados
 */
int RANKING::cargar(const string& archivo){
    registros.limpiar();
    ifstream in(archivo);
    if(!in.is_open()) return 0;

    string linea;
    while(getline(in, linea)){
        if(!linea.empty() && linea[linea.size()-1] == '\r') linea.erase(linea.size()-1); // CSV hecho en Windows
        if(linea.empty()) continue;

        // Separa la línea por comas
        vector<string> campos;
        stringstream ss(linea);
        string campo;
        while(getline(ss, campo, ',')) campos.push_back(campo);
        if(campos.size() != 5) continue;

        try{
            int p = stoi(campos[1]);
            int a = stoi(campos[2]);
            int e = stoi(campos[3]);
            int d = stoi(campos[4]);
            if(p < 0 || a < 0 || e < 0 || d < 0) continue;
            registros.agregar(REGISTRO(campos[0], p, a, e, d));
        }
        catch(...){
            continue; // Alguno de los campos numéricos no era un número
        }
    }
    return registros.tamanio();
}

/** guardar reescribe el archivo completo con todos los registros. */
bool RANKING::guardar(const string& archivo) const{
    ofstream out(archivo);
    if(!out.is_open()) return false;
    for(auto it = registros.begin(); it != registros.end(); ++it){
        out << it->aCSV() << "\n";
    }
    return true;
}

/** anexar agrega UN registro al final del archivo (sin reescribirlo). */
bool RANKING::anexar(const REGISTRO& r, const string& archivo) const{
    ofstream out(archivo, ios::app);
    if(!out.is_open()) return false;
    out << r.aCSV() << "\n";
    return true;
}

/* ===================== ORDENAMIENTO ===================== */

string RANKING::minusculas(string s) const{
    for(size_t i = 0; i < s.size(); i++) s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

/**
 * antes decide si el registro a debe ir ANTES que b según el criterio.
 * Es la única función que conoce los criterios: la lista y sus algoritmos
 * solo reciben este comparador. Números: de mayor a menor. Nombre: A-Z sin
 * distinguir mayúsculas. Es estricta (empate = false), así los empates
 * conservan su orden original (ordenamiento estable).
 */
bool RANKING::antes(const REGISTRO& a, const REGISTRO& b, CRITERIO c){
    comparaciones++;
    switch(c){
        case POR_PUNTOS:    return a.getPuntos()    > b.getPuntos();
        case POR_NOMBRE:    return minusculas(a.getNombre()) < minusculas(b.getNombre());
        case POR_ASTEROIDES:return a.getAsteroides()> b.getAsteroides();
        case POR_ENEMIGOS:  return a.getEnemigos()  > b.getEnemigos();
        case POR_DURACION:  return a.getDuracion()  > b.getDuracion();
    }
    return false;
}

/**
 * ordenar ordena el ranking por el criterio y algoritmo elegidos.
 * Reinicia el contador de comparaciones para poder comparar algoritmos.
 */
void RANKING::ordenar(CRITERIO c, ALGORITMO alg){
    comparaciones = 0;
    auto cmp = [this, c](const REGISTRO& a, const REGISTRO& b){ return antes(a, b, c); };
    switch(alg){
        case BURBUJA:   registros.ordenarBurbuja(cmp);   break;
        case INSERCION: registros.ordenarInsercion(cmp); break;
        case MERGE:     registros.ordenarMerge(cmp);     break;
    }
}

/**
 * insertarOrdenado mete un registro en su lugar dentro de un ranking que YA
 * está ordenado por puntos. No reordena todo: solo busca el hueco.
 *
 * @return posición en el ranking (1 = primer lugar)
 */
int RANKING::insertarOrdenado(const REGISTRO& r){
    comparaciones = 0;
    auto cmp = [this](const REGISTRO& a, const REGISTRO& b){ return antes(a, b, POR_PUNTOS); };
    return registros.insertarOrdenado(r, cmp) + 1;
}

/**
 * primero entrega el nombre y los puntos del primer registro. Si el ranking
 * está ordenado por puntos, es el récord actual.
 *
 * @return false si el ranking está vacío
 */
bool RANKING::primero(string& nombre, int& puntos) const{
    if(registros.vacia()) return false;
    nombre = registros.primero().getNombre();
    puntos = registros.primero().getPuntos();
    return true;
}

/* ===================== FILTROS ===================== */

/** filtrarPorPuntos regresa un RANKING nuevo solo con las partidas de min puntos o más. */
RANKING RANKING::filtrarPorPuntos(int min) const{
    RANKING r;
    for(auto it = registros.begin(); it != registros.end(); ++it){
        if(it->getPuntos() >= min) r.agregar(*it);
    }
    return r;
}

/** filtrarPorNombre regresa las partidas cuyo nombre contiene el texto (sin distinguir mayúsculas). */
RANKING RANKING::filtrarPorNombre(const string& texto) const{
    RANKING r;
    string buscado = minusculas(texto);
    for(auto it = registros.begin(); it != registros.end(); ++it){
        if(minusculas(it->getNombre()).find(buscado) != string::npos){
            r.agregar(*it);
        }
    }
    return r;
}

/** top regresa los primeros n registros en el orden actual. */
RANKING RANKING::top(int n) const{
    RANKING r;
    int i = 0;
    for(auto it = registros.begin(); it != registros.end() && i < n; ++it, ++i){
        r.agregar(*it);
    }
    return r;
}

/* ===================== DESPLIEGUE Y PRUEBAS ===================== */

/** mostrar imprime la tabla completa. */
void RANKING::mostrar() const{
    if(registros.vacia()){
        cout << "  (No hay registros que mostrar)\n";
        return;
    }
    REGISTRO::encabezado();
    int pos = 1;
    for(auto it = registros.begin(); it != registros.end(); ++it){
        it->mostrar(pos++);
    }
}

/** generarPrueba agrega n registros aleatorios (solo en memoria) para probar los algoritmos. */
void RANKING::generarPrueba(int n){
    const char* nombres[] = {"Luna", "Orion", "Nova", "Vega", "Atlas", "Zeta", "Kira", "Dante", "Mia", "Rex"};
    for(int i = 0; i < n; i++){
        int ast = rand() % 60;
        int ene = rand() % 8;
        int pts = ast * 5 + ene * 5;
        registros.agregar(REGISTRO(nombres[rand() % 10], pts, ast, ene, 30 + rand() % 400));
    }
}

#endif
