// Función para determinar si una pieza es blanca
int es_pieza_blanca(char pieza) {
    return (pieza >= 'A' && pieza <= 'Z');
}

// Función para determinar si una pieza es negra
int es_pieza_negra(char pieza) {
    return (pieza >= 'a' && pieza <= 'z');
}

// Función para determinar el tipo de pieza
int obtener_tipo_pieza(char pieza) {
    char p = (pieza >= 'a' && pieza <= 'z') ? (pieza - 32) : pieza; // Convertir a mayúscula
    
    switch (p) {
        case 'P': return PEON;
        case 'T': return TORRE;
        case 'C': return CABALLO;
        case 'A': return ALFIL;
        case 'D': return DAMA;
        case 'R': return REY;
        default: return -1; // No es una pieza válida
    }
}

// Función para determinar si una casilla está vacía
int es_casilla_vacia(char pieza) {
    return pieza == ' ';
}


int son_del_mismo_color(char pieza1, char pieza2) {
    return (es_pieza_blanca(pieza1) && es_pieza_blanca(pieza2)) || 
           (es_pieza_negra(pieza1) && es_pieza_negra(pieza2));
}