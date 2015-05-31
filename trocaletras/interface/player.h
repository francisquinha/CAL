//
// Created by Angie on 30/05/15.
//

#ifndef TROCALETRAS_PLAYER_H
#define TROCALETRAS_PLAYER_H

#include <iosfwd>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "newdictionary.h"

class Player {

    std::string name;
    std::vector<std::string> words;
    int score;
    bool type; // true - human, false - computer
    bool skip;

public:
    Player(std::string newName, bool newType);

    std::vector<char> turn(std::vector<char> chain, Dictionary *dictionary, int difficulty);

    void getIndex(unsigned long chainSize, int &index, std::string which);

    bool isNumber(const std::string number) const;

    void swapLetters(std::vector<char> &chain, int index1, int index2);

    void printChain(std::vector<char> chain);

    void printReverseChain(std::vector<char> chain);

    bool removeLetters(std::vector<char> &chain, int index1, int index2, std::string &word, Dictionary *dictionary);

    std::vector<char> &humanTurn(std::vector<char> &chain, Dictionary *dictionary);

    std::vector<char> &diff1Turn(std::vector<char> &chain, Dictionary *dictionary);

    std::vector<char> &diff2Turn(std::vector<char> &chain, Dictionary *dictionary);

    std::vector<char> &diff3Turn(std::vector<char> &chain, Dictionary *dictionary);

    bool getSkip();

    int getScore();

    std::string getName();

    long getBest(const std::vector<int> &indexes1, const std::vector<int> &indexes2) const;
};

#endif //TROCALETRAS_PLAYER_H
