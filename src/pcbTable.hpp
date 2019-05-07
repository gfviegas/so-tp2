#ifndef pcbTable_hpp
#define pcbTable_hpp

#include "simulatedProcess.hpp"

class PcbTable {
	private:
		/* data */

	public:
		list<SimulatedProcess> process;

		PcbTable (void);
};

#endif /* pcbTable_hpp */
