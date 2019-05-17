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
    insertProcess(firstProcess);

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
    cout << "[PM] Execute: " << pcbTable[runningState.pcbTableIndex].getValue() << reset << endl;

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
	PriorityProcessItem ppItem = runningState;
	PriorityProcessItem nextPpItem = readyState.top();
	readyState.pop();
	readyState.push(ppItem);

	runningState = nextPpItem;
	cpu.changeProcess(runningState.process, time);
}
