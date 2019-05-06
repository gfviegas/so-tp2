#ifndef commanderInterface_hpp
#define commanderInterface_hpp

#include "../util/logger.hpp"
#include "inputSource.hpp"

using namespace std;
class CommanderInterface {
	private:

	public:
		CommanderInterface (void);

		static void welcome(void) {
			cout << endl << endl;
		    printLine();
			cout << blue << "_____                      _   _ _           _       \n| ___ \\                    | | | (_)         | |\n| |_/ / ___ _ __ ___ ______| | | |_ _ __   __| | ___\n| ___ \\/ _ \\ '_ ` _ \\______| | | | | '_ \\ / _` |/ _ \\\n| |_/ /  __/ | | | | |     \\ \\_/ / | | | | (_| | (_) |\n\\____/ \\___|_| |_| |_|      \\___/|_|_| |_|\\__,_|\\___/\n";
			cout << yellow << "\n \t Ao TP 2 - SO!" << reset << endl;
			cout << cyan << "\t por: Bruno Marra, Gustavo Viegas & Heitor Passeado!" << reset;
		    printLine();
		}

		static InputSource chooseSource(void) {
			int choice = 0;

			cout << green << "Escolha qual a forma de entrada dos dados." << endl;
			cout << green << "1 - Entrada Padrão" << endl;
			cout << green << "2 - Arquivo de Entrada" << endl;
			cout << green << "0 - Cancelar" << endl;

			promptArrow();
			cin >> choice;

			switch (choice) {
				case 1: return STDIO;
				case 2: return EXTERNAL_FILE;
			}

			perror("Opção de entrada de dados inválida!");
			exit(1);
		}
};

#endif /* commanderInterface_hpp */
