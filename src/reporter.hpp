#ifndef reporter_hpp
#define reporter_hpp

#include "processManager.hpp"
#include "util/logger.hpp"
#include "pcbTableItem.hpp"
#include <iomanip>

using namespace std;
class Reporter {
	private:
		static void printReporterHeader(void);
		static void printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState);
		static void printProccess(PcbTableItem pItem);
		static void printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState);
	public:
		Reporter (void);
		static void print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState);
		static void end();
};

#endif /* reporter_hpp */
