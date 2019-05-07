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
		// No filho, vamos apenas ler, então vamos escrever a *escrita* do pipe
		close(fd[1]);

		// TODO: Arrumar esse codigo pra se tornar o PM
		// // Lendo o que foi escrito no pipe
		char codeReceived;
		int queueSize;

		// Lendo o tamanho da fila
		read(fd[0], &queueSize, sizeof(int));

		for (int i = 0; i < queueSize; i++) {
			read(fd[0], &codeReceived, sizeof(char));
			cout << endl << yellow << "[DEBUG PM] Lendo código: " << codeReceived << endl;
		}
	} else {
		// Se não, estamos no pai e o PID do filho está salvo na variável pid.
		// No pai a gente vai escrever, então vamos fechar a *leitura* do pipe.
		close(fd[0]);
		queue<char> codesQueue;
		char currentCode;
		int queueSize;

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
}


void Commander::menu(void) {
}

string Commander::leArquivo(void) {
	return "not_implemented";
}

string Commander::leEntrada(void) {
	return "not_implemented";
}

void Commander::sendDataPipe(string data) {
	// write(fd[1], data, sizeof(data) + 1)
}
