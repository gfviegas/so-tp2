#include "reporter.hpp"
#define PRIORITY_MAX_VALUE 12
// Constructor
Reporter::Reporter(void) {
}

void Reporter::print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState){
    printLineAsterisc();
    cout << "The current system state is as follows:";
    printLineAsterisc();
    cout << blue << "CURRENT TIME: " << green << time << reset << endl;

    cout << blue << "RUNNING PROCESS:" << reset << endl;
    printReporterHeader();
    printProccess(pcbtab[runningState.pcbTableIndex]);
    cout << blue << "BLOCKED PROCESSES:" << reset << endl;
    printReporterHeader();
    printBlockedQueue(pcbtab, blockedState);
    cout << blue << "PROCESSES READY TO EXECUTE:" << reset << endl;
    printReporterHeader();
    printPriorityQueue(pcbtab, readyState);

    printLineAsterisc();
}

void Reporter::printReporterHeader(void) {
    cout << endl;
    cout << cyan << setw(5) << right << "PID" << " | ";
    cout << cyan << setw(5) << right << "PPID" << " | ";
    cout << cyan << setw(10) << right << "Priority" << " | ";
    cout << cyan << setw(8) << right << "Value" << " | ";
    cout << cyan << setw(10) << right << "Start Time" << " | ";
    cout << cyan << setw(10) << right << "CPU Time" << " | " << reset << endl;
}

void Reporter::printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState) {
    cout << "Queue of blocked processes: \n";
    for (int i = 0; i < (int) blockedState.size(); i++) {
        printProccess(pcbtab[blockedState.front().pcbTableIndex]);
        blockedState.pop();
    }
}

void Reporter::printProccess(PcbTableItem pItem) {
    //impressao do processo rodando
    cout << yellow << setw(5) << right << pItem.pid << " | ";
    cout << yellow << setw(5) << right << pItem.getMasterId() << " | ";
    cout << yellow << setw(10) << right << pItem.priority << " | ";
    cout << yellow << setw(8) << right << pItem.getValue() << " | ";
    cout << yellow << setw(10) << right << pItem.getInitTime() << " | ";
    cout << yellow << setw(10) << right << pItem.getCpuTime() << reset << endl;
}

void Reporter::printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState){
    int i = 0;
    while (i <= PRIORITY_MAX_VALUE) {
        cout << "Queue of process with priority " << i << ":" << endl;
        while (pcbtab[readyState.top().pcbTableIndex].priority == i) {
            printProccess(pcbtab[readyState.top().pcbTableIndex]);
            readyState.pop();
        }

        i++;
    }
}

void Reporter::end() {
    // imprimir o tempo médio do ciclo
    cout << "tempo médio do ciclo" << endl;
    exit(1);
}
