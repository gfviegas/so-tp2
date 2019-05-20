#ifndef cpu_hpp
#define cpu_hpp

#include "setup.hpp"

// Forward Declarations
class SimulatedProcess;

class Cpu {
	private:

	public:
		SimulatedProcess* process;

		// Tempo total em que o processo atual esta rodando na CPU no contexto atual
		int processTime;

		// Tempo que o processo atual começou a rodar no contexto atual
		int startTime;

        // Constructor
		Cpu (void);

        /**
         * Altera o processo em execução na CPU
         * @param process     Processo a ser executada na CPU
         * @param currentTime Tempo atual pra definir o tempo de início do processo na CPU
         */
		void changeProcess(SimulatedProcess* process, int currentTime);

        /**
         * Requisita o processo a executar seu próximo comando
         */
        void nextCommand(void);
};

#endif /* cpu_hpp */
