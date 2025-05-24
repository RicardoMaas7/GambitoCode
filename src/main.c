#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablero.h"
#include "juego.h"
#include "timer.h"

// Función para mostrar el menú principal
void mostrar_menu() {
    printf("\n=====================================\n");
    printf("           GAMBITO CODE                \n");
    printf("=====================================\n");
    printf("  1. Jugar                          \n");
    printf("  2. Salir                          \n");
    printf("=====================================\n");
    printf("Seleccione una opcion: ");
}

// Función para mostrar las opciones durante el juegos
void mostrar_ayuda_juego() {
    printf("\nComandos disponibles:\n");
    printf("   Movimiento: 'posicion inicial posicion final'(e2 e4)\n");
    printf("   Ayuda: 'ayuda'\n");
    printf("   Salir: 'salir'\n");
}

// Función principal del juego
void jugar() {
    // Declarar el estado del juego
    EstadoJuego juego;
    
    // Inicializar el juego
    inicializar_juego(&juego);
    
    // Iniciar timer
    iniciar_timer();
    
    // Mostrar introducción
    printf("\nNuevo juego iniciado!\n");
    mostrar_ayuda_juego();
    mostrar_estado_juego(&juego);
    
    // Buffer para la entrada del usuario
    char entrada[20];
    
    // Bucle principal del juego
    while (juego.estado != JAQUE_MATE && juego.estado != TABLAS) {
        // Mostrar tiempo y solicitar movimiento
        printf("\n");
        mostrar_tiempo_transcurrido();
        printf("Ingrese su movimiento: ");
        fgets(entrada, sizeof(entrada), stdin);
        
        // Eliminar el salto de línea
        entrada[strcspn(entrada, "\n")] = 0;
        
        // Comandos especiales
        if (strcmp(entrada, "salir") == 0) {
            char confirmacion;
            printf("Esta seguro que desea salir? (s/n): ");
            scanf(" %c", &confirmacion);
            getchar(); // Limpiar buffer
            
            if (confirmacion == 's' || confirmacion == 'S') {
                printf("Juego abandonado.\n");
                mostrar_tiempo_transcurrido();
                printf("\n");
                break;
            } else {
                printf("Continuando el juego...\n");
                continue;
            }
        }
        
        if (strcmp(entrada, "ayuda") == 0) {
            mostrar_ayuda_juego();
            continue;
        }
        
        if (strlen(entrada) == 0) {
            printf("Por favor ingrese un movimiento valido.\n");
            continue;
        }
        
        // Procesar el turno
        if (procesar_turno(&juego, entrada)) {
            // Mostrar el estado actualizado
            mostrar_estado_juego(&juego);
            
            // Si hay jaque mate, mostrar tiempo final
            if (juego.estado == JAQUE_MATE) {
                printf("\nPartida terminada!\n");
                mostrar_tiempo_transcurrido();
                printf("\n");
            }
        }
    }
    
    // Si el juego terminó por tablas
    if (juego.estado == TABLAS) {
        printf("\nPartida terminada en tablas!\n");
        mostrar_tiempo_transcurrido();
        printf("\n");
    }
    
    printf("Presione Enter para volver al menu principal...");
    getchar();
}

int main() {
    int opcion;
    
    // Mensaje de bienvenida
    printf("Bienvenido al Ajedrez en C!\n");
    
    // Bucle del menú principal
    while (1) {
        mostrar_menu();
        
        if (scanf("%d", &opcion) != 1) {
            // Limpiar buffer si la entrada no es válida
            while (getchar() != '\n');
            printf("Opcion invalida. Por favor ingrese 1 o 2.\n");
            continue;
        }
        
        // Limpiar buffer
        getchar();
        
        switch (opcion) {
            case 1:
                jugar();
                break;
                
            case 2:
                printf("Gracias por jugar! Hasta la proxima.\n");
                return 0;
                
            default:
                printf("Opcion invalida. Por favor seleccione 1 o 2.\n");
                break;
        }
    }
    
    return 0;
}