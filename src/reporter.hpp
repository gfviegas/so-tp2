#ifndef reporter_hpp
#define reporter_hpp

#include "processManager.hpp"
#include "util/logger.hpp"
#include "pcbTableItem.hpp"

using namespace std;
class Reporter {
	private:
		/* data */

	public:
		Reporter (void);
		void print(int time, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState);
		void printProcessList(PcbTable pcbtab, queue<PriorityProcessItem> processList);
};

#endif /* reporter_hpp */
