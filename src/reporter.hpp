#ifndef reporter_hpp
#define reporter_hpp

#include "processManager.hpp"
#include "util/logger.hpp"

using namespace std;
class Reporter {
	private:
		/* data */

	public:
		Reporter (void);
		void print(ProcessManager pm);
};

#endif /* reporter_hpp */
