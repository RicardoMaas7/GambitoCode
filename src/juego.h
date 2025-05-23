#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "movimientos.h"

// Constantes para el estado del juego
#define JUGANDO 0
#define JAQUE 1
#define JAQUE_MATE 2
#define TABLAS 3

// Estructura para representar el estado del juego
typedef struct {
    char tablero[FILAS][COLUMNAS];
    int turno;           // BLANCO o NEGRO
    int estado;          // JUGANDO, JAQUE, JAQUE_MATE o TABLAS
} EstadoJuego;

// Inicializa el estado del juego
void inicializar_juego(EstadoJuego *juego);

// Procesa un turno del juego
int procesar_turno(EstadoJuego *juego, char *entrada);

// Verifica si hay jaque
int hay_jaque(EstadoJuego *juego);

// Verifica si hay jaque mate
int hay_jaque_mate(EstadoJuego *juego);

// Cambia el turno al siguiente jugador
void cambiar_turno(EstadoJuego *juego);

// Muestra el estado actual del juego
void mostrar_estado_juego(EstadoJuego *juego);

#endif 
