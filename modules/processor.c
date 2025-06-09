#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "processor.h"

#define MAX_CIUDADES 100

typedef struct {
    char ciudad[4];
    int distancia;
    char anterior[4];
    int visitado;
} Estado;

// ======================= CREACIÓN DEL GRAFO =========================

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

// ========================== LIBERAR MEMORIA ===========================

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

// ========================== DIJKSTRA ===============================

Vertice* buscar_vertice_por_nombre(Grafo* grafo, const char* ciudad) {
    Vertice* actual = grafo->inicio;
    while (actual) {
        if (strcmp(actual->ciudad, ciudad) == 0) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

int encontrar_indice(Estado estados[], int count, const char* ciudad) {
    for (int i = 0; i < count; i++) {
        if (strcmp(estados[i].ciudad, ciudad) == 0)
            return i;
    }
    return -1;
}

int min_distancia(Estado estados[], int count) {
    int min = INT_MAX;
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (!estados[i].visitado && estados[i].distancia < min) {
            min = estados[i].distancia;
            idx = i;
        }
    }
    return idx;
}

void reconstruir_ruta(Estado estados[], int count, const char* origen, const char* destino) {
    char ruta[MAX_CIUDADES][4];
    int pasos = 0;
    char actual[4];
    strcpy(actual, destino);

    while (strcmp(actual, "") != 0 && strcmp(actual, origen) != 0) {
        strcpy(ruta[pasos++], actual);
        int idx = encontrar_indice(estados, count, actual);
        if (idx == -1) break;
        strcpy(actual, estados[idx].anterior);
    }

    if (strcmp(actual, origen) != 0) {
        printf("No se encontró una ruta.\n");
        return;
    }

    printf("Ruta óptima: %s", origen);
    for (int i = pasos - 1; i >= 0; i--) {
        printf(" -> %s", ruta[i]);
    }

    int idx_final = encontrar_indice(estados, count, destino);
    printf("\nDistancia total: %d km\n", estados[idx_final].distancia);
}

void encontrar_ruta_minima(Grafo* grafo, const char* origen, const char* destino) {
    Estado estados[MAX_CIUDADES];
    int count = 0;

    // Inicializar tabla de estados
    Vertice* actual = grafo->inicio;
    while (actual) {
        strcpy(estados[count].ciudad, actual->ciudad);
        estados[count].distancia = INT_MAX;
        estados[count].visitado = 0;
        strcpy(estados[count].anterior, "");
        if (strcmp(actual->ciudad, origen) == 0)
            estados[count].distancia = 0;
        count++;
        actual = actual->siguiente;
    }

    // Dijkstra
    while (1) {
        int idx = min_distancia(estados, count);
        if (idx == -1) break;

        estados[idx].visitado = 1;
        Vertice* v = buscar_vertice_por_nombre(grafo, estados[idx].ciudad);
        Nodo* adj = v->adyacentes;

        while (adj) {
            int i = encontrar_indice(estados, count, adj->ciudad);
            if (i != -1 && !estados[i].visitado) {
                int nueva_dist = estados[idx].distancia + adj->peso;
                if (nueva_dist < estados[i].distancia) {
                    estados[i].distancia = nueva_dist;
                    strcpy(estados[i].anterior, estados[idx].ciudad);
                }
            }
            adj = adj->siguiente;
        }
    }

    reconstruir_ruta(estados, count, origen, destino);
}
