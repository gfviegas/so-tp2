#include "reporter.hpp"
#define PRIORITY_MAX_VALUE 12
// Constructor
Reporter::Reporter(void) {
}

void Reporter::print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState){
    printLine();
    cout << "The current system state is as follows";
    printLine();
    cout << "Current time: " << time << "\n";
    this->printRunningProcess(pcbtab, runningState);
    cout << "Blocked Process:\n";
    this->printBlockedQueue(pcbtab, blockedState);
    cout << "Process Ready to Execute";

}

void Reporter::printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState) {
    int i;
    cout << "Queue of blocked processes: \n";
    for( i = 0; i < blockedState.size(); i++){
        cout << pcbtab[blockedState.front().pcbTableIndex].pid << ",";
        cout << pcbtab[blockedState.front().pcbTableIndex].getMasterId() << ",";
        cout << pcbtab[blockedState.front().pcbTableIndex].priority << ",";
        cout << pcbtab[blockedState.front().pcbTableIndex].getValue() << ",";
        cout << pcbtab[blockedState.front().pcbTableIndex].getInitTime() << ",";
        cout << pcbtab[blockedState.front().pcbTableIndex].getCpuTime();
        blockedState.pop();
    }
}

void Reporter::printRunningProcess(PcbTable pcbtab, PriorityProcessItem runningState){
    cout << "Running Process\n";
    //impressao do processo rodando
    cout << pcbtab[runningState.pcbTableIndex].pid << ",";
    cout << pcbtab[runningState.pcbTableIndex].getMasterId() << ",";
    cout << pcbtab[runningState.pcbTableIndex].priority << ",";
    cout << pcbtab[runningState.pcbTableIndex].getValue() << ",";
    cout << pcbtab[runningState.pcbTableIndex].getInitTime() << ",";
    cout << pcbtab[runningState.pcbTableIndex].getCpuTime() << "\n";
}

void Reporter::printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState){
    int i = 0;
    while(i <= PRIORITY_MAX_VALUE){
        while(pcbtab[readyState.top().pcbTableIndex].priority == i){
            cout << "Qeue of process with priority " << i << "\n";
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
