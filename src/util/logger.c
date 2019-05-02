/**
 * Auxilia no output do programa com funções auxiliares para colorir o terminal
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "logger.h"

// Limpa o terminal. Abstraída para não ter que importar a stdlib em toda biblioteca
void clearOutput(void) {
	system("clear");
}

// Colored-Printf. Imprime uma mensagem no stdout, como no printf, mas colorido
void cprintf(AvailableColors color, const char* fmt, ...) {
    static const char* colors[] = {
        ANSI_COLOR_RED,
        ANSI_COLOR_GREEN,
        ANSI_COLOR_YELLOW,
        ANSI_COLOR_BLUE,
        ANSI_COLOR_MAGENTA,
        ANSI_COLOR_CYAN
    };

    char buffer[CPRINTF_BUFFER_LENGTH];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    printf("%s%s%s", colors[color], buffer, ANSI_COLOR_RESET);
}

// Imprime uma linha de tamanho LINE_SIZE, em cor Ciano
void printLine(void) {
    printf("\n");

    for (int i = 0; i < LINE_SIZE; i++)
        printf("%s=", ANSI_COLOR_CYAN);

    printf("\n%s", ANSI_COLOR_RESET);
}
