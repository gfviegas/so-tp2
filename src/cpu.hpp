#ifndef cpu_hpp
#define cpu_hpp

class Cpu {
	private:

	public:
		// SimulatedProcess* process;
		int processTime;
		int executedTime;


		Cpu (void);
		virtual ~Cpu ();
};

#endif /* cpu_hpp */
