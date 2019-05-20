/**
 * Interface de interação com o usuário do Módulo Commander
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef commanderInterface_hpp
#define commanderInterface_hpp

#include "../util/logger.hpp"
#include "inputSource.hpp"
#include <fstream>
#include <queue>

using namespace std;
class CommanderInterface {
	private:
		// Construtor privado pra evitar instâncias
		CommanderInterface (void);

        /**
         * Verifica se um código é válido
         * @param  code Código a ser validado
         * @return      Valor booleano indicando validade do código
         */
		static bool isCodeValid(char code);

	public:
        /**
         * Mostra uma mensagem de boas vindas, com os autores do trabalho
         */
		static void welcome(void);

        /**
         * Solicita o usuário o tipo de entrada de dados que ele vai fornecer os comandos
         * @return  Fonte de dados
         */
        static InputSource chooseSource(void);

        /**
         * Mostra um cabeçalho com os comandos disponíveis a serem executados
         */
		static void commandsInstructions(void);

        /**
         * Lê os comandos que o usuário inserir na saída padrão
         * @return  Fila de comandos digitadas pelo usuário
         */
		static queue<char> readCommandFromStdIO(void);

        /**
         * Lê os comandos que o usuário inseriu em um arquivo externo
         * @return  Fila de comandos lidas no arquivo
         */
        static queue<char> readCommandFromFile(void);
};

#endif /* commanderInterface_hpp */
