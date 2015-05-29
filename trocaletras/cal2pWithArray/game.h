#include <string>
#include "dictionary.h"

class Game{

	public:
	std::string characterSet;
	int p1Points;
	int p2Points;

	Dictionary* dic;

	void generateSet(int minWordsSelected);

	//actions allowed in the game
	void switchLetters(int a, int b);
	void makeWord(int a, int b);

	void AI();

	void run();

	void display();
};
