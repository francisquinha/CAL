#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    // std::random_shuffle
#include <vector>

#include "game.h"

void Game::generateSet(int minWordsSelected)
{
	//add letters from words
	while(minWordsSelected>0)
	{
	int randWordIndex = rand()%(dic->words.size()
			//select shorter words if there are going to be more words to be chosen
			/minWordsSelected);
	characterSet+= dic->words[randWordIndex];
	}

	//shuffle
	std::random_shuffle(characterSet.begin(),characterSet.end());
}
