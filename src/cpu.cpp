#include "cpu.hpp"

#include "simulatedProcess.hpp"
// Constructor
Cpu::Cpu(void) {
	processTime = 0;
	startTime = 0;
}

void Cpu::changeProcess(SimulatedProcess* process, int currentTime) {
	this->process = process;
	processTime = 0;
	startTime = currentTime;
}

void Cpu::nextCommand(void) {
    if (process == NULL) return;

	process->readComand();
    if (Setup::isDebug() && process != NULL) cout << magenta << "[DEBUG CPU] N: " << process->n << ", &N = " << &(process->n) << reset << endl;
	processTime++;
}
