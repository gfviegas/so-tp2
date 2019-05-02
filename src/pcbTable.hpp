#ifndef pcbTable_h
#define pcbTable_h

class PcbTable {
	private:
		/* data */

	public:
		SimulatedProcess *process;
		int masterId;
		int priority;
		int state;
		int initTime;
		int cpuTime;

		PcbTable (arguments);
		virtual ~PcbTable ();
};

#endif /* pcbTable_h */
