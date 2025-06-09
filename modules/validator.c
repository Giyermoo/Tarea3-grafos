#include "validator.h"
#include <stdio.h>

int validar_argumentos(int argc) {
    if (argc != 4) {
        return 0;
    }
    return 1;
}
