#include <string>
#include <vector>

class Node
{
public:
	bool wordDone;///<indicates if a word was completed or if more letters are required to form a word
	/**use the char as index, instead of creating nodes with explicit connections.
	 *  these connections are made implicit. NULL means that can't form any word with the letter*/
	Node* possibleDestinations[26];

	Node()
	{
		for(int i = 0; i<26;i++) possibleDestinations[i]=NULL;
		wordDone=false;
	}
};

class Dictionary
{

public:

	std::vector< std::string > words;

	bool freeWordsWhenBuildingDFA;
	Node dfa;
	int numberOfAtiveThreads;

	void readDICfile(std::string filename);

	bool checkIfWordExists(std::string word);

	//void addNodes(Node *node,int letterIndex);
	void buildDFA();//bool viaIndexes);
	bool isWord(std::string word);
	std::vector<int> WordsFromStart(std::string seq);
	void allWords(std::string seq,std::vector<int> &beginWord, std::vector<int> &endWord);
	std::vector<char> getCharactersFromSeq(std::string &seq);
	bool hasWordsFromStart(std::string seq);
	bool hasAnyWords(std::string seq);

/* problem: in "ocavarla"...missing1:cao,lavar,vaca. would not recognize vaca
	void fromStartMissingLetterPresentInSeq(std::string &oseq, std::vector<char> &charinseq,int startIndex,std::vector<int> &beginWord, std::vector<int> &endWord, std::vector<int> &swap1,std::vector<int> &swap2);
	void allMissingLetterPresentInSeq(std::string seq,int startIndex,std::vector<int> &beginWord, std::vector<int> &endWord, std::vector<int> &swap1,std::vector<int> &swap2);
*/

	void allWordsWithSwap(std::string seq,int swapIndex1, int swapIndex2,std::vector<int> &beginWord, std::vector<int> &endWord,std::vector<int> &swap1,std::vector<int> &swap2);
	void findSwapOnePossibilities(std::string seq, std::vector<int> &beginWord, std::vector<int> &endWord, std::vector<int> &swap1,std::vector<int> &swap2);

	std::string selectRandomWordsAux(Node* node,int index,int numberOfLetters);
	std::vector<std::string> selectRandomWords(int numberOfWords,int maxNumberOfletter);

	int seqLenght; int ocurrences[26];//aux vars to be used by the methods below
	/*debug func*/void show_permutations_withoutrepetitions(std::string str ,int last_position,int charIndex,int how_many_done,int filled);
	/*debug func*/void debug_charset_has_possible_words(std::string seq);
	bool check_permutations_withoutrepetitions(std::string str ,int last_position,int charIndex,int how_many_done,int filled);
	bool charset_has_possible_words(std::string seq);

	void freeNodeHeap(Node* node);
	void freeHeap();
};
