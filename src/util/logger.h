/**
 * Auxilia no output do programa com funções auxiliares para colorir o terminal
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef logger_h
#define logger_h

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>


// Código ANSI das cores para colorir o terminal
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

// Tamanho da linha a ser impressa diversas vezes
#define LINE_SIZE 60

// Tamanho máximo de uma string a ser impressa com a funcao cprintf
#define CPRINTF_BUFFER_LENGTH 4096

/**
 * Cores disponíveis para ser impressas
 */
typedef enum AvailableColors {
    RED,      // Vermelho
    GREEN,    // Verde
    YELLOW,   // Amarelo
    BLUE,     // Azul
    MAGENTA,  // Magenta
    CYAN      // Ciano
} AvailableColors;

/**
 * Limpa o terminal. Abstraída para não ter que importar a stdlib em toda biblioteca
 */
void clearOutput(void);

/**
 * Colored-Printf. Imprime uma mensagem no stdout, como no printf, mas colorido
 * @param color   Cor da mensagem a ser impressa
 * @param fmt     String de formato como do printf
 * @param VARARGS Argumentos adicionais a ser misturados no fmt
 */
void cprintf(AvailableColors color, const char* fmt, ...);

/**
 * Imprime uma linha de tamanho LINE_SIZE, em cor Ciano
 */
void printLine(void);

#endif /* logger_h */
