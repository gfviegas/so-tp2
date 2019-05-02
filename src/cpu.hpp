#ifndef cpu_h
#define cpu_h

class Cpu {
	private:

	public:
		SimulatedProcess* process;
		int processTime;
		int executedTime;


		Cpu (arguments);
		virtual ~Cpu ();
};

#endif /* cpu_h */
