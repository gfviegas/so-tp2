#ifndef reporter_hpp
#define reporter_hpp

#include "processManager.hpp"

class Reporter {
	private:
		/* data */

	public:
		Reporter (void);

		void print(ProcessManager pm);
};

#endif /* reporter_hpp */
