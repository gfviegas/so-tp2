#include "reporter.hpp"
#define PRIORITY_MAX_VALUE 12
// Constructor
Reporter::Reporter(void) {
}

void Reporter::print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState){
    printLineAsterisc();
    cout << "The current system state is as follows:";
    printLineAsterisc();
    cout << "CURRENT TIME: " << time << "\n";
    cout << "RUNNING PROCESS:\n";
    this->printRunningProcess(pcbtab, runningState);
    cout << "BLOCKED PROCESSES:\n";
    this->printBlockedQueue(pcbtab, blockedState);
    cout << "PROCESSES READY TO EXECUTE:\n";
    this->printPriorityQueue(pcbtab, readyState);
    printLineAsterisc();
}

void Reporter::printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState) {
    int i;
    cout << "Queue of blocked processes: \n";
    for( i = 0; i < blockedState.size(); i++){
        cout << pcbtab[blockedState.front().pcbTableIndex].pid << ", ";
        cout << pcbtab[blockedState.front().pcbTableIndex].getMasterId() << ", ";
        cout << pcbtab[blockedState.front().pcbTableIndex].priority << ", ";
        cout << pcbtab[blockedState.front().pcbTableIndex].getValue() << ", ";
        cout << pcbtab[blockedState.front().pcbTableIndex].getInitTime() << ", ";
        cout << pcbtab[blockedState.front().pcbTableIndex].getCpuTime() << "\n";
        blockedState.pop();
    }
}

void Reporter::printRunningProcess(PcbTable pcbtab, PriorityProcessItem runningState){
    //impressao do processo rodando
    cout << pcbtab[runningState.pcbTableIndex].pid << ", ";
    cout << pcbtab[runningState.pcbTableIndex].getMasterId() << ", ";
    cout << pcbtab[runningState.pcbTableIndex].priority << ", ";
    cout << pcbtab[runningState.pcbTableIndex].getValue() << ", ";
    cout << pcbtab[runningState.pcbTableIndex].getInitTime() << ", ";
    cout << pcbtab[runningState.pcbTableIndex].getCpuTime() << "\n";
}

void Reporter::printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState){
    int i = 0;
    while(i <= PRIORITY_MAX_VALUE){
        while(pcbtab[readyState.top().pcbTableIndex].priority == i){
            cout << "Queue of process with priority " << i << ":\n";
            cout << pcbtab[readyState.top().pcbTableIndex].pid << ",";
            cout << pcbtab[readyState.top().pcbTableIndex].getMasterId() << ",";
            cout << pcbtab[readyState.top().pcbTableIndex].priority << ",";
            cout << pcbtab[readyState.top().pcbTableIndex].getValue() << ",";
            cout << pcbtab[readyState.top().pcbTableIndex].getInitTime() << ",";
            cout << pcbtab[readyState.top().pcbTableIndex].getCpuTime() << "\n";
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
