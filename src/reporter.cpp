/**
 * Reporter - Processo que imprime os dados do sistema
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#include "reporter.hpp"

// Constructor
Reporter::Reporter(void) {
}

// Imprime o cabeçalho da tabela de processos
void Reporter::printReporterHeader(void) {
    cout << cyan << setw(5) << right << "PID" << " | ";
    cout << cyan << setw(5) << right << "PPID" << " | ";
    cout << cyan << setw(10) << right << "Priority" << " | ";
    cout << cyan << setw(8) << right << "Value" << " | ";
    cout << cyan << setw(10) << right << "Start Time" << " | ";
    cout << cyan << setw(10) << right << "CPU Time" << " | " << reset << endl;
}

// Dado um certo processo, imprime-o formatado pra tabela
void Reporter::printProccess(PcbTableItem pItem) {
    //impressao do processo rodando
    cout << yellow << setw(5) << right << pItem.pid << " | ";
    cout << yellow << setw(5) << right << pItem.getMasterId() << " | ";
    cout << yellow << setw(10) << right << pItem.priority << " | ";
    cout << yellow << setw(8) << right << pItem.getValue() << " | ";
    cout << yellow << setw(10) << right << pItem.getInitTime() << " | ";
    cout << yellow << setw(10) << right << pItem.getCpuTime() << reset << endl;
}

// Imprime a fila de processos bloqueados
void Reporter::printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState) {
    while (!blockedState.empty()) {
        printProccess(pcbtab[blockedState.front().pcbTableIndex]);
        blockedState.pop();
    }
}

// Imprime a fila de processos prontos a serem executados, agrupados por prioridade.
void Reporter::printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, int runningIndex){
    // TODO: Verificar se o processo está pronto, do jeito que está, vai printar os bloqueados tbm.
    vector<vector<PriorityProcessItem>> priorities{{}, {}, {}, {}};

    while (!readyState.empty()) {
        PriorityProcessItem p = readyState.top();
        readyState.pop();

        cout << red << "Found process " << p.process << " com prioridade " << *(p.priority) << endl;
        int priority = *(p.priority);
        if (priority < 0 || priority > 3) continue;
        priorities[*(p.priority)].push_back(p);
    }

    for (int i = 0; i <= 3; i++) {
        printLine(66, '-');
        cout << blue << setw(40) << right << "Priority " << i;
        printLine(66, '-');

        for (int j = 0; j < (int) priorities[i].size(); j++) {
            printProccess(pcbtab[priorities[i][j].pcbTableIndex]);
        }
    }
}

// Método principal de chamada para imprimir o estado atual do sistema
void Reporter::print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState){
    printLine(66);
    cout << blue << setw(5) << right << "The current system state is as follows:";
    printLine(66);

    cout << blue << "CURRENT TIME: " << green << time << reset << endl;

    cout << endl << blue << "RUNNING PROCESS:" << reset << endl;
    printReporterHeader();
    if (runningState.valid) printProccess(pcbtab[runningState.pcbTableIndex]);
    printLine(66, '-');

    cout << blue << "BLOCKED PROCESSES:" << reset << endl;
    printReporterHeader();
    printBlockedQueue(pcbtab, blockedState);
    printLine(66, '-');

    cout << blue << "PROCESSES READY TO EXECUTE:" << reset << endl;
    printReporterHeader();
    printPriorityQueue(pcbtab, readyState, runningState.pcbTableIndex);

    printLine(66);
}

// Calcula e imprime tempo médio de retorno dos processos
void Reporter::end(vector<int> returnTimes) {
    double average = (returnTimes.size() > 0) ? (accumulate(returnTimes.begin(), returnTimes.end(), 0) / returnTimes.size()) : 0;

    // Imprimir o tempo médio do ciclo
    cout << blue << "Tempo médio do ciclo: " << green << average << reset << endl;
}
