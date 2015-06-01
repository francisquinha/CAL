//
// Created by Angie on 30/05/15.
//

#include <iomanip>
#include "player.h"
#include "game.h"

using namespace std;

Player::Player(string newName, bool newType) {
    name = newName;
    type = newType;
    words = {};
    score = 0;
    skip = false;
}

vector<char> Player::turn(vector<char> chain, Dictionary * dictionary, int difficulty, Player* p) {
    if (type) chain = humanTurn(chain, dictionary);
    else
    	switch(difficulty){
    	case 1: chain = diff1Turn(chain, dictionary);
    				break;
    	case 2: chain = diff2Turn(chain, dictionary);
    	    		break;
    	case 3: chain = diff3Turn(chain, dictionary);
    	    		break;
    	case 4: chain = diff4Turn(chain, dictionary,p);
    	    		break;
    	default: cout<<"ERROR!"<<endl; break;
    	}


    return chain;
}

vector<char> &Player::humanTurn(vector<char> &chain, Dictionary *dictionary) {
    skip = true;
    string answer {};
    int index1 {};
    int index2 {};
    cout << endl << name << ": it's your turn." << endl << endl;
    Game::printChain(chain);
    cout << "Switch letters (y: yes / other: no)? ";
    getline(cin, answer);
    if (answer == "y"||answer == "Y") {
        getIndex(chain.size(), index1, "First");
        getIndex(chain.size(), index2, "Second");
        swapLetters(chain, index1, index2);
        cout << endl;
        Game::printChain(chain);
        if (chain[index1]!=chain[index2]) skip = false;
    }
    cout << "Choose word (y: yes / other: no)? ";
    getline(cin, answer);
    if (answer == "y"||answer == "Y") {
        getIndex(chain.size(), index1, "First");
        getIndex(chain.size(), index2, "Last");
        string word {};
        if (removeLetters(chain, index1, index2, word, dictionary))
        {
            cout << endl << "'" << word << "': Good! Score = " << score << "." << endl;
            skip = false;
        }
        else cout << endl << "Sorry, '" << word <<"' is not a word!" << endl;
    }
    return chain;
}

vector<char> &Player::diff1Turn(vector<char> &chain, Dictionary *dictionary) {
    skip = true;
    vector<int> indexes1 {};
    vector<int> indexes2 {};
    dictionary->allWords(string(chain.begin(), chain.end()), indexes1, indexes2);
    if (indexes1.size() > 0) {
        skip = false;
        long wordIndex = rand() % indexes1.size();
        int index1 = indexes1[wordIndex];
        int index2 = indexes2[wordIndex];
        string word{};
        removeLetters(chain, index1, index2, word, dictionary);
        cout << endl;
        Game::printChain(chain);
        cout << name << ": '" << word << "'. Score = " << score << "." << endl;
    }
    else {
        vector<int> swapIndexes1 {};
        vector<int> swapIndexes2 {};
        dictionary->findSwapOnePossibilities(string(chain.begin(), chain.end()), indexes1, indexes2, swapIndexes1, swapIndexes2);
        if (swapIndexes1.size() > 0) {
            skip = false;
            long wordIndex = rand() % swapIndexes1.size();
            int swapIndex1 = swapIndexes1[wordIndex];
            int swapIndex2 = swapIndexes2[wordIndex];
            int index1 = indexes1[wordIndex];
            int index2 = indexes2[wordIndex];
            cout << endl;
            Game::printChain(chain);
            cout << name << ": Swap "<< swapIndex2 << " " << swapIndex1 <<"." << endl << endl;
            swapLetters(chain, swapIndex1, swapIndex2);
            Game::printChain(chain);
            string word{};
            removeLetters(chain, index1, index2, word, dictionary);
            cout << name << ": '" << word << "'. Score = " << score << "." << endl;
        }
    }
    if(skip) cout << endl <<name << " skipped..."<<endl ;
    return chain;
}

vector<char> &Player::diff2Turn(vector<char> &chain, Dictionary *dictionary) {
    skip = true;
    vector<int> indexes1 {};
    vector<int> indexes2 {};
    dictionary->allWords(string(chain.begin(), chain.end()), indexes1, indexes2);
    if (indexes1.size() > 0) {
        skip = false;
        long wordIndex = getBest(indexes1, indexes2);
        int index1 = indexes1[wordIndex];
        int index2 = indexes2[wordIndex];
        string word{};
        removeLetters(chain, index1, index2, word, dictionary);
        cout << endl;
        Game::printChain(chain);
        cout << name << ": '" << word << "'. Score = " << score << "." << endl;
    }
    else {
        vector<int> swapIndexes1 {};
        vector<int> swapIndexes2 {};
        dictionary->findSwapOnePossibilities(string(chain.begin(), chain.end()), indexes1, indexes2, swapIndexes1, swapIndexes2);
        if (swapIndexes1.size() > 0) {
            skip = false;
            long wordIndex = rand() % swapIndexes1.size();
            int swapIndex1 = swapIndexes1[wordIndex];
            int swapIndex2 = swapIndexes2[wordIndex];
            int index1 = indexes1[wordIndex];
            int index2 = indexes2[wordIndex];
            cout << endl;
            Game::printChain(chain);
            swapLetters(chain, swapIndex1, swapIndex2);
            cout << name << ": Swap "<< swapIndex2 << " " << swapIndex1 <<"." << endl << endl;
            Game::printChain(chain);
            string word{};
            removeLetters(chain, index1, index2, word, dictionary);
            cout << name << ": '" << word << "'. Score = " << score << "." << endl;
        }
    }
    if(skip) cout << endl <<name << " skipped..."<<endl ;
    return chain;
}

vector<char> &Player::diff3Turn(vector<char> &chain, Dictionary *dictionary) {
    skip = true;
    vector<int> indexes1 {};
    vector<int> indexes2 {};
    vector<int> swapIndexes1 {};
    vector<int> swapIndexes2 {};
    dictionary->findSwapOnePossibilities(string(chain.begin(), chain.end()), indexes1, indexes2, swapIndexes1, swapIndexes2);
    if (swapIndexes1.size() > 0) {
        skip = false;
        long wordIndex = getBest(indexes1, indexes2);
        int swapIndex1 = swapIndexes1[wordIndex];
        int swapIndex2 = swapIndexes2[wordIndex];
        int index1 = indexes1[wordIndex];
        int index2 = indexes2[wordIndex];
        cout << endl;
        Game::printChain(chain);
        swapLetters(chain, swapIndex1, swapIndex2);
        cout << name << ": Swap "<< swapIndex2 << " " << swapIndex1 <<"." << endl << endl;
        Game::printChain(chain);
        string word{};
        removeLetters(chain, index1, index2, word, dictionary);
        cout << name << ": '" << word << "'. Score = " << score << "." << endl;
    }
    else {
        dictionary->allWords(string(chain.begin(), chain.end()), indexes1, indexes2);
        if (indexes1.size() > 0) {
            skip = false;
            long wordIndex = getBest(indexes1, indexes2);
            int index1 = indexes1[wordIndex];
            int index2 = indexes2[wordIndex];
            string word{};
            cout << endl;
            Game::printChain(chain);
            removeLetters(chain, index1, index2, word, dictionary);
            cout << name << ": '" << word << "'. Score = " << score << "." << endl;
        }
        else {
            reverse(chain.begin(), chain.end());
            dictionary->findSwapOnePossibilities(string(chain.begin(), chain.end()), indexes1, indexes2, swapIndexes1, swapIndexes2);
            if (swapIndexes1.size() > 0) {
                skip = false;
                long wordIndex = getBest(indexes1, indexes2);
                int swapIndex1 = swapIndexes1[wordIndex];
                int swapIndex2 = swapIndexes2[wordIndex];
                int index1 = indexes1[wordIndex];
                int index2 = indexes2[wordIndex];
                cout << endl;
                Game::printReverseChain(chain);
                swapLetters(chain, swapIndex1, swapIndex2);
                cout << name << ": Swap "<< chain.size() - swapIndex1 - 1 << " " << chain.size() - swapIndex2 - 1 <<"." << endl << endl;
                Game::printReverseChain(chain);
                string word{};
                removeLetters(chain, index1, index2, word, dictionary);
                cout << name << ": '" << word << "'. Score = " << score << "." << endl;
            }
            else {
                dictionary->allWords(string(chain.begin(), chain.end()), indexes1, indexes2);
                if (indexes1.size() > 0) {
                    skip = false;
                    long wordIndex = getBest(indexes1, indexes2);
                    int index1 = indexes1[wordIndex];
                    int index2 = indexes2[wordIndex];
                    string word{};
                    cout << endl;
                    Game::printReverseChain(chain);
                    removeLetters(chain, index1, index2, word, dictionary);
                    cout << name << ": '" << word << "'. Score = " << score << "." << endl;
                }
            }
            reverse(chain.begin(), chain.end());
        }
    }
    if(skip) cout << endl <<name << " skipped..."<<endl ;
    return chain;
}

vector<char> &Player::diff4Turn(vector<char> &chain, Dictionary *dictionary, Player* p) {

	skip = true;

	//win without mercy if already has more points
	if(p->getScore() < score && p->getSkip()) return chain;


//1
    vector<int> indexesNoSwap1 {};
    vector<int> indexesNoSwap2 {};
//2
    vector<int> indexes1 {};
    vector<int> indexes2 {};
    vector<int> swapIndexes1 {};
    vector<int> swapIndexes2 {};
//3
    vector<int> indexesNoSwapReverse1 {};
    vector<int> indexesNoSwapReverse2 {};
//4
    vector<int> indexesReverse1 {};
    vector<int> indexesReverse2 {};
    vector<int> swapIndexesReverse1 {};
    vector<int> swapIndexesReverse2 {};

    //- - - - -  - - - - - - - - -
    char whichOne=0;//0-for none ,1,2,3,4?
    long globalBestWordIndex=0;
    long wordIndex=0;

    //forwards
    dictionary->allWords(string(chain.begin(), chain.end()),indexesNoSwap1,indexesNoSwap2);
    if (indexesNoSwap1.size() > 0) {
    	whichOne=1;
    	globalBestWordIndex = getBest(indexesNoSwap1, indexesNoSwap2);
    }

    dictionary->findSwapOnePossibilities(string(chain.begin(), chain.end()), indexes1, indexes2, swapIndexes1, swapIndexes2);
    if (indexes1.size() > 0) {
    	wordIndex = getBest(indexes1, indexes2);
    	if(wordIndex>globalBestWordIndex){
    		whichOne=2;
    		globalBestWordIndex=wordIndex;
    	}
    }

    //reverses
    reverse(chain.begin(), chain.end());
    dictionary->allWords(string(chain.begin(), chain.end()),indexesNoSwapReverse1,indexesNoSwapReverse2);
    if (indexesNoSwapReverse1.size() > 0) {
    	wordIndex = getBest(indexesNoSwapReverse1, indexesNoSwapReverse2);
    	if(wordIndex>globalBestWordIndex){
    		whichOne=3;
    		globalBestWordIndex=wordIndex;
    	}
    }

    dictionary->findSwapOnePossibilities(string(chain.begin(), chain.end()), indexesReverse1, indexesReverse2, swapIndexesReverse1, swapIndexesReverse2);
    if (indexesReverse1.size() > 0) {
    	wordIndex = getBest(indexesReverse1, indexesReverse2);
    	if(wordIndex>globalBestWordIndex){
    		whichOne=4;
    		globalBestWordIndex=wordIndex;
    	}
    }

    //choose best
    if (whichOne!=0) skip = false;
    int lastStandSwap_index;
    string word{};
    switch(whichOne){
    case 1:
    	reverse(chain.begin(), chain.end());
    	cout<<endl;
    	Game::printChain(chain);
    	removeLetters(chain, indexesNoSwap1[globalBestWordIndex], indexesNoSwap2[globalBestWordIndex], word, dictionary);
    	cout << name << ": '" << word << "'. Score = " << score << "." << endl;
    	break;
    case 2:
    	reverse(chain.begin(), chain.end());
    	cout<<endl;
    	Game::printChain(chain);
    	swapLetters(chain, swapIndexes1[globalBestWordIndex], swapIndexes2[globalBestWordIndex]);
    	cout << name << ": Swap "<< swapIndexes2[globalBestWordIndex] << " " << swapIndexes1[globalBestWordIndex] <<"." << endl << endl;
    	cout<<endl;
    	Game::printChain(chain);
    	removeLetters(chain, indexes1[globalBestWordIndex], indexes2[globalBestWordIndex], word, dictionary);
    	cout << name << ": '" << word << "'. Score = " << score << "." << endl;
        	break;
    case 3:
    	cout<<endl;
    	Game::printReverseChain(chain);
    	removeLetters(chain, indexesNoSwapReverse1[globalBestWordIndex], indexesNoSwapReverse2[globalBestWordIndex], word, dictionary);
    	cout << name << ": '" << word << "'. Score = " << score << "." << endl;
    	reverse(chain.begin(), chain.end());
        	break;
    case 4:
    	cout<<endl;
    	Game::printReverseChain(chain);
    	swapLetters(chain, swapIndexesReverse1[globalBestWordIndex], swapIndexesReverse2[globalBestWordIndex]);
    	cout << name << ": Swap "<< chain.size() - swapIndexesReverse1[globalBestWordIndex] - 1 << " " << chain.size() - swapIndexesReverse2[globalBestWordIndex] - 1 <<"." << endl << endl;
    	cout<<endl;
    	Game::printReverseChain(chain);
    	removeLetters(chain, indexesReverse1[globalBestWordIndex], indexesReverse2[globalBestWordIndex], word, dictionary);
    	cout << name << ": '" << word << "'. Score = " << score << "." << endl;
    	reverse(chain.begin(), chain.end());
        	break;
    default:
    	reverse(chain.begin(), chain.end());
    if(p->getScore() > score && p->getSkip()) {
    	Game::printChain(chain);
    	lastStandSwap_index=rand()%(chain.size()-1)+1 ;
    	if (chain[0]!=chain[lastStandSwap_index]) swapLetters(chain,0 ,lastStandSwap_index );
    	cout << name << ": Swap "<< swapIndexes2[globalBestWordIndex] << " " << swapIndexes1[globalBestWordIndex] <<"." << endl << endl;
    	cout<<endl;
    	Game::printChain(chain);
    	skip=false;
    }
        	break;
    }

    if(skip) cout << endl <<name << " skipped..."<<endl ;
    return chain;
}


long Player::getBest(const vector<int> &indexes1, const vector<int> &indexes2) const {
    long wordIndex = 0;
    int wordSize = indexes2[0] - indexes1[0];
    for (int i = 1; i < indexes1.size(); i++) {
        if (indexes2[i] - indexes1[i] > wordSize) {
            wordIndex = i;
            wordSize = indexes2[i] - indexes1[i];
        }
    }
    return wordIndex;
}

void Player::getIndex(unsigned long chainSize, int &index, string which) {
    string answer {};
    bool ok {};
    do {
        cout << which << " letter (0 - " << chainSize - 1 << "): ";
        getline(cin, answer);
        if (isNumber(answer)) {
            index = atoi(answer.c_str());
            ok = !(index < 0 || index >= chainSize);
        }
        else ok = false;
    } while (!ok);
}

bool Player::isNumber(const string number) const {
    for (string::size_type i = 0; i != number.size(); i++) {
        if (!isdigit(number[i]))
            return false; /* existe pelo menos um caracter que nao e um numero */
    }
    return true; /* a string num e constituida exclusivamente por numeros */
}

void Player::swapLetters(vector<char> &chain, int index1, int index2) {
    char letter = chain[index1];
    chain[index1] = chain[index2];
    chain[index2] = letter;
}

bool Player::removeLetters(vector<char> &chain, int index1, int index2, string &word, Dictionary *dictionary) {
    if (index1 <= index2) {
        for (int i = index1; i <= index2; i++) {
            word += chain[i];
        }
        if (dictionary->isWord(word)) {
            chain.erase(chain.begin() + index1, chain.begin() + index2 + 1);
            words.push_back(word);
            score += word.length();
            return true;
        }
    }
    else {
        for (int i = index1; i >= index2; i--) {
            word += chain[i];
        }
        if (dictionary->isWord(word)) {
            chain.erase(chain.begin() + index2, chain.begin() + index1 + 1);
            words.push_back(word);
            score += word.length();
            return true;
        }
    }
    return false;
}

bool Player::getSkip() {
    return skip;
}

int Player::getScore() {
    return score;
}

string Player::getName() {
    return name;
}
