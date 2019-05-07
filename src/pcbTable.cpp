#include "pcbTable.hpp"

// Constructor
PcbTable::PcbTable(void)
{
}

void PcbTable::add(SimulatedProcess process)
{
    processes.push_back(process);
}