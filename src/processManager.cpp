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

// Inicializa o PM, configurando o primeiro processo.
void ProcessManager::init(void) {
	if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Init do PM rodou" << reset << endl;

    SimulatedProcess *firstProcess = new SimulatedProcess("R programs/init");
    insertProcess(firstProcess);

    contextChange();
}


// Calcula o quantum restante de um item, baseado na sua prioridade
int ProcessManager::remainingQuantum(PcbTableItem item) {
    // A quantidade de Quantum que o processo tem é 2^priority.
    int available = (1 << item.getPriority());
    int remaining = available - cpu.processTime;
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Quantum Available: " << available << ". Priority: " << item.getPriority() << reset << endl;
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Quantum Remaining: " << remaining << ". Cpu Time: " << cpu.processTime << reset << endl;

	return remaining;
}

// Q - Fim de uma unidade de tempo. Executa a próxima instrução do processo simulado.
void ProcessManager::execute(void) {
    time++;

	cpu.nextCommand();

    // Se não tiver processo na CPU, tenta pegar um pronto e não há prioridades pra mudar.
    if (!runningState.valid) {
        contextChange();
        return;
    }

    int remaining = remainingQuantum(pcbTable[runningState.pcbTableIndex]);
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Execute: " << pcbTable[runningState.pcbTableIndex].getValue() << reset << endl;

	//  Se o processo em execução usar a sua fatia de tempo por completo, a sua prioridade é diminuída
	if (remaining == 0) pcbTable[runningState.pcbTableIndex].decreasePriority();

    // Se usou todo o quantum disponível, e estamos com a configuração de preemptivo, então tira o processo atual da CPU.
    if (remaining <= 0 && Setup::preemptiveness == Preemptiveness::PREEMPTIVE) contextChange();
}

// U - Desbloqueia o primeiro processo simulado na fila bloqueada.
void ProcessManager::unblock(void) {
    if (blockedState.empty()) return;

	// Pega o primeiro processo bloqueado
	PriorityProcessItem p = blockedState.front();

	// Adiciona na fila de processos prontos
	readyState.push(p);

	// Remove o processo da fila de bloqueados.
	blockedState.pop();
}

// P - Imprime o estado atual do sistema.
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

// T - Imprime o tempo médio do ciclo e finaliza o sistema.
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

// Chamado pelo SP pra atualizar blockedState e atualizar prioridades de acordo com a politica.
void ProcessManager::block(void) {
	blockedState.push(runningState);

	// Se o processo for bloqueado, antes de expirar seu quantum alocado, a sua prioridade é aumentada.
	if (remainingQuantum(pcbTable[runningState.pcbTableIndex]) > 0) {
		pcbTable[runningState.pcbTableIndex].increasePriority();
	}

    // Se não tiver nenhum processo na fila de prontos, na proxima troca de contexto, o processo atual deve estar vago.
    runningState = {};
    cpu.changeProcess(NULL, time);
}

// Recebe um comando e chama o método devido relacionado a este comando.
void ProcessManager::runCommand(char command) {
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] RECEBIDO O COMANDO " << command << reset << endl;
    try {
        switch (command) {
            case 'Q': return execute();
            case 'U': return unblock();
            case 'P': return print();
            case 'T': return endExecution();
            default: throw invalid_argument("Comando inválido encaminhado para o PM");
        }
    } catch (exception &e) {
		printError(e);
		exit(1);
	}
}

// Insere um processo na tabela de processos e na lista de prontos.
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

// Reindexa as estruturas que armazena o pcbTableIndex após a remoção de um item
void ProcessManager::reindexStructures(int index) {
    if (Setup::isDebug()) cout << magenta << "Element Index " << index << reset << endl;

    // Criando uma blockedState nova com valores atualizados de pcbTableIndex
    queue<PriorityProcessItem> newBlockedQueue;
    while (!blockedState.empty()) {
        PriorityProcessItem pItem = blockedState.front();
        if (Setup::isDebug()) cout << magenta << "Blocked encontrado item com index " << pItem.pcbTableIndex << reset << endl;

        if (pItem.pcbTableIndex > index) pItem.pcbTableIndex--;
        newBlockedQueue.push(pItem);
        blockedState.pop();
    }
    blockedState = newBlockedQueue;

    // Criando uma readyState nova com valores atualizados de pcbTableIndex
    priority_queue<PriorityProcessItem> newReadyState;
    while (!readyState.empty()) {
        PriorityProcessItem pItem = readyState.top();
        if (Setup::isDebug()) cout << magenta << "Ready encontrado item com index " << pItem.pcbTableIndex << reset << endl;

        if (pItem.pcbTableIndex > index) pItem.pcbTableIndex--;
        newReadyState.push(pItem);
        readyState.pop();
    }
    readyState = newReadyState;
}

// Remove o processo atual da tabela de processos, do runningState e da CPU
void ProcessManager::removeCurrentProcess(void) {
    int elementIndex = runningState.pcbTableIndex;

    // Remove da tabela de processos
    pcbTable.erase(pcbTable.begin() + elementIndex);

    // Desalocando memória do processo
    delete runningState.process;

    // Como um processo foi finalizado, adicionamos o tempo atual na lista de retornos
    returnTimes.push_back(time);

    // Devemos também remover o processo da cpu e do runningState, já que ele já foi encerrado.
    runningState = {};
    cpu.changeProcess(NULL, time);

    // Todos elementos depois de index devem ser reindexados em: readyState e blockedState
    reindexStructures(elementIndex);
}

// Muda o processo que está rodando na CPU para o proximo na fila de readystate
void ProcessManager::contextChange(void) {
    // Se a fila de prontos estiver vazia, não há processos a se alternar.
    if (Setup::isDebug()) {
        cout << magenta << "[DEBUG PM] Context Change! ReadyState Size: " << readyState.size();
        cout << ", " << readyState.top().process->id << ", " << readyState.top().valid << reset << endl;
    }

    // Se não há ninguem na fila de prontos, não há o que fazer.
    if (readyState.empty()) return;

    PriorityProcessItem ppItem = runningState;
	PriorityProcessItem nextPpItem = readyState.top();
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Context Change - Current Process: " << ppItem.process << reset << endl;
    if (Setup::isDebug()) cout << magenta << "[DEBUG PM] Context Change - Next Process: " << nextPpItem.process << reset << endl;

    readyState.pop();
	if (ppItem.valid) readyState.push(ppItem);

	runningState = nextPpItem;
	cpu.changeProcess(runningState.process, time);
}
