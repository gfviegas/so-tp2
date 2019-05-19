/**
 * Reporter - Processo que imprime os dados do sistema
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#ifndef reporter_hpp
#define reporter_hpp

#include <iomanip>
#include <numeric>

#include "processManager.hpp"
#include "util/logger.hpp"
#include "pcbTableItem.hpp"

using namespace std;
class Reporter {
	private:
        /**
         * Imprime o cabeçalho da tabela de processos
         */
		static void printReporterHeader(void);

        /**
         * Dado um certo processo, imprime-o formatado pra tabela
         * @param pItem Elemento da Tabela de Processos
         */
        static void printProccess(PcbTableItem pItem);

        /**
         * Imprime a fila de processos bloqueados
         * @param pcbtab       Tabela de Processos a ser consultada
         * @param blockedState Fila de processos bloqueados
         */
		static void printBlockedQueue(PcbTable pcbtab, queue<PriorityProcessItem> blockedState);

        /**
         * Imprime a fila de processos prontos a serem executados, agrupados por prioridade.
         * @param pcbtab       Tabela de Processos a ser consultada
         * @param readyState   Fila de Prioridade de Processos prontos a serem executados
         * @param runningIndex Índice do processo atualmente em execução na CPU
         */
        static void printPriorityQueue(PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, int runningIndex);
	public:
		Reporter (void);

        /**
         * Método principal de chamada para imprimir o estado atual do sistema
         * @param time         Tempo atual
         * @param pcbtab       Tabela de Processos a ser consultada
         * @param readyState   Fila de Prioridade de Processos prontos a serem executados
         * @param blockedState Fila de processos bloqueados
         * @param runningState Processo atualmente na CPU
         */
		static void print(int time, PcbTable pcbtab, priority_queue<PriorityProcessItem> readyState, queue<PriorityProcessItem> blockedState, PriorityProcessItem runningState);

        /**
         * Calcula e imprime tempo médio de retorno dos processos
         * @param returnTimes Lista do tempo que os processos foram finalizados
         */
        static void end(vector<int> returnTimes);
};

#endif /* reporter_hpp */
