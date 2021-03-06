/**
 * Definição da classe Commander: Ponto inicial do programa. Cria um novo processo pra o PM e cria um pipe. A partir da leitura dos comandos
 * do usuário, encaminha para o processo do PM, através do pipe, os comandos lidos.
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "commander.hpp"

// Construtor da classe Commander - Cria um processo pro PM, um pipe e faz o fluxo de envio de comandos entre os processos.
Commander::Commander(InputSource is) {
	inputSource = is;

	// Inicializa o pipe com o fd definido
	if (pipe(fd) == -1) {
		perror("pipe");
		exit(1);
	}

	pid = fork();

	if (pid < 0) {
		// Se pid for < 0, deu erro!
		perror("fork");
		exit(1);
	} else if (pid == 0) {
		// Se for 0, estamos no filho!
		readCommands();
	} else {
		// Se não, estamos no pai e o PID do filho está salvo na variável pid.
		sendCommands();
	}
}

// Método executado apenas para o processo filho do Commander, criado no construtor.
void Commander::readCommands(void) {
    queue<char> codesQueue;
	char codeReceived;
	int queueSize;

	// Inicia o PM.
	ProcessManager::init();

	// No filho, vamos apenas ler, então vamos escrever a *escrita* do pipe
	close(fd[1]);

	// Lendo o tamanho da fila
	read(fd[0], &queueSize, sizeof(int));

	// Pra cada elemento na fila, invoca o PM pra orquestrar o comando de fato.
    if (Setup::isDebug()) cout << endl << magenta << "[DEBUG CM] Tamanho fila: " << queueSize << endl;

    // Preenchendo a fila antes pra liberar o pipe.
    for (int i = 0; i < queueSize; i++) {
        read(fd[0], &codeReceived, sizeof(char));
        codesQueue.push(codeReceived);
    }

    try {
        while (!codesQueue.empty()) {
            codeReceived = codesQueue.front();
            if (Setup::isDebug()) cout << endl << magenta << "[" << (queueSize - codesQueue.size()) << "] - [DEBUG CM] Lendo código: " << codeReceived << endl;
            ProcessManager::runCommand(codeReceived);
            codesQueue.pop();
        }
    } catch (exception &e) {
		printError(e);
		exit(1);
	}

    exit(0);
}

// Método executado apenas pelo processo pai do Commander, após o fork no construtor.
void Commander::sendCommands(void) {
	queue<char> codesQueue;
	char currentCode;
	int queueSize;

	// No pai a gente vai escrever, então vamos fechar a *leitura* do pipe.
	close(fd[0]);

	if (inputSource == STDIO) {
		CommanderInterface::commandsInstructions();
		codesQueue = CommanderInterface::readCommandFromStdIO();
	} else if (inputSource == EXTERNAL_FILE) {
		// Pega a fila de codigos do arquivo e escreve a fila no pipe.
		codesQueue = CommanderInterface::readCommandFromFile();
	}

	// Enviando pelo pipe o tamanho da fila
	queueSize = codesQueue.size();
    if (Setup::isDebug()) cout << endl << magenta << "[DEBUG CM] Tamanho fila: " << queueSize << endl;
	write(fd[1], &queueSize, sizeof(int));

	// Enviando a fila, caracter por caracter
    try {
        while (!codesQueue.empty()) {
            currentCode = codesQueue.front();
            write(fd[1], &currentCode, sizeof(char));
            codesQueue.pop();
        }
    } catch (exception &e) {
		printError(e);
		exit(1);
	}

    wait(NULL);
}
