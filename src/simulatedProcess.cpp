#include "simulatedProcess.hpp"

#include "util/logger.hpp"

/**
 * Inicializa um processo simulado
 */
void SimulatedProcess::init()
{
    id = ++COUNT_ID;
    pc = -1;
    n = 0;
    blocked = false;
}

// Constructor
SimulatedProcess::SimulatedProcess()
{
    init();
}

SimulatedProcess::SimulatedProcess(string rawProgram)
{
    init();

    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(rawProgram);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, '\n'))
    {
        tokens.push_back(intermediate);
    }

    program = new string[tokens.size()];

    // Printing the token vector
    for (int i = 0; i < tokens.size(); i++)
        program[i] = tokens[i];
}

/**
 * Seta um novo programa no sistema
 * @param {String} p programa do processo simulado
 */
void SimulatedProcess::setProgram(string *p)
{
    program = p;
}

/**
 * Incrementa PC e lê um comando do processo simulado
 * @return {String} comando na posição do PC
 */
string SimulatedProcess::readComand(void)
{
    pc++;
    return program[pc];
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
void SimulatedProcess::block(bool block)
{
    blocked = block;
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
SimulatedProcess *SimulatedProcess::fork(void)
{
    SimulatedProcess *forkedProcess = new SimulatedProcess;
    forkedProcess->setProgram(program);
    return forkedProcess;
}

void SimulatedProcess::read(void)
{
    // R
    // deve substituir o conteúdo do program pelo arquivo lido
}
