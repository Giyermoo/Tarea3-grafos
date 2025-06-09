#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct Nodo {
    char ciudad[4];
    int peso;
    struct Nodo* siguiente;
} Nodo;

typedef struct Vertice {
    char ciudad[4];
    Nodo* adyacentes;
    struct Vertice* siguiente;
} Vertice;

typedef struct {
    Vertice* inicio;
} Grafo;

Grafo* crear_grafo_desde_archivo(const char* archivo);
void encontrar_ruta_minima(Grafo* grafo, const char* origen, const char* destino);
void liberar_grafo(Grafo* grafo);

#endif
