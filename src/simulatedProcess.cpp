/**
 * Módulo do Process Manager, responsável por gerenciar os processos simulados em execução
 * com a orquestração do Commander
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "simulatedProcess.hpp"
#include "processManager.hpp"

// Inicializa um processo simulado
void SimulatedProcess::init(void) {
    id = ++COUNT_ID;
    masterId = -1;
    pc = -1;
    n = 0;
    cpuTime = 0;
}

// Constructors
SimulatedProcess::SimulatedProcess(void) {
    init();
}
SimulatedProcess::SimulatedProcess(string rawProgram) {
    init();
    program = explode(rawProgram, '\n');
}

// Define um novo programa pro processo
void SimulatedProcess::setProgram(int id, string *p, int programCounter, int value) {
    masterId = id;
    program = p;
    pc = programCounter;
    n = value;
}

// Incrementa PC e lê um comando do processo simulado
void SimulatedProcess::readComand(void) {
    pc++;
    cpuTime++;
    int n;
    if (program[pc].empty()) return end();

    string *command = explode(program[pc], ' ');

    // TODO: Verificar se exisite command[0], command[0].at(0)
    if (Setup::isDebug()) cout << magenta <<  "[DEBUG SP] " << command[0].at(0) << endl;
    switch (command[0].at(0)) {
        case 'S':
            n = atoi(command[1].c_str());
            return set(n);
        case 'A':
            n = atoi(command[1].c_str());
            return add(n);
        case 'D':
            n = atoi(command[1].c_str());
            return sub(n);
        case 'B':
            return block();
        case 'E':
            return end();
        case 'F':
            n = atoi(command[1].c_str());
            return (void) fork(n);
        case 'R':
            return read(command[1]);
    }
}

// Seta o valor da variável n para o value passado (S)
void SimulatedProcess::set(int value) {
    n = value;
    if (Setup::isDebug()) cout << magenta << "[DEBUG SP] SET: " << value << ", " << this->n << reset << endl;
}

// Incrementa o valor da variável n pelo value passado (A)
void SimulatedProcess::add(int value) {
    n += value;
    if (Setup::isDebug()) cout << magenta << "[DEBUG SP] ADD: " << value << ", " << this->n << reset << endl;
}

// Decrementa o valor da variável n pelo value passado (D)
void SimulatedProcess::sub(int value) {
    n -= value;
    if (Setup::isDebug()) cout << magenta << "[DEBUG SP] SUB: " << value << ", " << this->n << reset << endl;
}

// Bloqueia este processo simulado (B)
void SimulatedProcess::block() {
    ProcessManager::block();
}

// Encerra esse processo simulado
void SimulatedProcess::end() {
	ProcessManager::removeCurrentProcess();
}

// Cria um novo processo simulado a partir do processo pai (F)
SimulatedProcess *SimulatedProcess::fork(int skip) {
    SimulatedProcess *forkedProcess = new SimulatedProcess;
    forkedProcess->setProgram(id, program, pc, n);

    if (Setup::isDebug()) cout << magenta << "[DEBUG SP] Criado o processo: " << forkedProcess << " com pid " << forkedProcess->id << reset << endl;

    // Pula instruções do processo pai
    pc += skip;

	// Cadastra o processo criado na tabela de processos.
	ProcessManager::insertProcess(forkedProcess);

    return forkedProcess;
}

// Substitui o programa do processo simulado pelo arquivo passado (R)
void SimulatedProcess::read(string file) {
    ifstream stream;
    stream.open(file.c_str());

    if (!stream.is_open()) {
        cout << red << "Arquivo " << file << " não pode ser lido" << endl;
        return;
    }

    string rawProgram;
    char c = stream.get();

    while (stream.good()) {
        rawProgram += c;
        c = stream.get();
    }

    stream.close();

    program = explode(rawProgram, '\n');
    pc = -1;
}

int SimulatedProcess::getProgramSize(void) {
    return program->size();
}
