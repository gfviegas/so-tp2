#include "reporter.hpp"

// Constructor
Reporter::Reporter(void) {
}

void Reporter::print(int time, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState){
    printLine();
    cout << "The current system state is as follows";
    printLine();
    cout << "Current time: " << time;

}

void Reporter::printProcessList(PcbTable pcbtab, queue<PriorityProcessItem> processList) {
    int i;
    for( i = 0; i < processList.size(); i++){
        cout << pcbtab[processList[i].pcbTableIndex].pid << ",";
        cout << pcbtab[processList[i].pcbTableIndex].getMasterId() << ",";
        cout << pcbtab[processList[i].pcbTableIndex].priority << ",";
        cout << pcbtab[processList[i].pcbTableIndex].getValue() << ",";
        cout << pcbtab[processList[i].pcbTableIndex].getInitTime() << ",";
        cout << pcbtab[processList[i].pcbTableIndex].getCpuTime();
    }
}
