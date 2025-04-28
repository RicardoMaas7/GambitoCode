#include <stdio.h>
#include "tablero.h"

int main() {
    // Declarar el tablero
    char tablero[FILAS][COLUMNAS];

    // Inicializar el tablero con la posición inicial
    inicializar_tablero(tablero);

    // Mostrar el tablero
    printf("Tablero de ajedrez inicial:\n");
    mostrar_tablero(tablero);

    // Aquí irá el resto de la lógica del juego
    printf("\nJuego de ajedrez en desarrollo...\n");

    return 0;
}