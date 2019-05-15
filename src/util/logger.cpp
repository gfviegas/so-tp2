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
	cout << endl;
	cout << cyan;

    for (int i = 0; i < LINE_SIZE; i++)
		cout << "=";

	cout << reset << endl;
}

void printLineAsterisc(void) {
		cout << endl;

    for (int i = 0; i < LINE_SIZE; i++)
		cout << "*";

		cout << endl;
}

void promptArrow(void) {
	cout << yellow << " > " << reset;
}

void printError(exception& e) {
	cout << red << "Erro: " << e.what() << endl;
}
void printError(string e) {
	cout << red << "Erro: " << e << endl;
}
