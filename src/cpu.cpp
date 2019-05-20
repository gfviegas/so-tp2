#include "cpu.hpp"
#include "simulatedProcess.hpp"

// Constructor
Cpu::Cpu(void) {
	processTime = 0;
	startTime = 0;
}

// Altera o processo em execução na CPU
void Cpu::changeProcess(SimulatedProcess* process, int currentTime) {
	this->process = process;
	processTime = 0;
	startTime = currentTime;
}

// Requisita o processo a executar seu próximo comando
void Cpu::nextCommand(void) {
    if (process == NULL) return;

	process->readComand();
    if (Setup::isDebug() && process != NULL) cout << magenta << "[DEBUG CPU] N: " << process->n << ", &N = " << &(process->n) << reset << endl;
	processTime++;
}
