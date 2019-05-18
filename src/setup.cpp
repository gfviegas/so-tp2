/**
 * Definição das configurações do sistema
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "setup.hpp"

Preemptiveness Setup::preemptiveness;
Politics Setup::politic;
Setup::Mode Setup::mode;

Setup::Setup (void) {
    // Por default, o sistema será preemptivo
    Setup::preemptiveness = Preemptiveness::PREEMPTIVE;

    // Por default, o sistema terá a política de prioridade definida
    Setup::politic = Politics::PRIORITY_DEFAULT;

    // Por default, o sistema não estará no modo debug
    Setup::mode = Setup::Mode::NORMAL;
}

void Setup::printHelp(void) {
    cout << cyan << "Argumentos disponíveis: " << endl;
    cout << green << "--debug | -d " << blue << "Imprime essa mensagem auxiliar" << endl;
    cout << green << "[DEFAULT] --preemptive | -p " << blue << "Utiliza o modo preemptivo do escalonamento" << endl;
    cout << green << "--non-preemptive | -n " << blue << "Utiliza o modo não-preemptivo do escalonamento" << endl;
    cout << green << "[DEFUALT] --priority-defaut " << blue << "Utiliza a política de escalonamento padrão" << endl;
    cout << green << "--shortest " << blue << "Utiliza a política de escalonamento que prioriza os processos com jobs mais curtos" << endl;
    cout << green << "--least-used " << blue << "Utiliza a política de escalonamento que prioriza os processos com jobs menos executados" << endl;
}

void Setup::parseArguments(int argc, const char *argv[]) {
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg.compare("--help") == 0 || arg.compare("-h") == 0) {
            printHelp();
            exit(0);
            return;
        } else if (arg.compare("--debug") == 0 || arg.compare("-d") == 0) {
            Setup::mode = Setup::Mode::DEBUG;
        } else if (arg.compare("--preemptive") == 0 || arg.compare("-p") == 0) {
            Setup::preemptiveness = Preemptiveness::PREEMPTIVE;
        } else  if (arg.compare("--non-preemptive") == 0 || arg.compare("-n") == 0) {
            Setup::preemptiveness = Preemptiveness::NON_PREEMPTIVE;
        } else if (arg.compare("--priority-default") == 0) {
            Setup::politic = Politics::PRIORITY_DEFAULT;
        } else if (arg.compare("--shortest") == 0) {
            Setup::politic = Politics::SHORTEST;
        } else if (arg.compare("--least-used") == 0) {
            Setup::politic = Politics::LEAST_USED;
        } else {
            cout << "Argumento inválido: " << arg << endl;
            printHelp();
            exit(0);
            return;
        }
    }
}

bool Setup::isDebug(void) {
    return (mode == DEBUG);
}
