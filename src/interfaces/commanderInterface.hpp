#ifndef commanderInterface_hpp
#define commanderInterface_hpp

#include "../util/logger.hpp"
#include "inputSource.hpp"

using namespace std;
class CommanderInterface {
	private:
		// Construtor privado pra evitar instâncias
		CommanderInterface (void);
		static bool isCodeValid(char code);

	public:
		static void welcome(void);
		static void commandsInstructions(void);
		static InputSource chooseSource(void);
		static char readCommandFromStdIO(void);
};

#endif /* commanderInterface_hpp */
