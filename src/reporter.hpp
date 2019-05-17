#ifndef reporter_hpp
#define reporter_hpp

#include "processManager.hpp"
#include "util/logger.hpp"
#include "pcbTableItem.hpp"
#include <iomanip>
#include <numeric>

using namespace std;
class Reporter {
	private:
		static void printReporterHeader(void);
		static void printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState);
		static void printProccess(PcbTableItem pItem);
		static void printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, int runningIndex);
	public:
		Reporter (void);
		static void print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState);
		static void end(vector<int> returnTimes);
};

#endif /* reporter_hpp */
