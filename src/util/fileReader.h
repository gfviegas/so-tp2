/**
 * Gerencia e chama as funções relacionadas ao sudoku, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef fileReader_h
#define fileReader_h

#include <stdio.h>
#include "logger.h"
#include "interface.h"
#include "string.h"

// Tamanho da string com caminho do arquivo
#define FILE_PATH_BUFFER_SIZE 150

// Tamanho maximo de cada linha do arquivo em caracteres
#define FILE_BUFFER_SIZE 500

// Tamanho da string que aramazena o arquivo. Máximo de 100 linhas.
#define FILE_MAX_SIZE 50000

/**
 * Le o caminho pra um arquivo
 * @param filePath String que salvará o caminho do arquivo
 */
void promptFilePath(char* filePath);

/**
 * Abre um arquivo a partir de um caminho fornecido válido
 * @param file     Ponteiro pra o arquivo a ser aberto
 * @param filePath Caminho do arquivo, em uma string
 */
void openFile(FILE** file, char* filePath);

/**
 * Lê o conteudo de uma linha do arquivo e salva na string de buffer
 * @param  file   Arquivo lido
 * @param  buffer Buffer da linha
 * @return        Linha lida
 */
char* readLine(FILE* file, char* buffer);

/**
 * Lê o conteúdo de um arquivo e salva numa string
 * @param text String a ter seu valor escrito
 */
void parseFileInString(char *text);

#endif /* fileReader_h */
