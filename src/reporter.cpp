#include "reporter.hpp"

// Constructor
Reporter::Reporter(void) {
}

void Reporter::print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState){
    printLine(66);
    cout << blue << setw(5) << right << "The current system state is as follows:";
    printLine(66);

    cout << blue << "CURRENT TIME: " << green << time << reset << endl;

    cout << endl << blue << "RUNNING PROCESS:" << reset << endl;
    printReporterHeader();
    printProccess(pcbtab[runningState.pcbTableIndex]);
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

void Reporter::printReporterHeader(void) {
    cout << cyan << setw(5) << right << "PID" << " | ";
    cout << cyan << setw(5) << right << "PPID" << " | ";
    cout << cyan << setw(10) << right << "Priority" << " | ";
    cout << cyan << setw(8) << right << "Value" << " | ";
    cout << cyan << setw(10) << right << "Start Time" << " | ";
    cout << cyan << setw(10) << right << "CPU Time" << " | " << reset << endl;
}

void Reporter::printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState) {
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

void Reporter::printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, int runningIndex){
    int i = 0;
    while (i <= 3) {
        printLine(66, '-');
        cout << blue << setw(40) << right << "Priority " << i << endl;
        printLine(66, '-');

        for (int j = 0; j < (int) pcbtab.size(); j++) {
            if (pcbtab[j].priority == i && j != runningIndex)
                printProccess(pcbtab[j]);
        }

        i++;
    }
}

void Reporter::end(vector<int> returnTimes) {
    double average = (accumulate(returnTimes.begin(), returnTimes.end(), 0) / returnTimes.size());

    // Imprimir o tempo médio do ciclo
    cout << blue << "Tempo médio do ciclo: " << green << average << reset << endl;
}
