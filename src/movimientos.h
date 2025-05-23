#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

#include "piezas.h"

// Estructura para representar una posición en el tablero
typedef struct {
    int fila;
    int columna;
} Posicion;

// Estructura para representar un movimiento
typedef struct {
    Posicion origen;
    Posicion destino;
} Movimiento;

// Función para convertir notación algebraica a posición (ej: "e4" -> fila, columna)
Posicion convertir_notacion(char *notacion);

// Función para verificar si un movimiento es válido para una pieza específica
int es_movimiento_valido(char tablero[10][10], Movimiento mov);

// Funciones específicas para validar movimientos de cada tipo de pieza
int validar_movimiento_peon(char tablero[10][10], Movimiento mov);
int validar_movimiento_torre(char tablero[10][10], Movimiento mov);
int validar_movimiento_caballo(char tablero[10][10], Movimiento mov);
int validar_movimiento_alfil(char tablero[10][10], Movimiento mov);
int validar_movimiento_dama(char tablero[10][10], Movimiento mov);
int validar_movimiento_rey(char tablero[10][10], Movimiento mov);

// Función para ejecutar un movimiento en el tablero
void ejecutar_movimiento(char tablero[10][10], Movimiento mov);

#endif // MOVIMIENTOS_H