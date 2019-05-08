/**
 * Definição da classe ProcessManager: simula cinco funções de gerenciamento de
 * processos e inicia o processo reporter sempre que precisa imprimir o estado
 * do sistema.
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef processManager_hpp
#define processManager_hpp

#include "bits/stdc++.h"

#include "cpu.hpp"
#include "pcbTableItem.hpp"
#include "simulatedProcess.hpp"
// #include "reporter.hpp"

using namespace std;

class ProcessManager
{
private:
	// Q
	void execute(void);
	// U
	void unblock(void);
	// P
	void print(void);
	// T
	void endExecution(void);

	int time;
	Cpu cpu;
	PcbTable pcbTable;
	list<int> blockedState;
	list<int> readyState;
	int runningState;
	// Reporter reporter;
public:
	ProcessManager(void);

	void runCommand(char command);
};

#endif /* processManager_hpp */
