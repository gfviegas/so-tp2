#include "pcbTableItem.hpp"

// Constructor
PcbTableItem::PcbTableItem(int id, int mId, int value, int *programCounter, int initialTime)
{
    pid = id;
    masterId = mId;
    n = value;
    pc = programCounter;
    priority = 0;
    state = UNBLOCKED;
    initTime = initialTime;
    cpuTime = 0;
}
