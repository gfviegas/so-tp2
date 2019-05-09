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

#include "<priority_queue>"
#include "<queue>"
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

		// Unidade de tempo atual.
		static int time;

		// CPU
		static Cpu cpu;

		// Tabela de Processos.
		static PcbTable pcbTable;

		// Fila dos indices dos processos em pcbTable que estão prontos
		static priority_queue<priorityProcessItem> readyState;

		// Fila dos indices dos processos em pcbTable que estão bloqueados
		static queue<int> blockedState;

		// Índice do processo em pcbTable que está em execução no momento
		static int runningState;

		// Construtor
		ProcessManager(void);

	public:
		static void init(void);
		static void runCommand(char command);

		static void insertProcess(int pid, int masterId, int *pc, int *n, int *cpuTime);
		static void removeProcess(int pid);

		// Chamado pelo SP pra atualizar blockedState e atualizar prioridades de acordo com a politica.
		static void block(void);
};

#endif /* processManager_hpp */
