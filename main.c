#include <stdio.h>
#include "modules/processor.h"
#include "modules/validator.h"

int main(int argc, char *argv[]) {
    if (!validar_argumentos(argc)) {
        fprintf(stderr, "Uso correcto: %s rutas.txt ORIGEN DESTINO\n", argv[0]);
        return 1;
    }

    Grafo* grafo = crear_grafo_desde_archivo(argv[1]);
    if (!grafo) {
        fprintf(stderr, "Error al procesar el archivo.\n");
        return 1;
    }

    encontrar_ruta_minima(grafo, argv[2], argv[3]);
    liberar_grafo(grafo);

    return 0;
}
