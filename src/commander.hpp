/**
 * Definição da classe Commander: Ponto inicial do programa. Cria um novo processo pra o PM e cria um pipe. A partir da leitura dos comandos
 * do usuário, encaminha para o processo do PM, através do pipe, os comandos lidos.
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
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
		// Tipo de entrada dos dados (STDIO ou EXTERNAL_FILE)
		InputSource inputSource;

		// File Description - estrutura para o Pipe
		int fd[2];

		// pid do processo criado para o Process Manager
		pid_t pid;

		/**
		 * Método executado apenas para o processo filho do Commander, criado no construtor.
		 * Lê do pipe e chama o process manager os comandos lidos.
		 */
		void readCommands(void);

		/**
		 * Método executado apenas pelo processo pai do Commander, após o fork no construtor.
		 * Lê os comandos do usuário e os envia pelo pipe para o processo filho.
		 */
		void sendCommands(void);
	public:

		/**
		 * Construtor da classe Commander - Cria um processo pro PM, um pipe e faz o fluxo de envio de comandos entre os processos.
		 * @param is Tipo de entrada dos dados escolhida pelo usuário.
		 */
		Commander (InputSource is);
};

#endif /* commander_hpp */
