#include "pcbTableItem.hpp"

// Constructor
PcbTableItem(int id, int mId, int *n, int *programCounter, int *initTime, int *cpuTime) {
    pid = id;
    masterId = mId;
    n = n;
    pc = programCounter;
    priority = 0;
    state = UNBLOCKED;
    this->initTime = initTime;
	*cpuTime = 0;
    this->cpuTime = cpuTime;
}
