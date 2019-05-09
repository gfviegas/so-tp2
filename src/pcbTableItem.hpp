#ifndef pcbTableItem_hpp
#define pcbTableItem_hpp

#include "simulatedProcess.hpp"
#include "<vector>"

using namespace std;
class PcbTableItem {
	private:
		/* data */
		int pid;
		int masterId;
		int *pc;
		int *n;
		int initTime;
		int *cpuTime;

		// "Especiais"
		int priority;
		STATE state;
	public:
		//métodos
		PcbTableItem(int pid, int masterId, int *pc, int *n, int *cpuTime, int initTime);

};

typedef struct priorityProcessItem {
	int priority;
	int pcbTableIndex;

	bool operator<(const priorityProcessItem& item) const {
        return priority < item.priority;
    }
} priorityProcessItem;

typedef vector<PcbTableItem> PcbTable;
#endif /* pcbTable_hpp */
