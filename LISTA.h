/**
 * Proyecto Odisea Espacial clase LISTA<T>
 * Alonso Vega Reséndiz
 * A01713780
 * version : 2
 *
 * LISTA<T> es una lista doblemente enlazada genérica (plantilla) hecha a mano.
 * Cada nodo guarda un dato y apunta al nodo anterior y al siguiente.
 *
 * También implementa tres algoritmos de ordenamiento que reciben un
 * comparador "antes(a, b)" (true si a debe ir antes que b). La lista no
 * conoce el criterio: quien la usa decide cómo comparar.
 */

#ifndef LISTA_H
#define LISTA_H

#include <utility> // std::swap

template <typename T>
class LISTA{
    private:
        // Nodo de la lista
        struct NODO{
            T dato;
            NODO* sig;
            NODO* ant;
            NODO(const T& d) : dato(d), sig(nullptr), ant(nullptr) {}
        };

        NODO* cabeza; // Primer nodo
        NODO* cola;   // Último nodo
        int n;        // Cantidad de nodos

        /**
         * insertarNodo engancha un nodo ya creado en su lugar dentro de una
         * lista ordenada. Recorre desde el final hacia atrás mientras el nodo
         * deba ir antes; así los empates quedan en su orden original (estable).
         */
        template <typename F>
        void insertarNodo(NODO* nodo, F& antes){
            NODO* p = cola;
            while(p != nullptr && antes(nodo->dato, p->dato)){
                p = p->ant;
            }
            if(p == nullptr){ // Va al inicio
                nodo->ant = nullptr;
                nodo->sig = cabeza;
                if(cabeza != nullptr) cabeza->ant = nodo;
                else cola = nodo;
                cabeza = nodo;
            }
            else{ // Va justo después de p
                nodo->ant = p;
                nodo->sig = p->sig;
                if(p->sig != nullptr) p->sig->ant = nodo;
                else cola = nodo;
                p->sig = nodo;
            }
        }

        /** mezclarNodos une dos cadenas ya ordenadas relinkando nodos (sin copiar datos). */
        template <typename F>
        NODO* mezclarNodos(NODO* a, NODO* b, F& antes){
            NODO* ini = nullptr;
            NODO* fin = nullptr;
            while(a != nullptr && b != nullptr){
                NODO* tomar;
                // Solo se toma de b si b va estrictamente antes (estable)
                if(antes(b->dato, a->dato)){ tomar = b; b = b->sig; }
                else                       { tomar = a; a = a->sig; }
                if(ini == nullptr) ini = tomar;
                else fin->sig = tomar;
                fin = tomar;
            }
            NODO* resto = (a != nullptr) ? a : b;
            if(ini == nullptr) return resto;
            fin->sig = resto;
            return ini;
        }

        /** mergeNodos parte la cadena a la mitad, ordena cada mitad y las mezcla. */
        template <typename F>
        NODO* mergeNodos(NODO* h, F& antes){
            if(h == nullptr || h->sig == nullptr) return h;
            // Encuentra la mitad con dos punteros (lento avanza 1, rápido avanza 2)
            NODO* lento = h;
            NODO* rapido = h->sig;
            while(rapido != nullptr && rapido->sig != nullptr){
                lento = lento->sig;
                rapido = rapido->sig->sig;
            }
            NODO* mitad = lento->sig;
            lento->sig = nullptr;
            NODO* izq = mergeNodos(h, antes);
            NODO* der = mergeNodos(mitad, antes);
            return mezclarNodos(izq, der, antes);
        }

        void copiar(const LISTA& otra){
            for(NODO* p = otra.cabeza; p != nullptr; p = p->sig){
                agregar(p->dato);
            }
        }

    public:
        /**
         * ITER es el iterador de la lista (permite for(auto x : lista)).
         * Se define con plantilla para tener versión normal (T) y de solo
         * lectura (const T).
         */
        template <typename V>
        class ITER{
            friend class LISTA;
            private:
                NODO* actual;
            public:
                ITER(NODO* p = nullptr) : actual(p) {}
                V& operator*() const { return actual->dato; }
                V* operator->() const { return &(actual->dato); }
                ITER& operator++(){ actual = actual->sig; return *this; }
                ITER operator++(int){ ITER copia = *this; actual = actual->sig; return copia; }
                bool operator==(const ITER& o) const { return actual == o.actual; }
                bool operator!=(const ITER& o) const { return actual != o.actual; }
        };
        typedef ITER<T> iterador;
        typedef ITER<const T> iterador_const;

        LISTA() : cabeza(nullptr), cola(nullptr), n(0) {}
        LISTA(const LISTA& otra) : cabeza(nullptr), cola(nullptr), n(0) { copiar(otra); }
        ~LISTA(){ limpiar(); }

        LISTA& operator=(const LISTA& otra){
            if(this != &otra){
                limpiar();
                copiar(otra);
            }
            return *this;
        }

        iterador begin(){ return iterador(cabeza); }
        iterador end(){ return iterador(nullptr); }
        iterador_const begin() const { return iterador_const(cabeza); }
        iterador_const end() const { return iterador_const(nullptr); }

        int tamanio() const { return n; }
        bool vacia() const { return n == 0; }

        /** primero regresa el dato del primer nodo (revisar vacia() antes). */
        T& primero(){ return cabeza->dato; }
        const T& primero() const { return cabeza->dato; }

        /** agregar añade un dato al final de la lista. O(1). */
        void agregar(const T& d){
            NODO* nodo = new NODO(d);
            if(cola == nullptr){
                cabeza = cola = nodo;
            }
            else{
                nodo->ant = cola;
                cola->sig = nodo;
                cola = nodo;
            }
            n++;
        }

        /**
         * eliminar quita el nodo al que apunta el iterador y regresa un
         * iterador al siguiente. No libera lo que apunta el dato si T es un
         * puntero: eso lo hace quien usa la lista (delete *it antes).
         */
        iterador eliminar(iterador it){
            NODO* p = it.actual;
            if(p == nullptr) return end();
            NODO* siguiente = p->sig;
            if(p->ant != nullptr) p->ant->sig = p->sig;
            else cabeza = p->sig;
            if(p->sig != nullptr) p->sig->ant = p->ant;
            else cola = p->ant;
            delete p;
            n--;
            return iterador(siguiente);
        }

        /** limpiar elimina todos los nodos. */
        void limpiar(){
            NODO* p = cabeza;
            while(p != nullptr){
                NODO* sig = p->sig;
                delete p;
                p = sig;
            }
            cabeza = cola = nullptr;
            n = 0;
        }

        /**
         * insertarOrdenado inserta un dato en su lugar dentro de una lista que
         * YA está ordenada con el mismo comparador. Es el paso de "inserción"
         * del insertion sort aplicado a un solo elemento: O(n), sin mover datos.
         *
         * @return posición (0 = primero) donde quedó el dato
         */
        template <typename F>
        int insertarOrdenado(const T& d, F antes){
            NODO* nodo = new NODO(d);
            insertarNodo(nodo, antes);
            n++;
            int pos = 0;
            for(NODO* p = nodo->ant; p != nullptr; p = p->ant) pos++;
            return pos;
        }

        /* ================== ALGORITMOS DE ORDENAMIENTO ================== */

        /**
         * ordenarBurbuja compara nodos vecinos e intercambia sus datos.
         * Cada pasada deja el último elemento en su lugar; si una pasada no
         * cambia nada, termina. O(n²).
         */
        template <typename F>
        void ordenarBurbuja(F antes){
            if(n < 2) return;
            NODO* fin = nullptr;
            bool cambio = true;
            while(cambio && cabeza != fin){
                cambio = false;
                NODO* p = cabeza;
                while(p->sig != fin){
                    if(antes(p->sig->dato, p->dato)){
                        std::swap(p->dato, p->sig->dato);
                        cambio = true;
                    }
                    p = p->sig;
                }
                fin = p;
            }
        }

        /**
         * ordenarInsercion desengancha todos los nodos y los vuelve a
         * enganchar uno por uno en su lugar correcto. O(n²), pero O(n) si ya
         * estaba casi ordenada.
         */
        template <typename F>
        void ordenarInsercion(F antes){
            if(n < 2) return;
            NODO* resto = cabeza;
            cabeza = nullptr;
            cola = nullptr;
            while(resto != nullptr){
                NODO* nodo = resto;
                resto = resto->sig;
                nodo->sig = nullptr;
                nodo->ant = nullptr;
                insertarNodo(nodo, antes);
            }
        }

        /**
         * ordenarMerge divide la lista a la mitad recursivamente y mezcla las
         * mitades relinkando nodos. O(n log n), sin memoria extra de datos.
         */
        template <typename F>
        void ordenarMerge(F antes){
            if(n < 2) return;
            cabeza = mergeNodos(cabeza, antes);
            // mergeNodos solo arregla los enlaces "sig": se reconstruyen "ant" y cola
            NODO* previo = nullptr;
            for(NODO* p = cabeza; p != nullptr; p = p->sig){
                p->ant = previo;
                previo = p;
            }
            cola = previo;
        }
};

#endif
