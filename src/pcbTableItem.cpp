/**
 * Item interno da tabela de processos
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "pcbTableItem.hpp"

// Constructor
PcbTableItem::PcbTableItem(int id, int mId, int *pc, int *n, int initTime, int *cpuTime) {
    pid = id;
    masterId = mId;
    this->pc = pc;
    this->n = n;
    priority = 0;
    this->initTime = initTime;
    *cpuTime = 0;
    this->cpuTime = cpuTime;
}

// Aumenta a prioridade, diminuindo o seu valor inteiro se possível
int PcbTableItem::increasePriority(void) {
    if (priority > MIN_PRIORITY) priority--;
    return getPriority();
}

// Diminui a prioridade, aumentando o seu valor inteiro se possível
int PcbTableItem::decreasePriority(void) {
    if (priority < MAX_PRIORITY) priority++;
    return getPriority();
}

// Recupera o tempo de CPU
int PcbTableItem::getCpuTime(void) {
    return *cpuTime;
}

// Recupera a prioridade
int PcbTableItem::getPriority(void) {
    return priority;
}

// Recupera o PID do pai do processo
int PcbTableItem::getMasterId(void) {
    return masterId;
}

// Recupera o valor do inteiro manipulado pelo processo
int PcbTableItem::getValue(void) {
    return *n;
}

// Recupera o tempo de início do processo
int PcbTableItem::getInitTime(void) {
    return initTime;
}
