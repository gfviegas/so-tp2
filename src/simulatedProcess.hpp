#ifndef simulatedProcess_hpp
#define simulatedProcess_hpp

#include <string>
#include "bits/stdc++.h"

static int COUNT_ID = 0;

using namespace std;

class SimulatedProcess
{
private:
	int id;
	int pc;
	int n;
	bool blocked;
	string *program;

	void setProgram(string *p);

public:
	SimulatedProcess();
	SimulatedProcess(string rawProgram);

	string readComand(void);
	void set(int value);
	void add(int value);
	void sub(int value);
	void block(bool block);
	void end(SimulatedProcess **process);
	SimulatedProcess *fork(void);
	void read(void);
};

#endif /* simulatedProcess_hpp */
