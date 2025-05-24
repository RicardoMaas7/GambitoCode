#include "timer.h"
#include <stdio.h>

// Variable global para almacenar el tiempo de inicio
static time_t tiempo_inicio = 0;

// Inicializa el timer del juego
void iniciar_timer() {
    tiempo_inicio = time(NULL);
}

// Muestra el tiempo transcurrido desde que se inició
void mostrar_tiempo_transcurrido() {
    if (tiempo_inicio == 0) {
        printf("Timer no iniciado.\n");
        return;
    }
    
    time_t ahora = time(NULL);
    int segundos = (int)(ahora - tiempo_inicio);
    int minutos = segundos / 60;
    segundos = segundos % 60;
    
    printf("Tiempo de juego: %02d:%02d\n", minutos, segundos);
}

// Obtiene el tiempo transcurrido en segundos
int obtener_tiempo_transcurrido() {
    if (tiempo_inicio == 0) {
        return 0;
    }
    
    time_t ahora = time(NULL);
    return (int)(ahora - tiempo_inicio);
}