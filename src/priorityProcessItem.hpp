/**
 * Definição das configurações do sistema
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
    int *priority;
    int pcbTableIndex;
    SimulatedProcess *process;
    bool valid;

    PriorityProcessItem() : valid(false) {};

    bool operator<(const PriorityProcessItem& item) const {

        switch (Setup::politic) {
            case Politics::PRIORITY_DEFAULT:
                return priority < item.priority;
            case Politics::SHORTEST:
                return process->pc < item.process->pc;
            case Politics::LEAST_USED:
                return process->cpuTime < item.process->cpuTime;
        }
        return priority < item.priority;
    }
} PriorityProcessItem;

#endif /* priorityProcessItem_hpp */
