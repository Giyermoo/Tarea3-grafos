#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/processor.h"
#include "modules/validator.h"

int main(int argc, char *argv[]) {
    if (!validar_argumentos(argc)) {
        fprintf(stderr, "Uso: %s rutas.txt ORIGEN DESTINO\n", argv[0]);
        return 1;
    }

    char *archivo = argv[1];
    char *origen = argv[2];
    char *destino = argv[3];

    Grafo *grafo = crear_grafo_desde_archivo(archivo);
    if (!grafo) {
        fprintf(stderr, "Error al procesar el archivo.\n");
        return 1;
    }

    encontrar_ruta_minima(grafo, origen, destino);
    liberar_grafo(grafo);

    return 0;
}
