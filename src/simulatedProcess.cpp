#include "simulatedProcess.hpp"
#include "processManager.hpp"

/**
 * Inicializa um processo simulado
 */
void SimulatedProcess::init(void) {
    id = ++COUNT_ID;
    masterId = -1;
    pc = -1;
    n = 0;
	  cpuTime = 0;
}

// Constructor
SimulatedProcess::SimulatedProcess(void) {
    init();
}

SimulatedProcess::SimulatedProcess(string rawProgram) {
    init();
    program = explode(rawProgram, '\n');
}

/**
 * Seta um novo programa no sistema
 * @param {String} p programa do processo simulado
 */
void SimulatedProcess::setProgram(int id, string *p, int programCounter, int value) {
    masterId = id;
    program = p;
    pc = programCounter;
    n = value;
}

/**
 * Incrementa PC e lê um comando do processo simulado
 * @return {String} comando na posição do PC
 */
void SimulatedProcess::readComand(void) {
    pc++;
    cpuTime++;
    int n;
    string *command = explode(program[pc], ' ');

    // TODO: Verificar se exisite command[0], command[0].at(0)
    if (Setup::isDebug()) cout << magenta <<  "[DEBUG SP] " << command[0].at(0) << endl;
    switch (command[0].at(0)) {
        case 'S':
            n = atoi(command[1].c_str());
            set(n);
            break;
        case 'A':
            n = atoi(command[1].c_str());
            add(n);
            break;
        case 'D':
            n = atoi(command[1].c_str());
            sub(n);
            break;
        case 'B':
            block();
            break;
        case 'E':
            end();
            break;
        case 'F':
            n = atoi(command[1].c_str());
            fork(n - 1);
            break;
        case 'R':
            read(command[1]);
            break;
    }
}

/**
 * Seta o valor da variável n para o value passado (S)
 * @param {int} value novo valor
 */
void SimulatedProcess::set(int value) {
    n = value;
    if (Setup::isDebug()) cout << magenta << "[DEBUG SP] SET: " << value << ", " << this->n << reset << endl;
}

/**
 * Incrementa o valor da variável n pelo value passado (A)
 * @param {int} value novo valor
 */
void SimulatedProcess::add(int value) {
    n += value;
    if (Setup::isDebug()) cout << magenta << "[DEBUG SP] ADD: " << value << ", " << this->n << reset << endl;
}

/**
 * Decrementa o valor da variável n pelo value passado (D)
 * @param {int} value novo valor
 */
void SimulatedProcess::sub(int value) {
    n -= value;
    if (Setup::isDebug()) cout << magenta << "[DEBUG SP] SUB: " << value << ", " << this->n << reset << endl;
}

/**
 * Bloqueia ou desbloqueia um processo simulado (B)
 * @param {bool} block bloqueia ou desbloqueia processo simulado
 */
void SimulatedProcess::block() {
    ProcessManager::block();
}

/**
 * Encerra o processo simulado passado por parâmetro (E)
 * @param {SimulatedProcess **} ponteiro duplo de um processo simulado
 */
void SimulatedProcess::end() {
	ProcessManager::removeProcess(this->id, this);
}

/**
 * Cria um novo processo simulado a partir do processo pai (F)
 * @returns {SimulatedProcess*} processo simulado
 */
SimulatedProcess *SimulatedProcess::fork(int skip) {
    SimulatedProcess *forkedProcess = new SimulatedProcess;
    forkedProcess->setProgram(id, program, pc, n);

    // pula instruções do processo pai
    pc += skip;

	// Cadastra o processo criado na tabela de processos.
	ProcessManager::insertProcess(forkedProcess);

    return forkedProcess;
}

/**
 * Substitui o programa do processo simulado pelo arquivo passado (R)
 * @param {string} file arquivo que será lido
 */
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
