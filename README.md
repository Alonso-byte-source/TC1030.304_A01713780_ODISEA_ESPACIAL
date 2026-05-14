# TC1030.304_A01713780_ODISEA_ESPACIAL
# Odisea Espacial
# Space Survivor 🚀

## Descripción del proyecto

**Odisea Espacial** es un videojuego tipo arcade desarrollado en C++ bajo el paradigma de Programación Orientada a Objetos (POO). El jugador controla una nave espacial dentro de una pantalla 2D representada en consola ASCII, donde deberá esquivar asteroides, enfrentarse a enemigos y sobrevivir el mayor tiempo posible mientras obtiene puntos.

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
| `Bala` | Proyectiles disparados por la nave |
| `Enemigo` | Entidades hostiles con comportamiento propio |
| `Renderer` | Maneja la representación visual en consola |
| `Juego` | Controla la lógica principal y el game loop |

---

## Características planeadas

- Movimiento de la nave
- Sistema de disparos
- Colisiones
- Sistema de puntuación
- Enemigos con distintos comportamientos
- Generación dinámica de obstáculos
- HUD con vidas y score
