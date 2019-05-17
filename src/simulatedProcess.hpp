#ifndef simulatedProcess_hpp
#define simulatedProcess_hpp

#include "util/manstring.hpp"
// #include "processManager.hpp"

// Forward Declarations
class ProcessManager;

using namespace std;
static int COUNT_ID = -1;

class SimulatedProcess {
    private:
    	string *program;

    	void setProgram(int masterId, string *program, int pc, int value);
    	void init(void);
    	void set(int value);
    	void add(int value);
    	void sub(int value);
    	void block(void);
    	void end(void);
    	SimulatedProcess *fork(int n);
    	void read(string file);

    public:
    	int id;
    	int pc;
    	int n;
    	int masterId;
    	int cpuTime;

    	SimulatedProcess(void);
    	SimulatedProcess(string rawProgram);

    	void readComand(void);
};

#endif /* simulatedProcess_hpp */
