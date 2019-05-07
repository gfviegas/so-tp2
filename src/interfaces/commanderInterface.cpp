#include "commanderInterface.hpp"

void CommanderInterface::welcome(void) {
	cout << endl << endl;
	printLine();
	cout << blue << "_____                      _   _ _           _       \n| ___ \\                    | | | (_)         | |\n| |_/ / ___ _ __ ___ ______| | | |_ _ __   __| | ___\n| ___ \\/ _ \\ '_ ` _ \\______| | | | | '_ \\ / _` |/ _ \\\n| |_/ /  __/ | | | | |     \\ \\_/ / | | | | (_| | (_) |\n\\____/ \\___|_| |_| |_|      \\___/|_|_| |_|\\__,_|\\___/\n";
	cout << yellow << "\n \t Ao TP 2 - SO!" << reset << endl;
	cout << cyan << "\t por: Bruno Marra, Gustavo Viegas & Heitor Passeado!" << reset;
	printLine();
}

InputSource CommanderInterface::chooseSource(void) {
	int choice = 0;

	cout << green << "Escolha qual a forma de entrada dos dados." << endl;
	cout << green << "1 - Entrada Padrão" << endl;
	cout << green << "2 - Arquivo de Entrada" << endl;
	cout << green << "0 - Cancelar" << endl;

	try {
		promptArrow();
		cin >> choice;

		switch (choice) {
			case 1: return STDIO;
			case 2: return EXTERNAL_FILE;
			default: throw invalid_argument("Opção de entrada de dados inválida!");
		}
	} catch (exception& e) {
		printError(e);
		exit(1);
	}
}

void CommanderInterface::commandsInstructions(void) {
	clearOutput();
	cout << cyan << "[COMMANDER] Iniciando leitura de comandos por entrada padrão." << endl;
	cout << green << "Q - Fim de uma unidade de tempo." << endl;
	cout << green << "U - Desbloqueia o primeiro processo simulado na fila bloqueada." << endl;
	cout << green << "P - Imprime o estado atual do sistema." << endl;
	cout << green << "T - Imprime o tempo médio do ciclo e finaliza o sistema." << endl;
}

bool CommanderInterface::isCodeValid(char code) {
	bool condition = (code == 'Q' || code == 'U' || code == 'P' || code == 'T');
	if (!condition) cout << red << "Comando inválido! Tente novamente." << reset << endl;
	return condition;
}

queue<char> CommanderInterface::readCommandFromStdIO(void) {
	char code;
	queue<char> codesQueue;

	try {

		do {
			do {
				promptArrow();
				cin >> code;
				code = toupper(code);
			} while (!isCodeValid(code));

			codesQueue.push(code);
		} while (code != 'T');
	} catch (exception& e) {
		printError("Programa encerrado inesperadamente");
		exit(1);
	}

	return codesQueue;
}

queue<char> CommanderInterface::readCommandFromFile(void) {
	clearOutput();
	cout << cyan << "[COMMANDER] Iniciando leitura de comandos por arquivo." << endl;
	cout << green << "Digite o caminho do arquivo de entrada." << endl;

	char code;
	bool alreadyRan = false;
	string filePath;
	ifstream inputFile;
	queue<char> codesQueue;

	try {
		do {
			if (alreadyRan) cout << red << "Arquivo inválido ou não encontrado!" << reset << endl;
			promptArrow();
			cin >> filePath;
			cout << reset << endl;
			alreadyRan = true;

			inputFile.open(filePath);
		} while (!inputFile.is_open());


		while (inputFile >> code) {
			codesQueue.push(code);
		}

	} catch (exception& e) {
		printError("Programa encerrado inesperadamente");
		exit(1);
	}

	return codesQueue;
}
