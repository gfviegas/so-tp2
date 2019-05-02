/**
 * Gerencia e chama as funções relacionadas ao sudoku, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "fileReader.h"

// Le o caminho pra um arquivo
void promptFilePath(char* filePath) {
    cprintf(GREEN, "\nInsira o caminho do arquivo de leitura: \n");
    prePrompt();
    scanf("%s", filePath);
}

// Abre um arquivo a partir de um caminho fornecido válido
void openFile(FILE** file, char *filePath) {
    *file = fopen(filePath, "r");

    if (*file == NULL) {
        cprintf(RED, "O arquivo %s não existe ou não pode ser lido corretamente.\n Confira o caminho inserido e digite outro.\n\n", filePath);
        promptFilePath(filePath);
        return openFile(file, filePath);
    }
}

// Lê o conteudo de uma linha do arquivo e salva na string de buffer
char* readLine(FILE* file, char* buffer) {
    return fgets(buffer, FILE_BUFFER_SIZE, (FILE*) file);
}

// Lê o conteúdo de um arquivo e salva numa string
void parseFileInString(char *text) {
    char fileName [FILE_BUFFER_SIZE];
    char currentLine [FILE_BUFFER_SIZE];
    FILE *file = NULL;

    cprintf(BLUE,"[CAMINHO] (Exemplo: resources/textoBase.txt)");
    promptFilePath(fileName);
    openFile(&file, fileName);

    while (readLine(file, currentLine)) {
      strcat(text, currentLine);
    }

    cprintf(CYAN, "Texto carregado! \n\n%s\n", text);
    pressEnterToContinue();
}
