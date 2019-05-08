#include "commander.hpp"

// Constructor
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
		return readCommands();
	} else {
		// Se não, estamos no pai e o PID do filho está salvo na variável pid.
		return sendCommands();
	}
}

void Commander::readCommands(void) {
	char codeReceived;
	int queueSize;

	// No filho, vamos apenas ler, então vamos escrever a *escrita* do pipe
	close(fd[1]);

	// Lendo o tamanho da fila
	read(fd[0], &queueSize, sizeof(int));

	// Pra cada elemento na fila, invoca o PM pra orquestrar o comando de fato.
	for (int i = 0; i < queueSize; i++) {
		read(fd[0], &codeReceived, sizeof(char));
		cout << endl << yellow << "[DEBUG PM] Lendo código: " << codeReceived << endl;
		pm.runCommand(codeReceived);
	}
}

void Commander::sendCommands(void) {
	queue<char> codesQueue;
	char currentCode;
	int queueSize;
	ProcessManager processManager;

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
	write(fd[1], &queueSize, sizeof(int));

	// Enviando a fila, caracter por caracter
	while (!codesQueue.empty()) {
		currentCode = codesQueue.front();
		write(fd[1], &currentCode, sizeof(char));
		codesQueue.pop();
	}
}
