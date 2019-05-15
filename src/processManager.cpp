/**
 * Definição da classe ProcessManager: simula cinco funções de gerenciamento de
 * processos e inicia o processo reporter sempre que precisa imprimir o estado
 * do sistema.
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "processManager.hpp"
#include "simulatedProcess.hpp"
#include "reporter.hpp"

int ProcessManager::time;
Cpu ProcessManager::cpu;
PcbTable ProcessManager::pcbTable;
priority_queue<PriorityProcessItem> ProcessManager::readyState;
queue<PriorityProcessItem> ProcessManager::blockedState;
PriorityProcessItem ProcessManager::runningState;

ProcessManager::ProcessManager(void) {
}

void ProcessManager::init(void) {
	cout << green << "init do PM rodou" << reset << endl;

    ifstream stream;
    stream.open("src/init");

    string program;
    char c = stream.get();

    while (stream.good()) {
        program += c;
        c = stream.get();
    }

    stream.close();

    SimulatedProcess *firstProcess = new SimulatedProcess(program);
    insertProcess(
		firstProcess->id,
		firstProcess->masterId,
		&(firstProcess->pc),
		&(firstProcess->n),
		&(firstProcess->cpuTime),
		firstProcess
	);

    contextChange();
}


// Segundo a politica de escalonamento, parcela de quantum que o processo tem disponivel
int remainingQuantum(PcbTableItem item) {

	// A quantidade de Quantum que o processo tem que rodar é 2^priority.
	return item.getCpuTime() - (1 << item.getPriority());
}

/**
 * Q - Fim de uma unidade de tempo
 * Executa a próxima instrução do processo simulado.
 */
void ProcessManager::execute(void) {
	time++;
	cpu.nextCommand();

	//  Se o processo em execução usar a sua fatia de tempo por completo, a sua prioridade é diminuída
	if (remainingQuantum(pcbTable[runningState.pcbTableIndex]) == 0) {
		pcbTable[runningState.pcbTableIndex].decreasePriority();
	}
}

void ProcessManager::unblock(void) {
    if (blockedState.empty()) return;

	// Pega o primeiro processo bloqueado
	PriorityProcessItem p = blockedState.front();

	// Adiciona na fila de processos prontos
	readyState.push(p);

	// Remove o processo da fila de bloqueados.
	blockedState.pop();
}

void ProcessManager::print(void) {
	pid_t forkPID = fork();
	Reporter reporter;
	if(forkPID < 0 ){
		perror("Erro no fork");
		exit(1);
	} else if(forkPID == 0) {
		//Estamos no filho
		reporter.print(time, pcbTable, readyState, blockedState, runningState);
	} else {
		//Estamos no pai, temos que esperar
		waitpid(-1, NULL, 0);
	}
}

void ProcessManager::endExecution(void) {
	// chamar o processo de end do reporter
}

void ProcessManager::block(void) {
	blockedState.push(runningState);

	// Se o processo for bloqueado, antes de expirar seu quantum alocado, a sua prioridade é aumentada.
	if (remainingQuantum(pcbTable[runningState.pcbTableIndex]) > 0) {
		pcbTable[runningState.pcbTableIndex].increasePriority();
	}

	contextChange();
}

void ProcessManager::runCommand(char command) {
    cout << cyan << "[PM] RECEBIDO O COMANDO " << command << reset << endl;
	switch (command) {
		case 'Q': return execute();
		case 'U': return unblock();
		case 'P': return print();
		case 'T': return endExecution();
		default: throw invalid_argument("Comando inválido encaminhado para o PM");
	}
}

void ProcessManager::insertProcess(int pid, int masterId, int *pc, int *n, int *cpuTime, SimulatedProcess* process) {
	PcbTableItem item(
		pid,
		masterId,
		pc,
		n,
        time,
		cpuTime
	);

	pcbTable.push_back(item);

	PriorityProcessItem ppItem;
	ppItem.pcbTableIndex = pcbTable.size() - 1;
	ppItem.priority = &(pcbTable[ppItem.pcbTableIndex].priority);
	ppItem.process = process;
	readyState.push(ppItem);
}

// Remove um processo da tabela
void ProcessManager::removeProcess(int pid) {
    for (int i = 0; i < (int) pcbTable.size(); i++) {
        if (pcbTable[i].pid == pid) {
            pcbTable.erase(pcbTable.begin() + i);
            return;
        }
    }

	// TODO: dependendo da politica de escalonamento, chamar ela pra pegar um proximo processo
    contextChange();
}

// Muda o processo que está rodando na CPU para o proximo na fila de readystate
void ProcessManager::contextChange(void) {
	PriorityProcessItem ppItem = runningState;
	PriorityProcessItem nextPpItem = readyState.top();
	readyState.pop();
	readyState.push(ppItem);

	runningState = nextPpItem;
	cpu.changeProcess(runningState.process, time);
}
