#include "simulatedProcess.hpp"

// Constructor
SimulatedProcess::SimulatedProcess(void)
{
    pc = 0;
    n = 0;
}

/**
 * Incrementa PC e lê um comando do processo simulado
 * @return {String} comando na posição do PC
 */
string SimulatedProcess::readComand(void)
{
    pc++;

    // deve retornar o program na posição do pc
    return "instrução do programa";
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
 * Bloqueia o processo simulado
 */
void SimulatedProcess::block(void)
{
    // B
    // define status do processo simulado como bloqueado (aguardando entrada)
}

void SimulatedProcess::end(void)
{
    // E
    // finaliza o processo simulado
}

void SimulatedProcess::fork(void)
{
    // F
    // deve criar um novo processo simulado idêntico ao processo pai
}

void SimulatedProcess::read(void)
{
    // R
    // deve substituir o conteúdo do program pelo arquivo lido
}
