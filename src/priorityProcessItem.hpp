/**
 * Definição da estrutura que é utilizada nas filas do Process Manager
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef priorityProcessItem_hpp
#define priorityProcessItem_hpp

#include "simulatedProcess.hpp"
#include "politics.hpp"

using namespace std;
typedef struct PriorityProcessItem {
    // Ponteiro para a prioridade do processo, armazenado na tabela de processos.
    int *priority;

    // Índice da tabela de processo
    int pcbTableIndex;

    // Ponteiro do processo, necessário pra que possamos passá-la pra CPU
    SimulatedProcess *process;

    // Flag de validação pra verificar se é uma estrutura alocada pelo PM ou a inicial
    bool valid;

    // Por default, ela é inválida.
    PriorityProcessItem() : valid(false) {};

    /**
     * Operação de comparação para std::priority_queue. Varia dependendo da configuração do programa
     * @param Setup::politic [description]
     */
    bool operator<(const PriorityProcessItem& item) const {
        switch (Setup::politic) {
            case Politics::PRIORITY_DEFAULT:
                return priority < item.priority;
            case Politics::SHORTEST:
                return process->getProgramSize() < item.process->getProgramSize();
            case Politics::LEAST_USED:
                return process->cpuTime < item.process->cpuTime;
        }

        // Caso default
        return priority < item.priority;
    }
} PriorityProcessItem;

#endif /* priorityProcessItem_hpp */
