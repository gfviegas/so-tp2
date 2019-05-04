/**
 * Arquivo principal, que inicia a interface/programa
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#define NORMAL_MODE 0
#define DEBUG_MODE 1

#include "processManager.hpp"

using namespace std;

#include "util/logger.hpp"

int main(int argc, const char * argv[]) {
	clearOutput();

    SimulatedProcess process;

    process.set(8);
    process.add(2);

	cout << "BORA BOTAR PRA QUEBRAR!!" << endl;

	printLine();

    // Modo default é o modo normal
    // int programMode = NORMAL_MODE;

    // for (int i = 0; i < argc; i++)
        // if (strcmp(argv[i], "-d") == 0) programMode = DEBUG_MODE;

    return 0;
}
