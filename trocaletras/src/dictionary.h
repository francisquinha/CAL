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

	void addNodes(Node *node,int letterIndex);
	void buildDFA();
	bool isWord(std::string word);
	void freeNodeHeap(Node* node);
	void freeHeap();
};
