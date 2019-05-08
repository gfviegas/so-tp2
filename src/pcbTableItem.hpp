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
		int priority;
		STATE state;
		int initTime;
		int cpuTime;

	public:
		//métodos
		PcbTableItem(int id, int mId, int *n, int *programCounter, int initialTime);

};

// struct PcbTIComp {
// 	// Overload do operator pra fila de prioridades
// 	bool operator<(const PcbTableItem& a, const PcbTableItem& b) {
// 		return a.priority < b.priority;
// 	}
// };

typedef vector<PcbTableItem> PcbTable;
#endif /* pcbTable_hpp */
