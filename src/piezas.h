#ifndef PIEZAS_H
#define PIEZAS_H

// Definiciones para las piezas de ajedrez

// Constantes para identificar el color de las piezas
#define BLANCO 0
#define NEGRO 1

// Constantes para identificar el tipo de pieza
#define PEON 0
#define TORRE 1
#define CABALLO 2
#define ALFIL 3
#define DAMA 4
#define REY 5

// Función para determinar si una pieza es blanca
int es_pieza_blanca(char pieza);

// Función para determinar si una pieza es negra
int es_pieza_negra(char pieza);

// Función para determinar el tipo de pieza
int obtener_tipo_pieza(char pieza);

// Función para determinar si una casilla está vacía
int es_casilla_vacia(char pieza);

// Función para determinar si dos piezas son del mismo color
int son_del_mismo_color(char pieza1, char pieza2);

#endif // PIEZAS_H
