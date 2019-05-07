/**
 * Definição da classe Commander: [DESCRICAO]
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author
 */

#ifndef commander_hpp
#define commander_hpp

#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <queue>

#include "processManager.hpp"
#include "interfaces/commanderInterface.hpp"
#include "interfaces/inputSource.hpp"

using namespace std;
class Commander {
	private:
		InputSource inputSource;

	public:
		// File Description - para o Pipe
		int fd[2];

		pid_t pid;

		// [processManager description]
		ProcessManager processManager;

		/**
		 * [Commander  description]
		 * @param void [description]
		 */
		Commander (InputSource is);

		/**
		 * [menu description]
		 */
		void menu(void);

		/**
		 * [leArquivo description]
		 * @return  [description]
		 */
		string leArquivo(void);

		/**
		 * [leEntrada description]
		 * @return  [description]
		 */
		string leEntrada(void);

		void sendDataPipe(string data);
};

#endif /* commander_hpp */
