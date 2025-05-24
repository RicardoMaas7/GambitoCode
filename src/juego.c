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

// Función auxiliar para verificar si una posición está siendo atacada
int posicion_atacada(char tablero[FILAS][COLUMNAS], Posicion pos, int por_color) {
    // Verificar ataques de todas las piezas del color especificado
    for (int i = 1; i < FILAS-1; i++) {
        for (int j = 1; j < COLUMNAS-1; j++) {
            char pieza = tablero[i][j];
            
            // Verificar si la pieza pertenece al color atacante
            int es_pieza_atacante = 0;
            if (por_color == BLANCO && es_pieza_blanca(pieza)) es_pieza_atacante = 1;
            if (por_color == NEGRO && es_pieza_negra(pieza)) es_pieza_atacante = 1;
            
            if (!es_pieza_atacante) continue;
            
            // Crear movimiento desde la pieza atacante hacia la posición objetivo
            Movimiento mov_ataque;
            mov_ataque.origen.fila = i;
            mov_ataque.origen.columna = j;
            mov_ataque.destino = pos;
            
            // Verificar si la pieza puede atacar esa posición
            // Guardamos temporalmente la pieza en destino
            char pieza_temporal = tablero[pos.fila][pos.columna];
            
            // Colocamos una pieza enemiga temporal para simular captura
            char pieza_enemiga_temp = (por_color == BLANCO) ? 'p' : 'P';
            tablero[pos.fila][pos.columna] = pieza_enemiga_temp;
            
            // Verificamos si el movimiento es válido
            int puede_atacar = es_movimiento_valido(tablero, mov_ataque);
            
            // Restauramos la pieza original
            tablero[pos.fila][pos.columna] = pieza_temporal;
            
            if (puede_atacar) return 1;
        }
    }
    return 0;
}

// Verifica si hay jaque
int hay_jaque(EstadoJuego *juego) {
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
    
    if (!encontrado) return 0; // No se encontró el rey
    
    // Verificar si el rey está siendo atacado por el oponente
    int color_oponente = (juego->turno == BLANCO) ? NEGRO : BLANCO;
    return posicion_atacada(juego->tablero, pos_rey, color_oponente);
}

// Función auxiliar para verificar si un movimiento deja al rey en jaque
int movimiento_deja_en_jaque(EstadoJuego *juego, Movimiento mov) {
    // Guardar el estado original
    char pieza_origen = juego->tablero[mov.origen.fila][mov.origen.columna];
    char pieza_destino = juego->tablero[mov.destino.fila][mov.destino.columna];
    
    // Ejecutar el movimiento temporalmente
    juego->tablero[mov.destino.fila][mov.destino.columna] = pieza_origen;
    juego->tablero[mov.origen.fila][mov.origen.columna] = ' ';
    
    // Verificar si el rey queda en jaque
    int en_jaque = hay_jaque(juego);
    
    // Restaurar el estado original
    juego->tablero[mov.origen.fila][mov.origen.columna] = pieza_origen;
    juego->tablero[mov.destino.fila][mov.destino.columna] = pieza_destino;
    
    return en_jaque;
}

// Verifica si hay jaque mate
int hay_jaque_mate(EstadoJuego *juego) {
    // Primero verificar si hay jaque
    if (!hay_jaque(juego)) return 0;
    
    // Buscar todos los movimientos posibles del jugador actual
    for (int i = 1; i < FILAS-1; i++) {
        for (int j = 1; j < COLUMNAS-1; j++) {
            char pieza = juego->tablero[i][j];
            
            // Verificar si la pieza pertenece al jugador actual
            int es_pieza_actual = 0;
            if (juego->turno == BLANCO && es_pieza_blanca(pieza)) es_pieza_actual = 1;
            if (juego->turno == NEGRO && es_pieza_negra(pieza)) es_pieza_actual = 1;
            
            if (!es_pieza_actual) continue;
            
            // Probar todos los movimientos posibles desde esta posición
            for (int fi = 1; fi < FILAS-1; fi++) {
                for (int co = 1; co < COLUMNAS-1; co++) {
                    if (i == fi && j == co) continue; // Misma posición
                    
                    Movimiento mov;
                    mov.origen.fila = i;
                    mov.origen.columna = j;
                    mov.destino.fila = fi;
                    mov.destino.columna = co;
                    
                    // Verificar si es un movimiento válido
                    if (es_movimiento_valido(juego->tablero, mov)) {
                        // Verificar si este movimiento saca al rey del jaque
                        if (!movimiento_deja_en_jaque(juego, mov)) {
                            return 0; // Hay un movimiento válido, no es jaque mate
                        }
                    }
                }
            }
        }
    }
    
    return 1; // No hay movimientos válidos, es jaque mate
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
