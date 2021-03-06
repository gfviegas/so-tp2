/**
 * Arquivo principal, que inicia a interface/programa
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#define NORMAL_MODE 0
#define DEBUG_MODE 1

#include "setup.hpp"
#include "commander.hpp"
#include "interfaces/commanderInterface.hpp"


using namespace std;
int main(int argc, const char *argv[]) {
    Setup::parseArguments(argc, argv);

    try {
        clearOutput();
        CommanderInterface::welcome();
        InputSource is = CommanderInterface::chooseSource();

        Commander commander(is);
    } catch (exception &e) {
		printError(e);
		exit(1);
	}


    return 0;
}
