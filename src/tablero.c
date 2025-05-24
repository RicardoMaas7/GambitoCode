#include <stdio.h>
#define FILAS 10
#define COLUMNAS 10

void limpiar_tablero(char tablero[FILAS][COLUMNAS]) {
    printf("DEBUG: Limpiando tablero\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = ' ';
        }
    }
}

void inicializar_tablero(char tablero[FILAS][COLUMNAS]) {
    // Primero limpiamos el tablero
    limpiar_tablero(tablero);
    printf("DEBUG: Inicializando tablero\n");

    // Colocamos las coordenadas en los bordes
    char letras[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', ' '};
    char numeros[] = {' ', '8', '7', '6', '5', '4', '3', '2', '1', ' '};

    // Letras en la parte superior e inferior
    for (int j = 0; j < COLUMNAS; j++) {
        tablero[0][j] = letras[j];
        tablero[FILAS-1][j] = letras[j];
    }

    // Números en los laterales
    for (int i = 0; i < FILAS; i++) {
        tablero[i][0] = numeros[i];
        tablero[i][COLUMNAS-1] = numeros[i];
    }

    // Colocamos peones blancos y negros (CORREGIDO)
    for (int j = 1; j < COLUMNAS-1; j++) {
        tablero[2][j] = 'p'; // Peones negros (fila 7) p minuscula
        tablero[7][j] = 'P'; // Peones blancos (fila 2) P mayuscula
    }

    // Colocamos las piezas negras (fila 8) - CORREGIDO
    tablero[1][1] = 't'; // Torre
    tablero[1][8] = 't';
    tablero[1][2] = 'c'; // Caballo
    tablero[1][7] = 'c';
    tablero[1][3] = 'a'; // Alfil
    tablero[1][6] = 'a';
    tablero[1][4] = 'd'; // Dama
    tablero[1][5] = 'r'; // Rey

    // Colocamos las piezas blancas (fila 1) - CORREGIDO
    tablero[8][1] = 'T'; // Torre
    tablero[8][8] = 'T';
    tablero[8][2] = 'C'; // Caballo
    tablero[8][7] = 'C';
    tablero[8][3] = 'A'; // Alfil
    tablero[8][6] = 'A';
    tablero[8][4] = 'D'; // Dama
    tablero[8][5] = 'R'; // Rey
}

void mostrar_tablero(char tablero[FILAS][COLUMNAS]) {
    printf("\n  +---+---+---+---+---+---+---+---+---+---+\n");

    for (int i = 0; i < FILAS; i++) {
        printf("  |");
        for (int j = 0; j < COLUMNAS; j++) {
            printf(" %c |", tablero[i][j]);
        }
        printf("\n  +---+---+---+---+---+---+---+---+---+---+\n");
    }
}

void colocar_pieza(char tablero[FILAS][COLUMNAS], int fila, int columna, char pieza) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        printf("DEBUG: Colocando pieza '%c' en [%d,%d]\n", pieza, fila, columna);
        tablero[fila][columna] = pieza;
    }
}

char obtener_pieza(char tablero[FILAS][COLUMNAS], int fila, int columna) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        return tablero[fila][columna];
    }
    return ' '; // Retornar espacio si las coordenadas están fuera de rango
}

