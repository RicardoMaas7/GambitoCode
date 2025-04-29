#ifndef TABLERO_H
#define TABLERO_H

#include "tablero.c"
// Definiciones para el tablero

// Inicializa el tablero con las posiciones iniciales
void inicializar_tablero(char tablero[FILAS][COLUMNAS]);

// Muestra el tablero en consola
void mostrar_tablero(char tablero[FILAS][COLUMNAS]);

// Funciones adicionales para manipular el tablero
void limpiar_tablero(char tablero[FILAS][COLUMNAS]);
void colocar_pieza(char tablero[FILAS][COLUMNAS], int fila, int columna, char pieza);
char obtener_pieza(char tablero[FILAS][COLUMNAS], int fila, int columna);

#endif // TABLERO_H