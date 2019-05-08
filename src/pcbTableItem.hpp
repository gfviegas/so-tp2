#ifndef pcbTableItem_hpp
#define pcbTableItem_hpp

#include "simulatedProcess.hpp"

class PcbTableItem
{
private:
	/* data */

public:
	int pid;
	int masterId;
	int *pc;
	int n;
	int priority;
	STATE state;
	int initTime;
	int cpuTime;

	//métodos
	PcbTableItem(SimulatedProcess *process, int initialTime);
};

typedef list<PcbTableItem> PcbTable;

#endif /* pcbTable_hpp */
