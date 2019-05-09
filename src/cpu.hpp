#ifndef cpu_hpp
#define cpu_hpp

class Cpu {
	private:

	public:
		SimulatedProcess* process;

		// Tempo total em que o processo atual esta rodando na CPU no contexto atual
		int processTime;

		// Tempo que o processo atual começou a rodar no contexto atual
		int startTime;

		Cpu (void);
		void changeProcess(SimulatedProcess* process, int currentTime);
		void nextCommand(void);
};

#endif /* cpu_hpp */
