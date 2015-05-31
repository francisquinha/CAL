
#include <iostream>

#include "game.h"

using namespace std;

int main()
{
    srand ((unsigned int) time(NULL));
    int chainSize = 50;
    Dictionary *dic = new Dictionary;
    dic->freeWordsWhenBuildingDFA = true;
//    dic->readDICfile("US.dic");
//    dic->buildDFA();
//    dic->buildDFA_fromWords();
//    dic->saveDFA_toBinaryFile("US.dicnodes");//portugues_dictionary_nodes.data");
    dic->buildDFA_fromBinaryFile("US.dicnodes");
    Game *game;
    string answer{};
    cout << endl << "Letter Swap!" << endl << endl;
    cout << "Number of players (1/2)? ";
    getline(cin, answer);
    if (answer == "2") {
        cout << "Player 1: Name? ";
        string name1 {};
        getline(cin, name1);
        if (name1 == "") name1 = "Player 1";
        cout << "Player 2: Name? ";
        string name2 {};
        getline(cin, name2);
        if (name2 == "") name2 = "Player 2";
        game = new Game(2, name1, name2, 0, chainSize, dic);
    }
    else {
        cout << "Player 1: Name? ";
        string name1 {};
        getline(cin, name1);
        if (name1 == "") name1 = "Player 1";
        cout << "Difficulty (1 - easy, 2 - medium, 3 - hard)? ";
        getline(cin, answer);
        if (answer == "3") game = new Game(1, name1, "", 3, chainSize, dic);
        else if (answer == "2") game = new Game(1, name1, "", 2, chainSize, dic);
        else game = new Game(1, name1, "", 1, chainSize, dic);
    }
    cout << endl;
    game->play();
    return 0;
}
