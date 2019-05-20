/**
 * Item interno da tabela de processos
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef pcbTableItem_hpp
#define pcbTableItem_hpp

// Valores minimos - máximos da prioridade
#define MIN_PRIORITY 0
#define MAX_PRIORITY 3

class PcbTableItem {
    private:
        // PID do pai do processo. -1 se for o processo-raiz.
        int masterId;

        // Ponteiro pro ProgramCounter do processo
        int *pc;

        // Ponteiro pro valor do inteiro manipulado pelo processo
        int *n;

        // Tempo de início do processo
        int initTime;

        // Tempo de execução total do processo na CPU
        int *cpuTime;
    public:
        // PID do processo
        int pid;

        // Valor da prioridade (no intervalo [MIN_PRIORITY, MAX_PRIORITY]) do processo
        int priority;

        // Constructor
        PcbTableItem(int id, int mId, int *pc, int *n, int initTime, int *cpuTime);

        /**
         * Aumenta a prioridade, diminuindo o seu valor inteiro se possível
         * @return  Novo valor da prioridade
         */
        int increasePriority(void);

        /**
         * Diminui a prioridade, aumentando o seu valor inteiro se possível
         * @return  Novo valor da prioridade
         */
        int decreasePriority(void);

        /**
        * Recupera o tempo de CPU
        * @return  Valor inteiro do tempo total de execução do processo na CPU
        */
        int getCpuTime(void);

        /**
        * Recupera a prioridade
        * @return  Valor inteiro da prioridade do processo
        */
        int getPriority(void);

        /**
        * Recupera o PID do pai do processo
        * @return  Valor inteiro do parent PID do processo
        */
        int getMasterId(void);

        /**
         * Recupera o valor do inteiro manipulado pelo processo
         * @return  Valor inteiro do value manipulado no processo
         */
        int getValue(void);

        /**
         * Recupera o tempo de início do processo
         * @return  Valor inteiro representando o tempo de início do processo
         */
        int getInitTime(void);
};

#endif /* pcbTable_hpp */
