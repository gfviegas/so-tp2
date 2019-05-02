/**
 * Arquivo principal, que inicia a interface/programa
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#define NORMAL_MODE 0
#define DEBUG_MODE 1

#include <stdio.h>
#include <string.h>

#include "util/logger.h"
#include "util/interface.h"

int main(int argc, const char * argv[]) {
	clearOutput();

    // Modo default é o modo normal
    int programMode = NORMAL_MODE;

    for (int i = 0; i < argc; i++)
        if (strcmp(argv[i], "-d") == 0) programMode = DEBUG_MODE;


	printHeader(programMode);
	printf("\n");
    return 0;
}
