#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"
#include "piezas.h"


void inicializar_juego(EstadoJuego *juego) {
    
    inicializar_tablero(juego->tablero);
    
   
    juego->turno = BLANCO;
    
    
    juego->estado = JUGANDO;
}


int procesar_turno(EstadoJuego *juego, char *entrada) {
   
    char origen_str[3], destino_str[3];
    
    
    if (sscanf(entrada, "%s %s", origen_str, destino_str) != 2) {
        printf("Formato invalido. Use: 'e2 e4'\n");
        return 0;
    }
    
    
    Posicion origen = convertir_notacion(origen_str);
    Posicion destino = convertir_notacion(destino_str);
    
    
    Movimiento mov;
    mov.origen = origen;
    mov.destino = destino;
   
    char pieza = juego->tablero[origen.fila][origen.columna];
    if ((juego->turno == BLANCO && !es_pieza_blanca(pieza)) || 
        (juego->turno == NEGRO && !es_pieza_negra(pieza))) {
        printf("No puedes mover las piezas del oponente.\n");
        return 0;
    }
    
    
    if (!es_movimiento_valido(juego->tablero, mov)) {
        printf("Movimiento invalido.\n");
        return 0;
    }
    
  
    ejecutar_movimiento(juego->tablero, mov);
    

    if (hay_jaque(juego)) {
        juego->estado = JAQUE;
        
        
        if (hay_jaque_mate(juego)) {
            juego->estado = JAQUE_MATE;
            return 1;
        }
        
        printf("¡Jaque!\n");
    } else {
        juego->estado = JUGANDO;
    }
    
    cambiar_turno(juego);
    
    return 1;
}

// Verifica si hay jaque
int hay_jaque(EstadoJuego *juego) {
    // Esta es una implementación simplificada
    // En un juego real, se verificaría si el rey está bajo amenaza
    
    // Buscar la posición del rey del jugador actual
    char rey = (juego->turno == BLANCO) ? 'R' : 'r';
    Posicion pos_rey = {0, 0};
    int encontrado = 0;
    
    for (int i = 1; i < FILAS-1 && !encontrado; i++) {
        for (int j = 1; j < COLUMNAS-1 && !encontrado; j++) {
            if (juego->tablero[i][j] == rey) {
                pos_rey.fila = i;
                pos_rey.columna = j;
                encontrado = 1;
            }
        }
    }
    
    // Para simplificar, asumimos que no hay jaque
    // En una implementación completa, se verificaría si alguna pieza enemiga
    // puede moverse a la posición del rey
    return 0;
}

// Verifica si hay jaque mate
int hay_jaque_mate(EstadoJuego *juego) {
    // Esta es una implementación simplificada
    // En un juego real, se verificaría si el rey está en jaque y no puede moverse
    // ni ser defendido
    
    // Para simplificar, asumimos que no hay jaque mate
    return 0;
}

// Cambia el turno al siguiente jugador
void cambiar_turno(EstadoJuego *juego) {
    juego->turno = (juego->turno == BLANCO) ? NEGRO : BLANCO;
}

void mostrar_estado_juego(EstadoJuego *juego) {
    
    mostrar_tablero(juego->tablero);
    
    
    printf("\nTurno de las %s\n", (juego->turno == BLANCO) ? "BLANCAS" : "NEGRAS");
    
    
    switch (juego->estado) {
        case JAQUE:
            printf("¡JAQUE!\n");
            break;
        case JAQUE_MATE:
            printf("¡JAQUE MATE! Ganan las %s\n", (juego->turno == BLANCO) ? "NEGRAS" : "BLANCAS");
            break;
        case TABLAS:
            printf("¡TABLAS!\n");
            break;
    }
}
