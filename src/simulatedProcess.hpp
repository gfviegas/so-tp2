/**
 * Módulo do Process Manager, responsável por gerenciar os processos simulados em execução
 * com a orquestração do Commander
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef simulatedProcess_hpp
#define simulatedProcess_hpp

#include "util/manstring.hpp"
#include "setup.hpp"

// Forward Declarations
class ProcessManager;

using namespace std;
static int COUNT_ID = -1;

class SimulatedProcess {
    private:
        // Representação dos comandos do processo
    	string *program;

        /**
        * Inicializa um processo simulado
        */
        void init(void);

        /**
         * Define um novo programa pro processo
         * @param masterId PID do pai que criou o processo
         * @param program  Programa do processo
         * @param pc       Valor do Program Counter
         * @param value    Valor do inteiro manipulado
         */
    	void setProgram(int masterId, string *program, int pc, int value);

        /**
         * Seta o valor da variável n para o value passado (S)
         * @param value Novo valor
         */
        void set(int value);

        /**
         * Incrementa o valor da variável n pelo value passado (A)
         * @param value Valor a se incrementar
         */
        void add(int value);

        /**
         * Decrementa o valor da variável n pelo value passado (D)
         * @param value Valor a se decrementar
         */
    	void sub(int value);

        /**
         * Bloqueia este processo simulado (B)
         */
    	void block(void);

        /**
         * Encerra esse processo simulado
         */
    	void end(void);

        /**
         * Cria um novo processo simulado a partir do processo pai (F)
         * @returns Processo simulado criado
         */
    	SimulatedProcess *fork(int n);

        /**
         * Substitui o programa do processo simulado pelo arquivo passado (R)
         * @param file Arquivo que será lido
         */
    	void read(string file);

    public:
        // PID do processo
    	int id;

        // Valor do PC
    	int pc;

        // Valor da variável manipulada
    	int n;

        // PPID: o PID do Pai do processo
    	int masterId;

        // Tempo de execução total na CPU do processo.
    	int cpuTime;

        // Constructors
    	SimulatedProcess(void);
    	SimulatedProcess(string rawProgram);

        /**
         * Incrementa PC e lê um comando do processo simulado
         */
    	void readComand(void);

        /**
         * Retorna o tamanho do programa
         * @return  Inteiro representando o tamanho da string do programa.
         */
        int getProgramSize(void);
};

#endif /* simulatedProcess_hpp */
