/**
 * Auxilia no output do programa com funções auxiliares e colorir o terminal
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef logger_hpp
#define logger_hpp

#include <iostream>
#include <stdlib.h>

using namespace std;

// Tamanho da linha a ser impressa diversas vezes
#define LINE_SIZE 60

// Tamanho máximo de uma string a ser impressa com a funcao cprintf
#define CPRINTF_BUFFER_LENGTH 4096

// Constantes para colorir o output. Exemplo de uso:
// cout << "Teste: " << yellow << variavelX << reset << endl;
const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string blue("\033[1;34m");
const std::string magenta("\033[0;35m");
const std::string cyan("\033[0;36m");
const std::string reset("\033[0m");

/**
 * Limpa o terminal. Abstraída para não ter que importar a stdlib em toda biblioteca
 */
void clearOutput(void);

/**
 * Imprime uma linha de tamanho LINE_SIZE, em cor Ciano
 */
void printLine(void);

/**
 * Imprime uma linha auxiliar especial pra entrada de dados em amarelo (default do sistema)
 */
void promptArrow(void);

/**
 * Imprime uma linha auxiliar especial pra gerenciamento de erros
 */
void printError(exception& e);
void printError(string e);

#endif /* logger_hpp */
