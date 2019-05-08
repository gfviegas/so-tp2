#ifndef pcbTableItem_hpp
#define pcbTableItem_hpp

#include "simulatedProcess.hpp"

class PcbTableItem
{
private:
	/* data */
	int pid;
	int masterId;
	int *pc;
	int n;
	int priority;
	STATE state;
	int initTime;
	int cpuTime;

public:
	//métodos
	PcbTableItem(int id, int mId, int value, int *programCounter, int initialTime);
};

typedef list<PcbTableItem> PcbTable;

#endif /* pcbTable_hpp */
