#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablero.h"
#include "juego.h"

int main() {
    // Declarar el estado del juego
    EstadoJuego juego;
    
    // Inicializar el juego
    inicializar_juego(&juego);
    
    // Mostrar el tablero inicial
    printf("¡Bienvenido al juego de ajedrez!\n");
    mostrar_estado_juego(&juego);
    
    // Buffer para la entrada del usuario
    char entrada[10];
    
    // Bucle principal del juego
    while (juego.estado != JAQUE_MATE && juego.estado != TABLAS) {
        // Solicitar movimiento
        printf("\nIngrese su movimiento (ej: e2 e4): ");
        fgets(entrada, sizeof(entrada), stdin);
        
        // Eliminar el salto de línea
        entrada[strcspn(entrada, "\n")] = 0;
        
        // Si el usuario escribe "salir", terminar el juego
        if (strcmp(entrada, "salir") == 0) {
            printf("Juego terminado.\n");
            break;
        }
        
        // Procesar el turno
        if (procesar_turno(&juego, entrada)) {
            // Mostrar el estado actualizado
            mostrar_estado_juego(&juego);
        }
    }
    
    return 0;
}
