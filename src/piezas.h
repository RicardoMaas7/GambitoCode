#ifndef PIEZAS_H
#define PIEZAS_H

#define BLANCO 0
#define NEGRO 1

#define PEON 0
#define TORRE 1
#define CABALLO 2
#define ALFIL 3
#define DAMA 4
#define REY 5

int es_pieza_blanca(char pieza);

int es_pieza_negra(char pieza);

int obtener_tipo_pieza(char pieza);

int es_casilla_vacia(char pieza);

int son_del_mismo_color(char pieza1, char pieza2);

#endif