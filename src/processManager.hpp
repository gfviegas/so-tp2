/**
 * Definição da classe ProcessManager: simula cinco funções de gerenciamento de
 * processos e inicia o processo reporter sempre que precisa imprimir o estado
 * do sistema.
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef processManager_hpp
#define processManager_hpp

#include "cpu.hpp"
#include "pcbTable.hpp"
#include "pcbTableList.hpp"
// #include "reporter.hpp"

using namespace std;

class ProcessManager {
    private:
    public:
        PcbTableList blockedState;
        PcbTableList readyState;
        PcbTable runningState;
        int time;
        Cpu cpu;
        PcbTable pcbTable;
        // Reporter reporter;

        ProcessManager (void);

        void init(void);
        void unblock(void);
        void print(void);
        void endExecution(void);
        void execute(void);
};

#endif /* processManager_hpp */
