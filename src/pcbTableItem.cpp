#include "pcbTableItem.hpp"

// Constructor
PcbTableItem::PcbTableItem(SimulatedProcess *process){
    pid = process->id;
    masterId = process->masterId;
    pc = &process->pc;
}
