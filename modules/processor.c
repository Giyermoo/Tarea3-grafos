#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

Nodo* crear_nodo(const char* ciudad, int peso) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->ciudad, ciudad);
    nuevo->peso = peso;
    nuevo->siguiente = NULL;
    return nuevo;
}

Vertice* buscar_vertice(Grafo* grafo, const char* ciudad) {
    Vertice* actual = grafo->inicio;
    while (actual != NULL) {
        if (strcmp(actual->ciudad, ciudad) == 0)
            return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

Vertice* crear_vertice(Grafo* grafo, const char* ciudad) {
    Vertice* nuevo = (Vertice*)malloc(sizeof(Vertice));
    strcpy(nuevo->ciudad, ciudad);
    nuevo->adyacentes = NULL;
    nuevo->siguiente = grafo->inicio;
    grafo->inicio = nuevo;
    return nuevo;
}

void agregar_arista(Grafo* grafo, const char* origen, const char* destino, int peso) {
    Vertice* v_origen = buscar_vertice(grafo, origen);
    if (!v_origen) v_origen = crear_vertice(grafo, origen);

    Vertice* v_destino = buscar_vertice(grafo, destino);
    if (!v_destino) v_destino = crear_vertice(grafo, destino);

    Nodo* nuevo1 = crear_nodo(destino, peso);
    nuevo1->siguiente = v_origen->adyacentes;
    v_origen->adyacentes = nuevo1;

    Nodo* nuevo2 = crear_nodo(origen, peso);
    nuevo2->siguiente = v_destino->adyacentes;
    v_destino->adyacentes = nuevo2;
}

Grafo* crear_grafo_desde_archivo(const char* archivo) {
    FILE* f = fopen(archivo, "r");
    if (!f) return NULL;

    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->inicio = NULL;

    char origen[4], destino[4];
    int peso;

    while (fscanf(f, "%3s %3s %d", origen, destino, &peso) == 3) {
        agregar_arista(grafo, origen, destino, peso);
    }

    fclose(f);
    return grafo;
}

void encontrar_ruta_minima(Grafo* grafo, const char* origen, const char* destino) {
    printf("Grafo construido correctamente.\n");
    printf("Ruta de prueba: %s -> %s (algoritmo no implementado aún)\n", origen, destino);
}

void liberar_grafo(Grafo* grafo) {
    Vertice* actual = grafo->inicio;
    while (actual) {
        Nodo* adj = actual->adyacentes;
        while (adj) {
            Nodo* temp = adj;
            adj = adj->siguiente;
            free(temp);
        }
        Vertice* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    free(grafo);
}
