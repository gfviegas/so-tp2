/**
 * Gerencia e chama as funções relacionadas as tarefas, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#include "interface.h"

// Imprime uma mensagem de aguardando e aguarda a entrada do usuário para continuar a execução do programa
void pressEnterToContinue(void) {
	cprintf(RED, "\n Pressione enter para continuar...\n");
	int enter = -1;
	getchar();
	while (enter != '\n' && enter != '\r') { enter = getchar(); }
}

// Imprime uma flag que indica a leitura de um dado do usuário
void prePrompt(void) {
    cprintf(YELLOW, "->  ");
}

// Imprime o cabeçalho do programa
void printHeader(int debugMode) {
    clearOutput();
    if (debugMode) cprintf(RED, " *** \n [STATS] MODO DEBUG ATIVADO! \n *** \n");

    printf("\n\n");
    printLine();
    cprintf(BLUE, "_____                      _   _ _           _       \n| ___ \\                    | | | (_)         | |\n| |_/ / ___ _ __ ___ ______| | | |_ _ __   __| | ___\n| ___ \\/ _ \\ '_ ` _ \\______| | | | | '_ \\ / _` |/ _ \\\n| |_/ /  __/ | | | | |     \\ \\_/ / | | | | (_| | (_) |\n\\____/ \\___|_| |_| |_|      \\___/|_|_| |_|\\__,_|\\___/\n");
    cprintf(BLUE, "\n \t Ao TP 2 de SO !");
    cprintf(YELLOW, "\n \t por: Gustavo Viegas, Bruno Marra e Heitor Passeado");
    printLine();

    printMenu(debugMode);
}

// Inicializa o programa imprimindo o menu inicial
void printMenu(int debugMode) {
    int choice;

    cprintf(GREEN, "\n \n Selecione qual método de pesquisa você deseja usar : \n\n");
    cprintf(GREEN, "0 - Sair\n");
    prePrompt();
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            _bruteForceInitial(debugMode);
            break;
        case 2:
            _rabinKarpInitial(debugMode);
            break;
        case 0:
            return;
        default:
            cprintf(RED, "\n\n * Digite apenas ..., não temos tantas opções :(\n");
            return printMenu(debugMode);
    }
}
