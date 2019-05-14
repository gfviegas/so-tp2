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
		void print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState);
		void printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState);
		void printRunningProcess(PcbTable pcbtab, PriorityProcessItem runningState);
		void printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState);
};

#endif /* reporter_hpp */
