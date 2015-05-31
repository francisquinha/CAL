//
// Created by Angie on 30/05/15.
//

#include <iomanip>
#include "player.h"

using namespace std;

Player::Player(string newName, bool newType) {
    name = newName;
    type = newType;
    words = {};
    score = 0;
    skip = false;
}

vector<char> Player::turn(vector<char> chain, Dictionary * dictionary, int difficulty) {
    if (type) chain = humanTurn(chain, dictionary);
    else if (difficulty == 1) chain = diff1Turn(chain, dictionary);
    else if (difficulty == 2) chain = diff2Turn(chain, dictionary);
    else chain = diff3Turn(chain, dictionary);
    return chain;
}

vector<char> &Player::humanTurn(vector<char> &chain, Dictionary *dictionary) {
    skip = true;
    string answer {};
    int index1 {};
    int index2 {};
    cout << endl << name << ": it's your turn." << endl << endl;
    printChain(chain);
    cout << "Switch letters (y/n)? ";
    getline(cin, answer);
    if (answer == "y") {
        skip = false;
        getIndex(chain.size(), index1, "First");
        getIndex(chain.size(), index2, "Second");
        swapLetters(chain, index1, index2);
        cout << endl;
        printChain(chain);
    }
    cout << "Choose word (y/n)? ";
    getline(cin, answer);
    if (answer == "y") {
        skip = false;
        getIndex(chain.size(), index1, "First");
        getIndex(chain.size(), index2, "Last");
        string word {};
        if (removeLetters(chain, index1, index2, word, dictionary))
            cout << endl << "'" << word << "': Good! Score = " << score << "." << endl;
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
        printChain(chain);
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
            printChain(chain);
            cout << name << ": Swap "<< index1 << " " << index2 <<"." << endl << endl;
            swapLetters(chain, swapIndex1, swapIndex2);
            printChain(chain);
            string word{};
            removeLetters(chain, index1, index2, word, dictionary);
            cout << name << ": '" << word << "'. Score = " << score << "." << endl;
        }
    }
    return chain;
}

vector<char> &Player::diff2Turn(vector<char> &chain, Dictionary *dictionary) {
    skip = true;
    vector<int> indexes1 {};
    vector<int> indexes2 {};
    dictionary->allWords(string(chain.begin(), chain.end()), indexes1, indexes2);
    if (indexes1.size() > 0) {
        skip = false;
        long wordIndex = 0;
        int wordSize = indexes2[0] - indexes1[0];
        for (int i = 1; i < indexes1.size(); i++) {
            if (indexes2[i] - indexes1[i] > wordSize) {
                wordIndex = i;
                wordSize = indexes2[i] - indexes1[i];
            }
        }
        int index1 = indexes1[wordIndex];
        int index2 = indexes2[wordIndex];
        string word{};
        removeLetters(chain, index1, index2, word, dictionary);
        cout << endl;
        printChain(chain);
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
            printChain(chain);
            swapLetters(chain, swapIndex1, swapIndex2);
            cout << name << ": Swap "<< index1 << " " << index2 <<"." << endl << endl;
            printChain(chain);
            string word{};
            removeLetters(chain, index1, index2, word, dictionary);
            cout << name << ": '" << word << "'. Score = " << score << "." << endl;
        }
    }
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
        long wordIndex = 0;
        int wordSize = indexes2[0] - indexes1[0];
        for (int i = 1; i < indexes1.size(); i++) {
            if (indexes2[i] - indexes1[i] > wordSize) {
                wordIndex = i;
                wordSize = indexes2[i] - indexes1[i];
            }
        }
        int swapIndex1 = swapIndexes1[wordIndex];
        int swapIndex2 = swapIndexes2[wordIndex];
        int index1 = indexes1[wordIndex];
        int index2 = indexes2[wordIndex];
        cout << endl;
        printChain(chain);
        swapLetters(chain, swapIndex1, swapIndex2);
        cout << name << ": Swap "<< index1 << " " << index2 <<"." << endl << endl;
        printChain(chain);
        string word{};
        removeLetters(chain, index1, index2, word, dictionary);
        cout << name << ": '" << word << "'. Score = " << score << "." << endl;
    }
    else {
        dictionary->allWords(string(chain.begin(), chain.end()), indexes1, indexes2);
        if (indexes1.size() > 0) {
            skip = false;
            long wordIndex = 0;
            int wordSize = indexes2[0] - indexes1[0];
            for (int i = 1; i < indexes1.size(); i++) {
                if (indexes2[i] - indexes1[i] > wordSize) {
                    wordIndex = i;
                    wordSize = indexes2[i] - indexes1[i];
                }
            }
            int index1 = indexes1[wordIndex];
            int index2 = indexes2[wordIndex];
            string word{};
            cout << endl;
            printChain(chain);
            removeLetters(chain, index1, index2, word, dictionary);
            cout << name << ": '" << word << "'. Score = " << score << "." << endl;
        }
    }
    return chain;
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

void Player::printChain(vector<char> chain) {
    for (int i = 0; i < chain.size(); i++) cout << setw(2) << i << " ";
    cout << endl;
    for (int i = 0; i < chain.size(); i++) cout << setw(2) << chain[i] << " ";
    cout << endl << endl;
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
