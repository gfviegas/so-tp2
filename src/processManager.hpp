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

        /**
         * Q - Fim de uma unidade de tempo
         * Executa a próxima instrução do processo simulado.
         */
        static void execute(void);

        /**
         * U - Desbloqueia o primeiro processo simulado na fila bloqueada.
         */
        static void unblock(void);

        /**
         * P - Imprime o estado atual do sistema.
         */
        static void print(void);

        /**
         * T - Imprime o tempo médio do ciclo e finaliza o sistema.
         */
        static void endExecution(void);

        /**
        * Muda o processo que está rodando na CPU para o proximo na fila de readystate
        */
        static void contextChange(void);

        /**
         * Calcula o quantum restante de um item, baseado na sua prioridade
         * @param  item Item a ser consultado
         * @return      Valor de quantum restante pro processo
         */
        static int remainingQuantum(PcbTableItem item);

        // Construtor
        ProcessManager(void);

    public:
        /**
         * Inicializa o PM, configurando o primeiro processo.
         */
        static void init(void);

        /**
         * Recebe um comando e chama o método devido relacionado a este comando.
         * @param command Caracter representando a tarefa a ser executada pelo PM
         */
        static void runCommand(char command);

        /**
         * Insere um processo na tabela de processos e na lista de prontos.
         * @param process Ponteiro para o processo a ser inserido
         */
        static void insertProcess(SimulatedProcess* process);

        /**
         * Reindexa as estruturas que armazena o pcbTableIndex após a remoção de um item
         * @param index Índice do elemento que foi removido
         */
        static void reindexStructures(int index);

        /**
         * Remove o processo atual da tabela de processos, do runningState e da CPU
         */
        static void removeCurrentProcess(void);

        /**
         * Chamado pelo SP pra atualizar blockedState e atualizar prioridades de acordo com a politica.
         */
        static void block(void);
};

#endif /* processManager_hpp */
