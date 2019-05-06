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
		read(fd[0], &codeReceived, 1);
		cout << endl << yellow << "[DEBUG] O PIPE RECEBEU O DADO: " << codeReceived << endl;

	} else {
		// Se não, estamos no pai e o PID do filho está salvo na variável pid.
		// No pai a gente vai escrever, então vamos fechar a *leitura* do pipe.
		close(fd[0]);


		if (inputSource == STDIO) {
			CommanderInterface::commandsInstructions();

			char code = CommanderInterface::readCommandFromStdIO();
			write(fd[1], &code, 1);
		} else if (inputSource == EXTERNAL_FILE) {
			// TODO: Criar interface pra leitura do arquivo
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
