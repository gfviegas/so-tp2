/**
 * Definição das configurações do sistema
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef setup_hpp
#define setup_hpp

#include <string>
#include "util/logger.hpp"
#include "politics.hpp"

using namespace std;
class Setup {
    private:
        Setup (void);

        static void printHelp(void);
    public:
        enum Mode { NORMAL, DEBUG };
        static Preemptiveness preemptiveness;
        static Politics politic;
        static Mode mode;

        static void parseArguments(int argc, const char *argv[]);
};

#endif /* setup_hpp */
