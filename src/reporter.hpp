#ifndef reporter_hpp
#define reporter_hpp

#include "processManager.hpp"
#include "util/logger.hpp"
#include "pcbTableItem.hpp"

using namespace std;
class Reporter {
	private:
		static void printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState);
		static void printRunningProcess(PcbTable pcbtab, PriorityProcessItem runningState);
		static void printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState);
	public:
		Reporter (void);
		static void print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState);
		static void end();
};

#endif /* reporter_hpp */
