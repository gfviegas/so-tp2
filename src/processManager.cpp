/**
 * Definição da classe ProcessManager: simula cinco funções de gerenciamento de
 * processos e inicia o processo reporter sempre que precisa imprimir o estado
 * do sistema.
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "processManager.hpp"

#include "util/logger.hpp"

ProcessManager::ProcessManager(void)
{
    ifstream firstProcess;
    firstProcess.open("init");

    string program = "";
    char c;

    while (firstProcess >> c)
    {
        cout << c << endl;
        program += c;
    }

    cout << program << endl;

    firstProcess.close();
}

void ProcessManager::unblock(void)
{
}

void ProcessManager::print(void)
{
}

void ProcessManager::endExecution(void)
{
}

void ProcessManager::execute(void)
{
}
