#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movimientos.h"
#include "tablero.h"

// Función para convertir notación algebraica a posición (ej: "e4" -> fila, columna)
Posicion convertir_notacion(char *notacion) {
    Posicion pos;
    
    // Validar la entrada
    if (strlen(notacion) < 2 || 
        notacion[0] < 'a' || notacion[0] > 'h' || 
        notacion[1] < '1' || notacion[1] > '8') {
        // Valores por defecto en caso de error
        pos.fila = -1;
        pos.columna = -1;
        printf("DEBUG: Notación inválida: %s\n", notacion);
        return pos;
    }
    
    // La columna es la primera letra (a-h -> 1-8)
    pos.columna = notacion[0] - 'a' + 1;
    
    // La fila es el segundo carácter (1-8 -> 8-1)
    pos.fila = '9' - notacion[1];
    
    printf("DEBUG: Notación: %s -> Fila: %d, Columna: %d\n", notacion, pos.fila, pos.columna);
    
    return pos;
}

// Función para verificar si un movimiento es válido para una pieza específica
int es_movimiento_valido(char tablero[10][10], Movimiento mov) {
    char pieza = tablero[mov.origen.fila][mov.origen.columna];
    
    // Verificar que la posición de origen tenga una pieza
    if (es_casilla_vacia(pieza)) {
        printf("DEBUG: No hay pieza en la posición de origen [%d,%d]\n", 
               mov.origen.fila, mov.origen.columna);
        return 0;
    }
    
    // Verificar que la posición de destino no tenga una pieza del mismo color
    char pieza_destino = tablero[mov.destino.fila][mov.destino.columna];
    if (!es_casilla_vacia(pieza_destino) && son_del_mismo_color(pieza, pieza_destino)) {
        printf("DEBUG: Hay una pieza del mismo color en la posición de destino\n");
        return 0;
    }
    
    // Validar según el tipo de pieza
    int resultado = 0;
    switch (obtener_tipo_pieza(pieza)) {
        case PEON:
            resultado = validar_movimiento_peon(tablero, mov);
            break;
        case TORRE:
            resultado = validar_movimiento_torre(tablero, mov);
            break;
        case CABALLO:
            resultado = validar_movimiento_caballo(tablero, mov);
            break;
        case ALFIL:
            resultado = validar_movimiento_alfil(tablero, mov);
            break;
        case DAMA:
            resultado = validar_movimiento_dama(tablero, mov);
            break;
        case REY:
            resultado = validar_movimiento_rey(tablero, mov);
            break;
        default:
            resultado = 0;
    }
    
    printf("DEBUG: Validación de movimiento para pieza '%c': %s\n", 
           pieza, resultado ? "VÁLIDO" : "INVÁLIDO");
    return resultado;
}

// Función para validar movimiento de peón
int validar_movimiento_peon(char tablero[10][10], Movimiento mov) {
    char pieza = tablero[mov.origen.fila][mov.origen.columna];
    int direccion = es_pieza_blanca(pieza) ? -1 : 1; // Blancas suben, negras bajan
    int fila_inicial = es_pieza_blanca(pieza) ? 7 : 2; // Fila inicial para peones
    
    // Movimiento hacia adelante (1 casilla)
    if (mov.origen.columna == mov.destino.columna && 
        mov.destino.fila == mov.origen.fila + direccion && 
        es_casilla_vacia(tablero[mov.destino.fila][mov.destino.columna])) {
        return 1;
    }
    
    // Movimiento inicial (2 casillas)
    if (mov.origen.fila == fila_inicial && 
        mov.origen.columna == mov.destino.columna && 
        mov.destino.fila == mov.origen.fila + 2 * direccion && 
        es_casilla_vacia(tablero[mov.origen.fila + direccion][mov.origen.columna]) && 
        es_casilla_vacia(tablero[mov.destino.fila][mov.destino.columna])) {
        return 1;
    }
    
    // Captura en diagonal
    if (mov.destino.fila == mov.origen.fila + direccion && 
        (mov.destino.columna == mov.origen.columna + 1 || mov.destino.columna == mov.origen.columna - 1) && 
        !es_casilla_vacia(tablero[mov.destino.fila][mov.destino.columna]) && 
        !son_del_mismo_color(pieza, tablero[mov.destino.fila][mov.destino.columna])) {
        return 1;
    }
    
    return 0;
}

// Función para validar movimiento de torre
int validar_movimiento_torre(char tablero[10][10], Movimiento mov) {
    // La torre se mueve en línea recta (horizontal o vertical)
    if (mov.origen.fila != mov.destino.fila && mov.origen.columna != mov.destino.columna) {
        return 0;
    }
    
    int i, j;
    
    // Movimiento horizontal
    if (mov.origen.fila == mov.destino.fila) {
        int inicio = (mov.origen.columna < mov.destino.columna) ? mov.origen.columna + 1 : mov.destino.columna + 1;
        int fin = (mov.origen.columna < mov.destino.columna) ? mov.destino.columna : mov.origen.columna;
        
        for (j = inicio; j < fin; j++) {
            if (!es_casilla_vacia(tablero[mov.origen.fila][j])) {
                return 0;
            }
        }
    }
    // Movimiento vertical
    else {
        int inicio = (mov.origen.fila < mov.destino.fila) ? mov.origen.fila + 1 : mov.destino.fila + 1;
        int fin = (mov.origen.fila < mov.destino.fila) ? mov.destino.fila : mov.origen.fila;
        
        for (i = inicio; i < fin; i++) {
            if (!es_casilla_vacia(tablero[i][mov.origen.columna])) {
                return 0;
            }
        }
    }
    
    return 1;
}

// Función para validar movimiento de caballo
int validar_movimiento_caballo(char tablero[10][10], Movimiento mov) {
    // El caballo se mueve en forma de L: 2 casillas en una dirección y 1 en perpendicular
    int dif_fila = (mov.destino.fila > mov.origen.fila) ? 
                   (mov.destino.fila - mov.origen.fila) : 
                   (mov.origen.fila - mov.destino.fila);
                   
    int dif_columna = (mov.destino.columna > mov.origen.columna) ? 
                      (mov.destino.columna - mov.origen.columna) : 
                      (mov.origen.columna - mov.destino.columna);
    
    return (dif_fila == 2 && dif_columna == 1) || (dif_fila == 1 && dif_columna == 2);
}

// Función para validar movimiento de alfil
int validar_movimiento_alfil(char tablero[10][10], Movimiento mov) {
    // El alfil se mueve en diagonal
    int dif_fila = mov.destino.fila - mov.origen.fila;
    int dif_columna = mov.destino.columna - mov.origen.columna;
    
    // Verificar que el movimiento sea diagonal
    if (abs(dif_fila) != abs(dif_columna)) {
        printf("DEBUG: Movimiento no diagonal para alfil\n");
        return 0;
    }
    
    // Determinar la dirección del movimiento
    int dir_fila = (dif_fila > 0) ? 1 : -1;
    int dir_columna = (dif_columna > 0) ? 1 : -1;
    
    // Verificar que no haya piezas en el camino
    int i = mov.origen.fila + dir_fila;
    int j = mov.origen.columna + dir_columna;
    
    while (i != mov.destino.fila) {
        printf("DEBUG: Verificando casilla [%d,%d] en camino del alfil\n", i, j);
        if (!es_casilla_vacia(tablero[i][j])) {
            printf("DEBUG: Hay una pieza en el camino del alfil en [%d,%d]\n", i, j);
            return 0;
        }
        i += dir_fila;
        j += dir_columna;
    }
    
    return 1;
}

// Función para validar movimiento de dama
int validar_movimiento_dama(char tablero[10][10], Movimiento mov) {
    // La dama combina los movimientos de la torre y el alfil
    return validar_movimiento_torre(tablero, mov) || validar_movimiento_alfil(tablero, mov);
}

// Función para validar movimiento de rey
int validar_movimiento_rey(char tablero[10][10], Movimiento mov) {
    // El rey se mueve una casilla en cualquier dirección
    int dif_fila = (mov.destino.fila > mov.origen.fila) ? 
                   (mov.destino.fila - mov.origen.fila) : 
                   (mov.origen.fila - mov.destino.fila);
                   
    int dif_columna = (mov.destino.columna > mov.origen.columna) ? 
                      (mov.destino.columna - mov.origen.columna) : 
                      (mov.origen.columna - mov.destino.columna);
    
    return dif_fila <= 1 && dif_columna <= 1;
}

// Función para ejecutar un movimiento en el tablero
void ejecutar_movimiento(char tablero[10][10], Movimiento mov) {
    char pieza = tablero[mov.origen.fila][mov.origen.columna];
    
    printf("DEBUG: Moviendo pieza '%c' de [%d,%d] a [%d,%d]\n", 
           pieza, mov.origen.fila, mov.origen.columna, 
           mov.destino.fila, mov.destino.columna);
    
    // Mover la pieza a la posición de destino
    tablero[mov.destino.fila][mov.destino.columna] = pieza;
    
    // Dejar vacía la posición de origen
    tablero[mov.origen.fila][mov.origen.columna] = ' ';
}
