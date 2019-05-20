/**
 * Auxilia no output do programa com funções auxiliares e colorir o terminal
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "logger.hpp"

// Limpa o terminal. Abstraída para não ter que importar a stdlib em toda biblioteca
void clearOutput(void) {
	system("clear");
}

// Imprime uma linha de tamanho LINE_SIZE, em cor Ciano
void printLine(void) {
    printLine(LINE_SIZE);
}
void printLine(char character) {
	printLine(LINE_SIZE, character);
}
void printLine(int lineSize) {
	printLine(lineSize, '=');
}
void printLine(int lineSize, char character) {
	cout << endl << cyan;
    for (int i = 0; i < lineSize; i++)
		cout << character;

	cout << reset << endl;
}

// Imprime uma linha auxiliar especial pra entrada de dados em amarelo (default do sistema)
void promptArrow(void) {
	cout << yellow << " > " << reset;
}

// Imprime uma linha auxiliar especial pra gerenciamento de erros
void printError(exception& e) {
	cout << red << "Erro: " << e.what() << endl;
}
void printError(string e) {
	cout << red << "Erro: " << e << endl;
}
