#include "simulatedProcess.hpp"

#include "util/logger.hpp"

string *explode(string text, char delimiter)
{
    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(text);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, delimiter))
    {
        tokens.push_back(intermediate);
    }

    string *program = new string[tokens.size()];

    // Printing the token vector
    for (int i = 0; i < tokens.size(); i++)
        program[i] = tokens[i];

    return program;
}

/**
 * Inicializa um processo simulado
 */
void SimulatedProcess::init()
{
    id = ++COUNT_ID;
    masterId = -1;
    pc = -1;
    n = 0;
    state = UNBLOCKED;
    initTime = 0;
    cpuTime = 0;
}

// Constructor
SimulatedProcess::SimulatedProcess()
{
    init();
}

SimulatedProcess::SimulatedProcess(string rawProgram)
{
    init();
    program = explode(rawProgram, '\n');
}

/**
 * Seta um novo programa no sistema
 * @param {String} p programa do processo simulado
 */
void SimulatedProcess::setProgram(int masterId, string *program, int pc)
{
    masterId = masterId;
    program = program;
    pc = pc;
}

/**
 * Incrementa PC e lê um comando do processo simulado
 * @return {String} comando na posição do PC
 */
void SimulatedProcess::readComand(void)
{
    pc++;

    string *command = explode(program[pc], ' ');

    switch (command[0].at(0))
    {
    case 'S':
        int n = atoi(command[1].c_str());
        set(n);
        break;
    case 'A':
        int n = atoi(command[1].c_str());
        add(n);
        break;
    case 'D':
        int n = atoi(command[1].c_str());
        sub(n);
        break;
    case 'B':
        block();
        break;
    case 'E':
        break;
    case 'F':
        int n = atoi(command[1].c_str());
        fork(n);
        // adicionar a lista de processos
        break;
    case 'R':
        read(command[1]);
        break;
    default:
        break;
    }
}

/**
 * Seta o valor da variável n para o value passado (S)
 * @param {int} value novo valor
 */
void SimulatedProcess::set(int value)
{
    n = value;
}

/**
 * Incrementa o valor da variável n pelo value passado (A)
 * @param {int} value novo valor
 */
void SimulatedProcess::add(int value)
{
    n += value;
}

/**
 * Decrementa o valor da variável n pelo value passado (D)
 * @param {int} value novo valor
 */
void SimulatedProcess::sub(int value)
{
    n -= value;
}

/**
 * Bloqueia ou desbloqueia um processo simulado (B)
 * @param {bool} block bloqueia ou desbloqueia processo simulado
 */
void SimulatedProcess::block()
{
    state = BLOCKED;

    // adicionar processo a lista de bloqueados
}

/**
 * Encerra o processo simulado passado por parâmetro (E)
 * @param {SimulatedProcess **} ponteiro duplo de um processo simulado
 */
void SimulatedProcess::end(SimulatedProcess **process)
{
    delete *process;
    *process = NULL;
}

/**
 * Cria um novo processo simulado a partir do processo pai (F)
 * @ returns {SimulatedProcess*} processo simulado
 */
SimulatedProcess *SimulatedProcess::fork(int n)
{
    SimulatedProcess *forkedProcess = new SimulatedProcess;
    forkedProcess->setProgram(id, program, pc + 1);

    // pula instruções do processo pai
    pc += n;

    return forkedProcess;
}

void SimulatedProcess::read(string file)
{
    // R
    // deve substituir o conteúdo do program pelo arquivo lido
}
