/**
 * Definição da classe Commander: [DESCRICAO]
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author
 */

#ifndef commander_h
#define commander_h

using namespace std;
#include <string.h>

class Commander {
	private:
	public:
		// [pipe description]
		Pipe pipe;
		// [processManager description]
		ProcessManager processManager;

		/**
		 * [Commander  description]
		 * @param arguments [description]
		 */
		Commander (arguments);
		virtual ~Commander ();

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
};

#endif /* commander_h */
