#ifndef TROCALETRAS_DICTIONARY_H
#define TROCALETRAS_DICTIONARY_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
//#include <stdlib.h>
//#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

struct Node
{
public:
    bool wordDone;///<indicates if a word was completed or if more letters are required to form a word
    /**use the char as index, instead of creating nodes with explicit connections.
     *  these connections are made implicit. NULL means that can't form any word with the letter*/
    unsigned int possibleDestinations[26];///<instead of using pointers this variable indicates the index in an array

    /*Node()
    {
        for(int i = 0; i<26;i++) possibleDestinations[i]=0;
        wordDone=false;
    }*/
};

class Dictionary
{

public:

    std::vector< std::string > words;

    bool freeWordsWhenBuildingDFA;

    unsigned long dfaSize;
    struct Node* dfa;//should be an array
    int numberOfAtiveThreads;

    void readDICfile(std::string filename);

    bool checkIfWordExists(std::string word);

    void buildDFA_fromWords();
    void buildDFA_fromBinaryFile(std::string filename);
    void saveDFA_toBinaryFile(std::string filename);
    bool isWord(std::string word);
    std::vector<int> WordsFromStart(std::string seq);
    void allWords(std::string seq,std::vector<int> &beginWord, std::vector<int> &endWord);
    std::vector<char> getCharactersFromSeq(std::string &seq);
    bool hasWordsFromStart(std::string seq);
    bool hasAnyWords(std::string seq);

    void allWordsWithSwap(std::string seq,int swapIndex1, int swapIndex2,std::vector<int> &beginWord, std::vector<int> &endWord,std::vector<int> &swap1,std::vector<int> &swap2);
    void findSwapOnePossibilities(std::string seq, std::vector<int> &beginWord, std::vector<int> &endWord, std::vector<int> &swap1,std::vector<int> &swap2);

    std::string selectRandomWordsAux(int node,int index,int numberOfLetters);
    std::vector<std::string> selectRandomWords(int numberOfWords,int maxNumberOfletter);

    int seqLenght; int ocurrences[26];//aux vars to be used by the methods below
    /*debug func*/void show_permutations_withoutrepetitions(std::string str ,int last_position,int charIndex,int how_many_done,int filled);
    /*debug func*/void debug_charset_has_possible_words(std::string seq);
    bool check_permutations_withoutrepetitions(std::string str ,int last_position,int charIndex,int how_many_done,int filled);
    bool charset_has_possible_words(std::string seq);

    //void freeNodeHeap(Node* node);
    void freeHeap();
};

#endif //TROCALETRAS_DICTIONARY_H
