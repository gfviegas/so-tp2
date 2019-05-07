#ifndef simulatedProcess_hpp
#define simulatedProcess_hpp

#include "bits/stdc++.h"

static int COUNT_ID = -1;
typedef enum STATE
{
	BLOCKED,
	UNBLOCKED
} State;

using namespace std;

class SimulatedProcess
{
private:
	int id;
	int pc;
	int n;
	string *program;

	// confirmar esses atributos na estutura correta
	int masterId;
	int priority;
	State state;
	int initTime;
	int cpuTime;

	void setProgram(int masterId, string *program, int pc);
	void init();
	void set(int value);
	void add(int value);
	void sub(int value);
	void block();
	void end(SimulatedProcess **process);
	SimulatedProcess *fork(int n);
	void read(string file);

public:
	SimulatedProcess();
	SimulatedProcess(string rawProgram);

	void readComand(void);
};

#endif /* simulatedProcess_hpp */
