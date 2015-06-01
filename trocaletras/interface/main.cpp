
#include <iostream>

#include "game.h"

#include <stdio.h>
#include <time.h>

using namespace std;

void printLogo(int state)
{
	switch(state)
	{
	case 1:
		cout << "      _____  "<<endl;
		cout << "|\\   |  __ \\ "<<endl;
		cout << "| \\  | |__) |"<<endl;
		cout << "|\\ \\ |  ___/ "<<endl;
		cout << "|__ \\| |     "<<endl;
		cout << "|  \\_\\_|     "<<endl;
		break;
	case 2:
		cout << "_______          __     _____  "<<endl;
		cout << " ____\\ \\        / /\\   |  __ \\ "<<endl;
		cout << "(___  \\ \\  /\\  / /  \\  | |__) |"<<endl;
		cout << "___ \\  \\ \\/  \\/ / /\\ \\ |  ___/ "<<endl;
		cout << "___) |  \\  /\\  / ____ \\| |     "<<endl;
		cout << "____/    \\/  \\/_/    \\_\\_|     "<<endl;
		break;
	case 3:
		cout << "_____     _______          __     _____  "<<endl;
		cout << "  __ \\   / ____\\ \\        / /\\   |  __ \\ "<<endl;
		cout << " |__) | | (___  \\ \\  /\\  / /  \\  | |__) |"<<endl;
		cout << "  _  /   \\___ \\  \\ \\/  \\/ / /\\ \\ |  ___/ "<<endl;
		cout << " | \\ \\   ____) |  \\  /\\  / ____ \\| |     "<<endl;
		cout << "_|  \\_\\ |_____/    \\/  \\/_/    \\_\\_|     "<<endl;
		break;
	case 4:
		cout << "____ ______ _____     _______          __     _____  "<<endl;
		cout << "  __|  ____|  __ \\   / ____\\ \\        / /\\   |  __ \\ "<<endl;
		cout << " |  | |__  | |__) | | (___  \\ \\  /\\  / /  \\  | |__) |"<<endl;
		cout << " |  |  __| |  _  /   \\___ \\  \\ \\/  \\/ / /\\ \\ |  ___/ "<<endl;
		cout << " |  | |____| | \\ \\   ____) |  \\  /\\  / ____ \\| |     "<<endl;
		cout << "_|  |______|_|  \\_\\ |_____/    \\/  \\/_/    \\_\\_|     "<<endl;
		break;
	case 5:
		cout << "____ _______ _______ ______ _____     _______          __     _____  "<<endl;
		cout << "____|__   __|__   __|  ____|  __ \\   / ____\\ \\        / /\\   |  __ \\ "<<endl;
		cout << "__     | |     | |  | |__  | |__) | | (___  \\ \\  /\\  / /  \\  | |__) |"<<endl;
		cout << "__|    | |     | |  |  __| |  _  /   \\___ \\  \\ \\/  \\/ / /\\ \\ |  ___/ "<<endl;
		cout << "____   | |     | |  | |____| | \\ \\   ____) |  \\  /\\  / ____ \\| |     "<<endl;
		cout << "____|  |_|     |_|  |______|_|  \\_\\ |_____/    \\/  \\/_/    \\_\\_|     "<<endl;
		break;
	default:
	cout << " _      ______ _______ _______ ______ _____     _______          __     _____  "<<endl;
	cout << "| |    |  ____|__   __|__   __|  ____|  __ \\   / ____\\ \\        / /\\   |  __ \\ "<<endl;
	cout << "| |    | |__     | |     | |  | |__  | |__) | | (___  \\ \\  /\\  / /  \\  | |__) |"<<endl;
	cout << "| |    |  __|    | |     | |  |  __| |  _  /   \\___ \\  \\ \\/  \\/ / /\\ \\ |  ___/ "<<endl;
	cout << "| |____| |____   | |     | |  | |____| | \\ \\   ____) |  \\  /\\  / ____ \\| |     "<<endl;
	cout << "|______|______|  |_|     |_|  |______|_|  \\_\\ |_____/    \\/  \\/_/    \\_\\_|     "<<endl;
	break;
	}
}

int main()
{

#if defined(__APPLE__) || defined(__unix__)
	printf("\033c");
#else
	system("cls");
#endif
	cout<<"LOADING DICTIONARY ... ... ..."<<endl;

//LOAD STUFF ========================

	Dictionary *dic = new Dictionary;
	dic->freeWordsWhenBuildingDFA = true;
	//    dic->readDICfile("US.dic");
	//    dic->buildDFA();
	//    dic->buildDFA_fromWords();
	//    dic->saveDFA_toBinaryFile("US.dicnodes");//portugues_dictionary_nodes.data");
	dic->buildDFA_fromBinaryFile("US.dicnodes");

	system("cls");
for (int i = 0; i<7;++i){
#if defined(__APPLE__) || defined(__unix__)
	//???system("sleep 0.5f");
	printf("\033c");
#else
	system("sleep 1");
	system("cls");
#endif
	if (i>0) printLogo(i);
}
system("sleep 1");

	//RUN THE GAME =================

	bool play=true;
	while(play) {
#if defined(__APPLE__) || defined(__unix__)
	printf("\033c");
#else
	system("cls");
#endif
	//printLogo(0);
	    //print rules
		cout << endl << endl;
		 cout << "__________ Objective __________________________________________________________"<<endl;
		 cout<<"1 - Select words present in the sequence to win points"<<endl;
		 cout<<"2 - The number of points given by selecting a word is equal to it's length"<<endl;
		 cout<<"3 - The player with more points at the end of the game wins"<<endl;
		 cout << "__________ Rules ______________________________________________________________"<<endl;
		 cout<<"1 - A player can select a word in the sequence"<<endl;
		 cout<<"2 - Selecting words composed of one letter is not permitted ('I' and 'a')"<<endl;
		 cout<<"3 - A player can swap 2 letters, and 2 only, of the character sequence"<<endl;
		 cout<<"4 - A player may select a word in the sequence after swapping letters"<<endl;
		 cout<<"5 - A player can select words from left to right inputing the lesser index of"<<endl << "the word 1st or"
				 " select words form right to left inputing the greater index 1st"<<endl;
		 cout<<"6 - After selecting a word, it's characters will be removed from the sequence"<<endl;
		 cout<<"7 - A player may skip the turn by not swapping a letter and not selecting a"<<endl<< "valid word"<<endl;
		 cout<<"8 - Swapping equal letters is not considered a valid swap"<<endl;
	    cout << "__________ THE GAME WILL END WHEN ______________________________________________"<<endl;
	    cout<< "1 - Both players skip their turn by not swapping or trying to guess a word"<<endl;
	    cout<< "2 - When the character sequence has less than 11 characters and it's not"<<endl<<"possible to form any word"<<endl;
	    cout <<"________________________________________________________________________________"<<endl;

		srand ((unsigned int) time(NULL));
		int chainSize = 50;
		Game *game;
		string answer{};
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
			cout << "Difficulty (4 - hardest, 3 - hard, 2 - medium, any other - easy)? ";
			getline(cin, answer);
			if (answer == "4") game = new Game(1, name1, "", 4, chainSize, dic);
			else if (answer == "3") game = new Game(1, name1, "", 3, chainSize, dic);
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
