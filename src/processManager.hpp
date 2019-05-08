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

class ProcessManager {
	private:
		// Q - Fim de uma unidade de tempo
	    static void execute(void);

	    // U - Desbloqueia o primeiro processo simulado na fila bloqueada.
	    static void unblock(void);

	    // P - Imprime o estado atual do sistema.
	    static void print(void);

	    // T - Imprime o tempo médio do ciclo e finaliza o sistema.
	    static void endExecution(void);

		static int time;
		static Cpu cpu;
		// static PcbTable pcbTable;
		// list<SimulatedProcess> blockedState;
		// PcbTableList readyState;
		// PcbTable runningState;
		// Reporter reporter;

		ProcessManager(void);
	public:
		static void init(void);
		static void runCommand(char command);

		static void appendProcess();
};

#endif /* processManager_hpp */
