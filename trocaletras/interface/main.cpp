
#include <iostream>

#include "game.h"

using namespace std;

int main()
{

	Dictionary *dic = new Dictionary;
	dic->freeWordsWhenBuildingDFA = true;
	//    dic->readDICfile("US.dic");
	//    dic->buildDFA();
	//    dic->buildDFA_fromWords();
	//    dic->saveDFA_toBinaryFile("US.dicnodes");//portugues_dictionary_nodes.data");
	dic->buildDFA_fromBinaryFile("US.dicnodes");

	bool play=true;
	while(play) {
		system("cls");
		srand ((unsigned int) time(NULL));
		int chainSize = 50;
		Game *game;
		string answer{};
		cout << endl << "Letter Swap!" << endl << endl;
		cout << "Play against: (h-human/other-computer)? ";
		getline(cin, answer);
		if (answer == "h"||answer == "H") {
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

		game->freeHeap();
		delete game;

		string playagaina_answ {};
		do{
		cout << endl;
		cout << "Play again? (y-yes/n-no)" <<endl;
		getline(cin, playagaina_answ);
		}while (playagaina_answ!="y"&&playagaina_answ!="n"&&playagaina_answ!="N"&&playagaina_answ!="Y");
		if (playagaina_answ=="n"||answer == "N") play=false;
	}//end while(play)

	dic->freeHeap();
	delete dic;

    return 0;
}
