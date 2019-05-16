#include "pcbTableItem.hpp"

#include <iostream>
// Constructor
PcbTableItem::PcbTableItem(int id, int mId, int *pc, int *n, int initTime, int *cpuTime) {
    pid = id;
    masterId = mId;
    this->pc = pc;
    this->n = n;
    priority = 0;
    this->initTime = initTime;
    *cpuTime = 0;
    this->cpuTime = cpuTime;

    std::cout << "[PCTi] *N = " << *n << "N = " << n << std::endl;
}

int PcbTableItem::increasePriority(void) {
    if (priority < MAX_PRIORITY) priority++;
    return getPriority();
}

int PcbTableItem::decreasePriority(void) {
    if (priority > MIN_PRIORITY) priority--;
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

int PcbTableItem::getValue(void) {
    return *n;
}

int PcbTableItem::getInitTime(void) {
    return initTime;
}
