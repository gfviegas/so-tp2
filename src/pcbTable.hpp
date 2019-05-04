#ifndef pcbTable_hpp
#define pcbTable_hpp

#include "simulatedProcess.hpp"

class PcbTable {
	private:
		/* data */

	public:
		SimulatedProcess *process;
		int masterId;
		int priority;
		int state;
		int initTime;
		int cpuTime;

		PcbTable (void);
		virtual ~PcbTable ();
};

#endif /* pcbTable_hpp */
