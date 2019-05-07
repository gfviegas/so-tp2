#ifndef pcbTable_hpp
#define pcbTable_hpp

#include "simulatedProcess.hpp"

class PcbTable
{
private:
	/* data */

public:
	list<SimulatedProcess> processes;

	PcbTable(void);
	void add(SimulatedProcess process);
};

#endif /* pcbTable_hpp */
