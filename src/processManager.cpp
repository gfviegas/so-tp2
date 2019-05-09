/**
 * Definição da classe ProcessManager: simula cinco funções de gerenciamento de
 * processos e inicia o processo reporter sempre que precisa imprimir o estado
 * do sistema.
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "processManager.hpp"

#include "util/logger.hpp"

ProcessManager::ProcessManager(void) {
}

void ProcessManager::init(void) {
	cout << green << "init do PM rodou" << reset << endl;

    ifstream stream;
    stream.open("src/init");

    string program;
    char c = stream.get();

    while (stream.good())
    {
        program += c;
        c = stream.get();
    }

    stream.close();

    SimulatedProcess *firstProcess = new SimulatedProcess(program);

    // firstProcess->readComand();
    // firstProcess->readComand();

    // enviar processo para CPU, PCBTABLE
}

/**
 * Q - Fim de uma unidade de tempo
 * Executa a próxima instrução do processo simulado.
 */
void ProcessManager::execute(void) {
	time++;
	cpu.nextCommand(time);
}

void ProcessManager::unblock(void) {
}

void ProcessManager::print(void) {
}


void ProcessManager::endExecution(void) {
}

void ProcessManager::block(void) {
	// Verificar tempo de CPU do SP, ver sua prioridade, se nao usou X valores, atualizar priroidade...
	// Atualizar blockedState, etc.
}

void ProcessManager::runCommand(char command) {
	switch (command) {
		case 'Q': return execute();
		case 'U': return unblock();
		case 'P': return print();
		case 'T': return endExecution();
		default: throw invalid_argument("Comando inválido encaminhado para o PM");
	}
}

void ProcessManager::insertProcess(int pid, int masterId, int *pc, int *n, int *cpuTime) {
	PcbTableItem item = new PcbTableItem(
		pid,
		masterId,
		pc,
		n,
		cpuTime,
		time
	);

	pcbTable.push_back(item);

	priorityProcessItem ppItem;
	ppItem.pcbTableIndex = pcbTable.size() - 1;
	ppItem.priority = &(pcbTable[ppItem.pcbTableIndex].priority);
	readyState.push_back(ppItem);
}

// Remove um processo da tabela
void ProcessManager::removeProcess(int pid) {
	int index;

	for (PcbTableItem item : pcbTable) {
		if (item.id == pid) {
			int index = distance(pcbTable.begin(), item);
			pcbTable.erase(index);
			return;
		}
	}

	// TODO: dependendo da politica de escalonamento, chamar ela pra pegar um proximo processo
}

// Muda o processo que está rodando na CPU
void ProcessManager::contextChange(SimulatedProcess *process) {
	cpu.process = process;

	for (int i = 0; i < pcbTable.size(); i++) {
		if (pcbTable[i].pid == process->id) {
			runningState = i;
		}
	}
}
