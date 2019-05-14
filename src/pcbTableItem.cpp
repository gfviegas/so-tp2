#include "pcbTableItem.hpp"

// Constructor
PcbTableItem::PcbTableItem(int id, int mId, int *n, int *pc, int initTime, int *cpuTime) {
    pid = id;
    masterId = mId;
    this->n = n;
    this->pc = pc;
    priority = 0;
    this->initTime = initTime;
    *cpuTime = 0;
    this->cpuTime = cpuTime;
}

int PcbTableItem::increasePriority(void) {
    priority++;
    return getPriority();
}

int PcbTableItem::decreasePriority(void) {
    priority--;
    return getPriority();
}

int PcbTableItem::getPriority(void) {
    return priority;
}

int PcbTableItem::getCpuTime(void) {
    return *cpuTime;
}

int PcbTableItem::getMasterId(void) {
    return masterId;
}

int PcbTableItem::getValue(void){
    return *n;
}

int PcbTableItem::getInitTime(void){
    return initTime;
}
