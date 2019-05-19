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

#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>

#include "util/logger.hpp"
#include "setup.hpp"
#include "pcbTableItem.hpp"
#include "priorityProcessItem.hpp"
#include "cpu.hpp"

using namespace std;

// Forward Declarations
class SimulatedProcess;

// Declarando
typedef vector<PcbTableItem> PcbTable;

class ProcessManager {
    private:
        // Comando Q - Fim de uma unidade de tempo
        static void execute(void);

        // U - Desbloqueia o primeiro processo simulado na fila bloqueada.
        static void unblock(void);

        // P - Imprime o estado atual do sistema.
        static void print(void);

        // T - Imprime o tempo médio do ciclo e finaliza o sistema.
        static void endExecution(void);

        // Unidade de tempo atual.
        static int time;

        //PID para criar o process reporter
        static pid_t forkPID;

        // CPU
        static Cpu cpu;

        // Tabela de Processos.
        static PcbTable pcbTable;

        // Fila dos indices dos processos em pcbTable que estão prontos
        static priority_queue<PriorityProcessItem> readyState;

        // Fila dos indices dos processos em pcbTable que estão bloqueados
        static queue<PriorityProcessItem> blockedState;

        // Índice do processo em pcbTable que está em execução no momento
        static PriorityProcessItem runningState;

        // Lista com os tempos que os processos foram finalizados
        static vector<int> returnTimes;

        // Troca de contexto
        static void contextChange(void);

        /**
         * Troca de contexto forçando a remoção do processo atual da CPU
         * @param forceRemove Flag se é pra remover o processo rodando na CPU independente se tem ou não processos na fila de pronto
         */
        static void contextChange(bool forceRemove);

        // Construtor
        ProcessManager(void);

    public:
        static void init(void);
        static void runCommand(char command);

        static void insertProcess(SimulatedProcess* process);
        static void removeProcess(int pid, SimulatedProcess* process);

        // Chamado pelo SP pra atualizar blockedState e atualizar prioridades de acordo com a politica.
        static void block(void);
};

#endif /* processManager_hpp */
