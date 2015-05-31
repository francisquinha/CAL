
#ifndef TROCALETRAS_GAME_H
#define TROCALETRAS_GAME_H

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    // std::random_shuffle
#include <vector>
#include <string>
#include "player.h"

class Game{

    int numberPlayers;
    Player *player1;
    Player *player2;
    int difficulty;
    int chainSize;
    std::vector<char> letters;
    std::vector<char> chain;
    Dictionary* dictionary;
    int startingPlayer;

public:

    Game(int nPlayers, std::string p1Name, std::string p2Name, int difficult, int size, Dictionary *dic);

    void randomLettersChain();

    void randomWordsChain();

    void play();

    bool checkFinish();

    void freeHeap();
};

#endif //TROCALETRAS_GAME_H
