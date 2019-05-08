#include "pcbTableItem.hpp"

// Constructor
PcbTableItem::PcbTableItem(SimulatedProcess *process, int initialTime)
{
    pid = process->id;
    masterId = process->masterId;
    pc = &process->pc;
    priority = 0;
    state = UNBLOCKED;
    initTime = initialTime;
    cpuTime = 0;
}
