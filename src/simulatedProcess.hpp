#ifndef simulatedProcess_hpp
#define simulatedProcess_hpp

#include <string>

using namespace std;
class SimulatedProcess {
	private:
		/* data */

	public:
		int id;
		int pc;
		int n;
		string program;

		SimulatedProcess (void);

		string readComand(void);
		void set(int value);
		void add(int value);
		void sub(int value);
		void block(void);
		void end(void);
		void fork(void);
		void read(void);
};

#endif /* simulatedProcess_hpp */
