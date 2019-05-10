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
	process->readComand();
	processTime++;
}
