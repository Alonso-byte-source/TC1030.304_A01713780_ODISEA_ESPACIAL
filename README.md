# TC1030.304_A01713780_ODISEA_ESPACIAL
# Odisea Espacial

## Descripción del proyecto

**Odisea Espacial** es un videojuego tipo arcade desarrollado en C++ bajo el paradigma de Programación Orientada a Objetos (POO), el cual rinde homenaje a los grandes clásicos del género arcade, busca combinar las mecánicas fundamentales de posicionamiento de **Galaga**, con el ritmo frenético e intensidad táctica inspirada en la icónica misión final de **Metal Slug 3**.

El jugador controla una nave espacial dentro de una pantalla 2D representada en consola, donde deberá esquivar asteroides, enfrentarse a enemigos y sobrevivir el mayor tiempo posible mientras obtiene puntos.

Además, el juego cuenta con un **ranking de partidas** que se guarda en un archivo, se carga al iniciar el programa y se puede ordenar, filtrar y consultar desde un menú.

El proyecto tiene como objetivo aplicar conceptos fundamentales de POO como:

- Herencia
- Polimorfismo run-time
- Encapsulación
- Abstracción
- Composición y agregación

Y, en su versión final, también:

- Estructuras de datos propias (lista doblemente enlazada genérica)
- Algoritmos de ordenamiento (burbuja, inserción y merge sort)
- Persistencia de datos en archivos (carga, consulta y guardado)

---

## Idea principal

El jugador controla una nave (`Nave`) capaz de moverse y disparar proyectiles (`Bala`) para destruir enemigos (`Enemigo`) y evitar colisiones con asteroides (`Asteroide`).

Todos los objetos interactivos del juego derivan de una clase abstracta llamada `Entidad`.

El juego funciona mediante un **game loop** que:

1. Actualiza entidades
2. Detecta colisiones
3. Genera nuevos enemigos y asteroides
4. Renderiza el estado actual en consola

Al terminar una partida, el programa pide el nombre del jugador, guarda el resultado en `ranking.csv` y muestra la posición obtenida junto con el Top 5.

---

## Clases principales

| Clase | Función |
|---|---|
| `Entidad` | Clase base abstracta para todos los objetos del juego |
| `Nave` | La controla el jugador |
| `Asteroide` | Obstáculos que se desplazan por la pantalla |
| `Bala` | Proyectiles disparados por la nave y el enemigo |
| `Enemigo` | Entidades hostiles con comportamiento propio; reaparecen en cada oleada |
| `Console` | Funciones auxiliares de consola (posicionar el cursor, teclado, pausas), usadas por las demás clases |
| `Juego` | Controla la lógica principal y el game loop, y lleva las estadísticas de la partida |
| `Lista<T>` | **Nueva.** Lista doblemente enlazada genérica hecha a mano; incluye los algoritmos de ordenamiento |
| `Registro` | **Nueva.** Guarda los datos de una partida terminada (nombre, puntos, asteroides, enemigos y duración) |
| `Ranking` | **Nueva.** Guarda los registros en una `Lista<Registro>`; carga, guarda, ordena, filtra y despliega la información |

El diagrama completo está en [`UML_Odisea_Espacial.pdf`](UML_Odisea_Espacial.pdf). Lo nuevo respecto al diagrama anterior aparece en azul.

---

## Características planeadas

- Movimiento de la nave
- Sistema de disparos
- Colisiones
- Sistema de puntuación
- HUD con vidas y score

## Características agregadas

- Enemigo que reaparece en cada oleada, con su contador de enemigos derrotados
- Estadísticas por partida: puntos, asteroides destruidos, enemigos derrotados y duración
- Ranking de partidas guardado en `ranking.csv`
- Récord en pantalla durante la partida, con aviso `** NUEVO RECORD! **` al superarlo
- Posición final y Top 5 al terminar la partida
- Menú principal (jugar, ver ranking, salir)
- Ordenamiento del ranking por puntos, nombre, asteroides, enemigos o duración, eligiendo el algoritmo
- Filtros por puntos mínimos, por nombre de jugador y top N
- Datos de prueba generados en memoria para comparar los algoritmos

---

## Estructura de datos y algoritmos

### Lista doblemente enlazada (`Lista<T>`)

Cada nodo guarda un dato y apunta al nodo anterior y al siguiente. Se eligió porque el juego agrega y elimina elementos todo el tiempo (balas, asteroides, partidas del ranking):

- Eliminar un nodo es O(1) y se puede hacer mientras se recorre la lista.
- Insertar en el lugar correcto de una lista ordenada no obliga a mover los demás datos.
- Es una plantilla, así que la misma clase guarda `Registro`, `Bala*`, `Asteroide*` y `Entidad*`.

Se usa en `Juego` (asteroides, balas del jugador, balas del enemigo y entidades) y en `Ranking` (registros).

### Algoritmos de ordenamiento

Los tres están implementados dentro de `Lista<T>` y reciben un comparador, por lo que la lista no conoce el criterio de orden. La función `Ranking::antes` es la que decide cómo se compara según el atributo elegido.

| Algoritmo | Complejidad | Comparaciones con 2000 registros de prueba |
|---|---|---|
| Burbuja | O(n²) | ≈ 2,000,000 |
| Inserción | O(n²) | ≈ 1,000,000 |
| Merge sort | O(n log n) | ≈ 19,000 |

Los tres son estables: los empates conservan su orden original. El menú muestra cuántas comparaciones hizo el último ordenamiento.

### Dónde se usa el ordenamiento

- El ranking se ordena por puntos al cargar el archivo.
- Cada partida nueva se inserta directamente en su lugar (`insertarOrdenado`), sin reordenar todo.
- Como el primero de la lista es el mejor, el juego muestra el récord durante la partida y calcula la posición del jugador al terminar.
- Desde el menú se puede reordenar una copia del ranking por cualquier otro atributo.

---

## Archivo de datos

El ranking se guarda en `ranking.csv`, junto al ejecutable, con una partida por línea:

```
nombre,puntos,asteroides,enemigos,duracion
Alonso,250,30,4,185
```

- Si el archivo no existe, el programa inicia con el ranking vacío y lo crea al terminar la primera partida.
- Las líneas con formato incorrecto se ignoran al cargar.
- Cada partida terminada se agrega al final del archivo.
- La duración está en segundos. El nombre se recorta a 14 caracteres y no puede contener comas.

---

## Controles

### Durante el juego

| Botón | Acción |
|---|---|
| <center>**a**</center> | Desplaza la nave hacia la izquierda |
| <center>**d**</center> | Desplaza la nave hacia la derecha |
| <center>**s**</center> | Desplaza la nave hacia abajo |
| <center>**w**</center> | Desplaza la nave hacia arriba |
| <center>**barra espaciadora**</center> | Dispara los proyectiles |

### En los menús

Se elige la opción escribiendo su número y presionando **Enter**.

| Menú | Opciones |
|---|---|
| Principal | 1) Jugar, 2) Ver ranking, 3) Salir |
| Ranking | 1) Ordenar, 2) Filtrar por puntos mínimos, 3) Filtrar por nombre, 4) Top N, 5) Restablecer, 6) Datos de prueba, 0) Volver |

---

## Archivos del proyecto

| Archivo | Contenido |
|---|---|
| `main.cpp` | Menú principal y menú del ranking |
| `JUEGO.h` | Clase `Juego` (game loop, colisiones, estadísticas) |
| `ENTIDAD.h`, `NAVE.h`, `ASTEROIDE.h`, `BALA.h`, `ENEMIGO.h` | Jerarquía de objetos del juego |
| `CONSOLE.h` | Funciones auxiliares de consola (Windows y Linux/Mac) |
| `LISTA.h` | Lista doblemente enlazada y algoritmos de ordenamiento |
| `REGISTRO.h` | Datos de una partida |
| `RANKING.h` | Carga, guardado, ordenamiento, filtros y despliegue |
| `ranking.csv` | Datos del ranking (se crea o se actualiza al jugar) |

---

## Ejecución

Ejecutar en consola externa.

Compilar con un compilador compatible con C++11 o superior (por ejemplo, g++):

```
g++ -std=c++17 main.cpp -o juego
```

Y ejecutar desde la carpeta donde está `ranking.csv`:

```
./juego        (Linux / Mac)
juego.exe      (Windows)
```
