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
vector<int> ProcessManager::returnTimes;

ProcessManager::ProcessManager(void) {
    pcbTable = {};
    readyState = {};
    blockedState = {};
    returnTimes = {};
}

void ProcessManager::init(void) {
	if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Init do PM rodou" << reset << endl;

    SimulatedProcess *firstProcess = new SimulatedProcess("R programs/init");
    insertProcess(firstProcess);

    contextChange();
}


// Segundo a politica de escalonamento, parcela de quantum que o processo tem disponivel
int remainingQuantum(PcbTableItem item) {
    // A quantidade de Quantum que o processo tem é 2^priority.
    int available = (1 << item.getPriority());
    int remaining = available - item.getCpuTime();
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Quantum Available: " << available << ". Priority: " << item.getPriority() << reset << endl;
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Quantum Remaining: " << remaining << ". Cpu Time: " << item.getCpuTime() << reset << endl;

	return remaining;
}

/**
 * Q - Fim de uma unidade de tempo
 * Executa a próxima instrução do processo simulado.
 */
void ProcessManager::execute(void) {
	time++;
	cpu.nextCommand();
    int remaining = remainingQuantum(pcbTable[runningState.pcbTableIndex]);

    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Execute: " << pcbTable[runningState.pcbTableIndex].getValue() << reset << endl;

	//  Se o processo em execução usar a sua fatia de tempo por completo, a sua prioridade é diminuída
	if (remaining == 0) pcbTable[runningState.pcbTableIndex].decreasePriority();

    // Se usou todo o quantum disponível, e estamos com a configuração de preemptivo, então tira o processo atual da CPU.
    if (remaining <= 0 && Setup::preemptiveness == Preemptiveness::PREEMPTIVE) {
        contextChange();
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

	if (forkPID < 0) {
		perror("Erro no fork");
		exit(1);
	} else if(forkPID == 0) {
		//Estamos no filho
		Reporter::print(time, pcbTable, readyState, blockedState, runningState);
        exit(0);
	} else {
		//Estamos no pai, temos que esperar
		wait(NULL);
	}
}

void ProcessManager::endExecution(void) {
	pid_t forkPID = fork();
	if (forkPID < 0 ) {
		perror("Erro no fork");
		exit(1);
	} else if (forkPID == 0) {
		// Estamos no filho
		Reporter::end(returnTimes);
	} else {
		//Estamos no pai, temos que esperar
		waitpid(forkPID, NULL, 0);
        system("exit");
	}
}

void ProcessManager::block(void) {
	blockedState.push(runningState);

	// Se o processo for bloqueado, antes de expirar seu quantum alocado, a sua prioridade é aumentada.
	if (remainingQuantum(pcbTable[runningState.pcbTableIndex]) > 0) {
		pcbTable[runningState.pcbTableIndex].increasePriority();
	}

	contextChange(true);
}

void ProcessManager::runCommand(char command) {
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] RECEBIDO O COMANDO " << command << reset << endl;
	switch (command) {
		case 'Q': return execute();
		case 'U': return unblock();
		case 'P': return print();
		case 'T': return endExecution();
		default: throw invalid_argument("Comando inválido encaminhado para o PM");
	}
}

void ProcessManager::insertProcess(SimulatedProcess* process) {
	PcbTableItem item(
		process->id,
		process->masterId,
		&(process->pc),
		&(process->n),
        time,
		&(process->cpuTime)
	);

	pcbTable.push_back(item);

	PriorityProcessItem ppItem;
	ppItem.pcbTableIndex = pcbTable.size() - 1;
	ppItem.priority = &(pcbTable[ppItem.pcbTableIndex].priority);
	ppItem.process = process;
	ppItem.valid = true;
	readyState.push(ppItem);
}

// Remove um processo da tabela
void ProcessManager::removeProcess(int pid, SimulatedProcess* process) {
    int elementIndex = -1;
    for (int i = 0; i < (int) pcbTable.size(); i++) {
        if (pcbTable[i].pid == pid) {
            elementIndex = i;
            pcbTable.erase(pcbTable.begin() + i);
            break;
        }
    }

    // Como um processo foi finalizado, adicionamos o tempo atual na lista de retornos
    returnTimes.push_back(time);

    // Erro!
    if (elementIndex == -1) {
        perror("Erro ao remover o processo!");
		exit(1);
    }

    // Todos elementos depois de elementIndex devem ser reindexados em: readyState, blockedState e runningState
    if (runningState.pcbTableIndex > elementIndex) runningState.pcbTableIndex--;

    // Criando uma blockedState nova com valores atualizados de pcbTableIndex
    queue<PriorityProcessItem> newBlockedQueue;
    while (!blockedState.empty()) {
        PriorityProcessItem pItem = blockedState.front();
        if (pItem.pcbTableIndex > elementIndex) pItem.pcbTableIndex--;
        newBlockedQueue.push(pItem);
        blockedState.pop();
    }
    blockedState = newBlockedQueue;

    // Criando uma readyState nova com valores atualizados de pcbTableIndex
    priority_queue<PriorityProcessItem> newReadyState;
    while (!readyState.empty()) {
        PriorityProcessItem pItem = readyState.top();
        if (pItem.pcbTableIndex > elementIndex) pItem.pcbTableIndex--;
        newBlockedQueue.push(pItem);
        readyState.pop();
    }
    readyState = newReadyState;


    // Desalocando memória do processo
    delete process;
    process = NULL;

	// TODO: dependendo da politica de escalonamento, chamar ela pra pegar um proximo processo
    contextChange();
}

// Muda o processo que está rodando na CPU para o proximo na fila de readystate
void ProcessManager::contextChange(void) {
    return contextChange(false);
}

void ProcessManager::contextChange(bool forceRemove) {
    if (runningState.process != NULL) runningState.process->cpuTime = 0;

    // Se a fila de prontos estiver vazia, não há processos a se alternar.
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Context Change! ReadyState Size: " << readyState.size() << reset << endl;
    if (readyState.empty()) {
        if (forceRemove) runningState = {};
        return;
    }

    PriorityProcessItem ppItem = runningState;
	PriorityProcessItem nextPpItem = readyState.top();
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Context Change - Current Process: " << ppItem.process << reset << endl;
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Context Change - Next Process: " << nextPpItem.process << reset << endl;

    readyState.pop();
	if (ppItem.valid) readyState.push(ppItem);

	runningState = nextPpItem;
	cpu.changeProcess(runningState.process, time);
}
