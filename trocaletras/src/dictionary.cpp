#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>
//#include <stdlib.h>
//#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#define MAX_NUMBER_OF_LETTERS 7
//#define MAX_NUMBER_OF_THREADS 4

char lowerAndRemoveAcentosAndCedilha(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  if (in == 'Á'|| in == 'À' || in=='á' || in=='à' || in == 'ã' || in== 'â' || in == 'Ã' || in == 'Â') return 'a';
  if (in == 'É'|| in == 'È' || in=='é' || in=='è'|| in== 'ê') return 'e';
  if (in == 'Í'|| in == 'Ì' || in=='í' || in=='ì') return 'i';
  if (in == 'Ó'|| in == 'Ò' || in=='ó' || in=='ò' || in == 'õ' || in == 'Õ' || in == 'ô' || in== 'Ô') return 'o';
  if (in == 'Ú'|| in == 'Ù' || in=='ú' || in=='ù') return 'u';
  if (in == 'ç' || in == 'Ç') return 'c';

  return in;
}

void Dictionary::readDICfile(std::string filename)
{
	ifstream fin;

	string temp;

	fin.open(filename.c_str());

	if (fin.fail())
	{
		cout<<"Failed to load <"<<filename << ">\n";
		throw "FAILED TO LOAD DICTIONARY";
	}

	while (!fin.eof())
	{
		getline(fin,temp);
		std::transform(temp.begin(), temp.end(), temp.begin(), lowerAndRemoveAcentosAndCedilha);
		if (temp.length()>1 && temp.find('-')==std::string::npos) //avoid empty lines, chars, and composite words
			if(temp.length()<=MAX_NUMBER_OF_LETTERS) //(LIMIT STUFF) avoid long words (should be optional
				words.push_back(temp);
		//cout<<temp<<endl;
	}

	fin.close();
}

bool compareWords (string i,string j) {
	//ver se o comprimento e menor ou maior
	if (i.length()<j.length()) return true;
	else if (i.length()>j.length()) return false;
	//se tem o mesmo tamanho compara as strings
	return i<j;
}

bool Dictionary::checkIfWordExists(std::string word)
{
	return binary_search(words.begin(), words.end(), word, compareWords);
}
#if 0 //not so good implementation, works fine but it's not really efficient even with the 26 done thing
void Dictionary::addNodes(Node *node,int letterIndex)
{
	if (letterIndex>MAX_NUMBER_OF_LETTERS) return; //(LIMIT STUFF)long word, cant use more recursive calls
	int dones=0;
/*cout<<"\n-CC"<<((int)words.size()-1);
cout<<"\nmmm"<<(int)words[99].size();
cout<<"\n"<<words[words.size()-2].length();*/
	for (int i = words.size()-1;
		i>=0 &&	letterIndex<(int)words[i].length()  && (dones<26||freeWordsWhenBuildingDFA);
	i--)
	{
		unsigned int charIndex =  (unsigned int) words[i][letterIndex]- (unsigned int) 'a';
		if(charIndex>26) {cout<<"\n---:::"<<words[i][letterIndex]; continue;}

		Node* aux = &dfa;
		for(int z =0 ; z<letterIndex;z++)
			if(aux==NULL) break;
			else aux=aux->possibleDestinations[(unsigned int) words[i][z]- (unsigned int) 'a'];
		if(aux!=node) continue;

		if( node->possibleDestinations[ charIndex ] == NULL)
		{
			node->possibleDestinations[ charIndex ] = new Node();
			node->possibleDestinations[ charIndex ]->wordDone = false;
		}
		if ( (!node->possibleDestinations[ charIndex ]->wordDone||freeWordsWhenBuildingDFA)
				&& ((int) words[i].length()-1)==letterIndex )
		{
			node->possibleDestinations[ charIndex ]->wordDone = true; dones++;
			if (freeWordsWhenBuildingDFA) words.erase(words.begin()+i,words.begin()+i);
		}
	}
//cout<<"\n__";
	for(int i = 0; i<26;i++) if (node->possibleDestinations[i]!=NULL) {
		/*std::pthread_mutex_lock(&mutex);
		if(numberOfAtiveThreads<=MAX_NUMBER_OF_THREADS)
			{
				numberOfAtiveThreads++;
				std::thread t1(addNodes, node->possibleDestinations[i],letterIndex+1);
			}
		else addNodes(node->possibleDestinations[i],letterIndex+1);
		pthread_mutex_unlock(&mutex);*/
		addNodes(node->possibleDestinations[i],letterIndex+1);
	}
	//numberOfAtiveThreads--;
}
#endif

void Dictionary::buildDFA()//bool viaIndexes)
{
	for(int i = 0; i<26;i++) dfa.possibleDestinations[i]=NULL;
	//if(viaIndexes) addNodes(&dfa,0);//... ... ... ...
	//else
	for(unsigned int i=0;i<words.size(); )
	{
		bool quick=false;//not sure if this actually make it faster
		Node* node=&dfa;
		int l=words[i].length();
		for(int j = 0 ; j<l;j++)
		{
			unsigned int charIndex =  (unsigned int) words[i][j]- (unsigned int) 'a';
			if (quick) node->possibleDestinations[charIndex]=new Node();
			else if(node->possibleDestinations[charIndex]==NULL) {node->possibleDestinations[charIndex]=new Node(); quick=true;}
			node=node->possibleDestinations[charIndex];
		}
		node->wordDone=true;

		if(freeWordsWhenBuildingDFA) words.erase(words.begin());
		else i++;
	}

}

bool Dictionary::isWord(std::string word)
{
	Node* node;
	node=&dfa;
	int wordlenght=word.length();
	for(int i = 0 ; i<wordlenght ; i++)
	{
		node=node->possibleDestinations[(unsigned int)word[i]- (unsigned int) 'a'];
		if(node==NULL) return false;
	}

	return node->wordDone;
}

/*
 * turismo -> retorna tu e turismo (1 e 6
 * impar -> retorna impar mas não par (4
 * param indexes indices do caracter final das palavras encontradas
 * */
std::vector<int> Dictionary::WordsFromStart(std::string seq)
{
	vector<int> indexes;
	Node* node;
	node=&dfa;
	int wordlenght=seq.length();
	int i = 0 ;

	for(; i<wordlenght ; i++)
	{
		node=node->possibleDestinations[(unsigned int)seq[i]- (unsigned int) 'a'];
		if(node==NULL) return indexes;
		if (node->wordDone) indexes.push_back(i);
	}
	return indexes;
}


void Dictionary::allWords(std::string seq,std::vector<int> &beginWord, std::vector<int> &endWord)
{
	unsigned int originalSeqLenght_less1 = seq.length()-1;
	for(unsigned int i=0; i<originalSeqLenght_less1;++i)//-1 cause there is no need to check a single letter
	{
		vector<int> ws = WordsFromStart(seq);
		for(int j = ws.size()-1; j>=0;--j)
		{beginWord.push_back(i); endWord.push_back(i+ws[j]);}
		seq = seq.substr(1);
	}
}

vector<char> Dictionary::getCharactersFromSeq(string &seq)
{
	vector<char> ret;
	for(int i=seq.size()-1; i>=0;--i)
		{
			bool added=false;
			for(int j=ret.size()-1; j>=0&&!added;--j)
				if(ret[j]==seq[i]) added=true;
			if(!added) ret.push_back(seq[i]);
		}
	return ret;
}

//---------------------------------------------------------------
/*std::vector<int> Dictionary::WordsFromStartR1(std::string seq,char subs)
{
	vector<int> indexes;
	Node* node;
	node=&dfa;
	int wordlenght=seq.length();
	vector<Node*> innerAlternatives;


	for(int i = 0 ; i<wordlenght ; i++)
	{
		node=node->possibleDestinations[(unsigned int)seq[i]- (unsigned int) 'a'];
		if(node==NULL) return indexes;
		if (node->wordDone) indexes.push_back(i);

		//find inner subtitutions
		if(i>0){
			if(innerAlternatives) innerAlternatives.push_back();
		}
	}
	return indexes;
}

void Dictionary::fromStartMissingLetterPresentInSeq(string &oseq, vector<char> &charinseq,int startIndex,std::vector<int> &beginWord, std::vector<int> &endWord, std::vector<int> &swap1,std::vector<int> &swap2)
{
	string seq=oseq.substr(startIndex);
	unsigned int seqLenght_less1 = seq.length()-1;
	for(unsigned int i=0; i<seqLenght_less1;++i)
	{
		for(int c = charinseq.size()-1;c>=0;--c)//tentar p/ tds os caracteres presentes em seq
		{
			if(seq[i]!= charinseq[c]){
				string seq2 = seq;
				char toReplace = seq2[i];
				seq2[i]=charinseq[c];
				vector<int> ws = WordsFromStartR1(seq,toReplace);
				for(int j = ws.size()-1; j>=0;--j)//check for each case if the missing letter is present outside the word
				{
					for(int a=0; a<startIndex;a++)//find outer subtitutions
						if(charinseq[c]==oseq[a]) {beginWord.push_back(startIndex); endWord.push_back(startIndex+ws[j]); swap1.push_back(startIndex+(int)i);swap2.push_back(a);    }
					for(int a=startIndex+ws[j]+1; a<seq.length();a++)
						if(charinseq[c]==oseq[a]) {beginWord.push_back(startIndex); endWord.push_back(startIndex+ws[j]); swap1.push_back(startIndex+(int)i);swap2.push_back(a);    }
				}
			}

		}
	}
}

void Dictionary::allMissingLetterPresentInSeq(std::string seq,int startIndex, std::vector<int> &beginWord, std::vector<int> &endWord, std::vector<int> &swap1,std::vector<int> &swap2)
{
	vector<char> charinseq = getCharactersFromSeq(seq);
	for(unsigned int i=0; i<seq.size();++i)
		fromStartMissingLetterPresentInSeq(seq, charinseq, startIndex ,beginWord, endWord, swap1,swap2);
}
*/

void Dictionary::allWordsWithSwap(string seq,int swapIndex1, int swapIndex2,vector<int> &beginWord, vector<int> &endWord,vector<int> &swap1,std::vector<int> &swap2)
{
    int limit = swapIndex1>swapIndex2? swapIndex1:swapIndex2;
	for( int i=0; i<=limit;++i)//-1 cause there is no need to check a single letter
	{
		vector<int> ws = WordsFromStart(seq);
		for(int j = ws.size()-1; j>=0;--j) //one of swapped letters must be inside found word
			if( (i<=swapIndex1 && swapIndex1<=i+ws[j] )|| (i<=swapIndex2 && swapIndex2<=i+ws[j]) )
		{beginWord.push_back(i); endWord.push_back(i+ws[j]); swap1.push_back(swapIndex1);swap2.push_back(swapIndex2);}
		seq = seq.substr(1);
	}
}

void Dictionary::findSwapOnePossibilities(std::string seq, std::vector<int> &beginWord, std::vector<int> &endWord, std::vector<int> &swap1,std::vector<int> &swap2)
{

	for(int i = seq.size()-1;i>0;--i)
		for(int j = i-1; j>=0;--j)
		{
			if(seq[j] == seq[i]) continue;//no need to check equal chars
			string auxSeq=seq;
			auxSeq[i] = seq[j]; auxSeq[j] = seq[i];
			//cout<< auxSeq <<endl;
			allWordsWithSwap(auxSeq,i,j,beginWord,endWord,swap1,swap2);
		}
}

//vector<int> possibleIndexesO = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
string Dictionary::selectRandomWordsAux(Node* node,int index,int numberOfLetters)//backtracking solution
{
	vector<int> possibleIndexes; //= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	for (int i =0;i<26;++i) possibleIndexes.push_back(i);
	string rest="";
	 int choosenIndex;
	 for(int i=0;i<26;++i){
	 choosenIndex = rand() % possibleIndexes.size();
	 if (node->possibleDestinations[choosenIndex]==NULL)possibleIndexes.erase(possibleIndexes.begin()+choosenIndex);
	 else
		{
		 if(index+1==numberOfLetters)
		 {
			 if (node->possibleDestinations[choosenIndex]->wordDone) return ( (char)('a' + choosenIndex) + rest );//ok, word was found
			 else possibleIndexes.erase(possibleIndexes.begin()+choosenIndex);
		 }
		 else if (  (rest=selectRandomWordsAux(node->possibleDestinations[choosenIndex],index+1,numberOfLetters))!="?" ) return ( (char)('a' + choosenIndex) + rest );
		 else possibleIndexes.erase(possibleIndexes.begin()+choosenIndex);
		 }
	 }
	 return "?";
}

vector<string> Dictionary::selectRandomWords(int numberOfWords,int maxNumberOfletter)
{

	 srand (time(NULL));
	vector<string> ret;
	for(;numberOfWords>0;--numberOfWords){

		 int number_of_letters = rand() % (maxNumberOfletter-1) + 2;

			string newS = selectRandomWordsAux(&dfa,0,number_of_letters);

			if (newS!="?") ret.push_back(newS);
			else cout<<"warning on selectRandomWords: no word of given length found"<<endl;
	}
	return ret;
}


void Dictionary::freeNodeHeap(Node* node)
{
	for(int i = 0; i<26;i++) if (node->possibleDestinations[i]!=NULL) freeNodeHeap(node->possibleDestinations[i]);
	delete node;
}
void Dictionary::freeHeap()
{
	for(int i = 0; i<26;i++) if (dfa.possibleDestinations[i]!=NULL) freeNodeHeap(dfa.possibleDestinations[i]);
}

