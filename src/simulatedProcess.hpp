#ifndef simulatedProcess_h
#define simulatedProcess_h

class SimulatedProcess {
	private:
		/* data */

	public:
		int id;
		int pc;
		int n;
		String program;

		SimulatedProcess (arguments);
		virtual ~SimulatedProcess ();

		String readComand(void);
		void set(int value);
		void add(int value);
		void sub(int value);
		void block(void);
		void end(void);
		void fork(void);
		void read(void);
};

#endif /* simulatedProcess_h */
