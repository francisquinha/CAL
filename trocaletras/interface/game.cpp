
#include "game.h"

using namespace std;

Game::Game(int nPlayers, std::string p1Name, std::string p2Name, int difficult, int size, Dictionary *dic) {
    numberPlayers = nPlayers;
    difficulty = difficult;
    chainSize = size;
    player1 = new Player(p1Name, true);
    if (numberPlayers == 2) player2 = new Player(p2Name, true);
    else if (difficulty == 1) player2 = new Player("Dumbo", false);
    else if (difficulty == 2) player2 = new Player("Smarto", false);
    else player2 = new Player("Deep Thought", false);
    letters = {};
    for (int i = 0; i < 26 ; i++) letters.push_back((const char &) ('a' + i));
    chain = {};
    dictionary = dic;
    randomWordsChain();
    startingPlayer = rand() % 2 + 1;
}

void Game::randomLettersChain() {
    for (int i = 0; i < chainSize; i++) {
        chain.push_back(letters[rand() % 26]);
    }
}

void Game::randomWordsChain() {
    vector<string> randomWords = dictionary->selectRandomWords(chainSize, 5); // words of size at most 5
    int index = 0;
    while (chain.size() < chainSize) {
        string newWord = randomWords[index];
        for (int i = 0; i < newWord.length(); i++) {
            chain.push_back(newWord[i]);
        }
        index++;
    }
    while (chain.size() > chainSize) {
        chain.pop_back();
    }
    random_shuffle(chain.begin(), chain.end());
}

void Game::play() {
    Player *firstPlayer;
    Player *secondPlayer;
    if (startingPlayer == 1) {
        firstPlayer = player1;
        secondPlayer = player2;
    }
    else {
        firstPlayer = player2;
        secondPlayer = player1;
    }
    do {
    	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
        cout<<firstPlayer->getName()<<" score = "<<firstPlayer->getScore()  <<endl;
        chain = firstPlayer->turn(chain, dictionary, difficulty);
        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    	cout<<secondPlayer->getName()<<" score = "<< secondPlayer->getScore()  <<endl;
        chain = secondPlayer->turn(chain, dictionary, difficulty);
    }
    while (!checkFinish());
    if (player1->getScore() == player2->getScore())
        cout << endl << "The game ends with a tie at " << player1->getScore() << " points." << endl;
    else if (player1->getScore() > player2->getScore())
        cout << endl << player1->getName() << " wins with " << player1->getScore() << " points, versus "
            << player2->getScore() << " points from " << player2->getName() << "." << endl;
    else
        cout << endl << player2->getName() << " wins with " << player2->getScore() << " points, versus "
            << player1->getScore() << " points from " << player1->getName() << "." << endl;
}

bool Game::checkFinish() {
    return player1->getSkip() && player2->getSkip();
}

void Game::freeHeap()
{
delete player1; delete player2;
}
