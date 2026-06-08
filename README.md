# TC1030.304_A01713780_ODISEA_ESPACIAL
# Odisea Espacial

## Descripción del proyecto

**Odisea Espacial** es un videojuego tipo rcade desarrollado en C++ bajo el paradigma de Programación Orientada objetos (POO), el cual rinde homenaje a los grandes clásicos del género arcade, busca combinar las mecánicas fundamentales de posicionamiento de **Galaga**, con el ritmo frenético e intensidad táctica inspirada en la icónica misión final de **Metal Slug 3**.

El jugador controla una nave espacial dentro de una pantalla 2D representada en consola, donde deberá esquivar asteroides, enfrentarse a enemigos y sobrevivir el mayor tiempo posible mientras obtiene puntos.

El proyecto tiene como objetivo aplicar conceptos fundamentales de POO como:

- Herencia
- Polimorfismo run-time
- Encapsulación
- Abstracción
- Composición y agregación

---

## Idea principal

El jugador controla una nave (`Nave`) capaz de moverse y disparar proyectiles (`Bala`) para destruir enemigos (`Enemigo`) y evitar colisiones con asteroides (`Asteroide`).

Todos los objetos interactivos del juego derivan de una clase abstracta llamada `Entidad`.

El juego funciona mediante un **game loop** que:

1. Actualiza entidades
2. Detecta colisiones
3. Genera nuevos enemigos y asteroides
4. Renderiza el estado actual en consola

---

## Clases principales

| Clase | Función |
|---|---|
| `Entidad` | Clase base abstracta para todos los objetos del juego |
| `Nave` | La controla  eljugador |
| `Asteroide` | Obstáculos que se desplazan por la pantalla |
| `Bala` | Proyectiles disparados por la nave y el enemigo |
| `Enemigo` | Entidades hostiles con comportamiento propio |
| `Renderer` | Maneja la representación visual en consola |
| `Juego` | Controla la lógica principal y el game loop |

---

## Características planeadas

- Movimiento de la nave
- Sistema de disparos
- Colisiones
- Sistema de puntuación
- HUD con vidas y score

---

## Controles
| Botón | Acción |
|---|---|
| <center>**a**</center> | Desplaza la nave hacia la izquierda |
| <center>**d**</center> | Desplaza la nave hacia la derecha |
| <center>**s**</center> | Desplaza la nave hacia abajo |
| <center>**w**</center> | Desplaza la nave hacia arriba |
| <center>**barra espaciadora**</center> | Dipara los proyectiles | 

---

## Ejecución

Ejecutar en consola externa 
