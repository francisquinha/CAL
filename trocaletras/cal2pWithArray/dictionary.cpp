#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>
//#include <stdlib.h>
//#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#define MAX_NUMBER_OF_LETTERS 50
#define MAX_NUMBER_OF_NODES 600000 //596535 no portugues.dic
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
		if (temp.length()>1 && temp.find('-')==std::string::npos) //avoid empty lines, chars, and composite words, and one letter words
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

void Dictionary::buildDFA_fromWords()//bool viaIndexes)
{
	dfaSize=1;
	dfa = (Node*) malloc(sizeof(Node)*MAX_NUMBER_OF_NODES);
	for(int i = 0; i<26;i++) dfa[0].possibleDestinations[i]=0;//zero means none cause its the starting node

	for(unsigned int i=0;i<words.size(); )
	{

		bool quick=false;//not sure if this actually make it faster
		Node* node=dfa;
		int l=words[i].length();

		//not really precise cause letters may repeat but work anyway
		if(l+dfaSize>MAX_NUMBER_OF_NODES) {cout<<"Dictionary was to big to be fully loaded!"; return;}

		for(int j = 0 ; j<l;j++)
		{
			//cout<<words[i]<<endl;
			cout<<dfaSize<<endl;
			unsigned int charIndex =  (unsigned int) words[i][j]- (unsigned int) 'a';
			if (quick)
			{
				node->possibleDestinations[charIndex]=dfaSize;
				//dfa = (Node*) realloc(dfa,sizeof(struct Node)*(dfaSize+1));
				for(int k = 0; k<26;k++) dfa[dfaSize].possibleDestinations[k]=0;
				dfaSize++;
			}
			else if(node->possibleDestinations[charIndex]==0)
			{
				node->possibleDestinations[charIndex]=dfaSize;
				//dfa = (Node*) realloc(dfa,sizeof(struct Node)*(dfaSize+1));
				for(int k = 0; k<26;k++) dfa[dfaSize].possibleDestinations[k]=0;
				dfaSize++;
				quick=true;
			}
			node=&(dfa[node->possibleDestinations[charIndex]]);
		}
		node->wordDone=true;

		if(freeWordsWhenBuildingDFA) words.erase(words.begin());
		else i++;
	}

}

void Dictionary::buildDFA_fromBinaryFile(std::string filename)
{
	  ifstream myFile(filename.c_str(), ios::in | ios::binary);
	  dfa = (Node*) malloc(sizeof(Node)*MAX_NUMBER_OF_NODES);
	  myFile.read( (char*) dfa,sizeof(struct Node)*MAX_NUMBER_OF_NODES);
	  myFile.close();
}
void Dictionary::saveDFA_toBinaryFile(std::string filename)
{
  ofstream myFile(filename.c_str(), ios::out | ios::binary);
  myFile.write( (char*) dfa,sizeof(struct Node)*MAX_NUMBER_OF_NODES);
  myFile.close();
}

bool Dictionary::isWord(std::string word)
{
	Node* node;
	node=dfa;
	int wordlenght=word.length();
	for(int i = 0 ; i<wordlenght ; i++)
	{
		node=&dfa[node->possibleDestinations[(unsigned int)word[i]- (unsigned int) 'a']];
		if(node==0) return false;
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
	node=dfa;
	int wordlenght=seq.length();
	int i = 0 ;

	for(; i<wordlenght ; i++)
	{
		node=&dfa[node->possibleDestinations[(unsigned int)seq[i]- (unsigned int) 'a']];
		if(node==0) return indexes;
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


bool Dictionary::hasWordsFromStart(std::string seq)
{
	Node* node;
	node=dfa;
	int wordlenght=seq.length();
	int i = 0 ;

	for(; i<wordlenght ; i++)
	{
		node=&dfa[node->possibleDestinations[(unsigned int)seq[i]- (unsigned int) 'a']];
		if(node==0) return false;
		if (node->wordDone) return true;
	}
	return false;
}
bool Dictionary::hasAnyWords(std::string seq)
{
	unsigned int originalSeqLenght_less1 = seq.length()-1;
	for(unsigned int i=0; i<originalSeqLenght_less1;++i)//-1 cause there is no need to check a single letter
	{
		if( hasWordsFromStart(seq) ) return true;
		seq = seq.substr(1);
	}
	return false;
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
			 if (dfa[node->possibleDestinations[choosenIndex]].wordDone) return ( (char)('a' + choosenIndex) + rest );//ok, word was found
			 else possibleIndexes.erase(possibleIndexes.begin()+choosenIndex);
		 }
		 else if (  (rest=selectRandomWordsAux(&dfa[node->possibleDestinations[choosenIndex]],index+1,numberOfLetters))!="?" ) return ( (char)('a' + choosenIndex) + rest );
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

			string newS = selectRandomWordsAux(dfa,0,number_of_letters);

			if (newS!="?") ret.push_back(newS);
			else cout<<"warning on selectRandomWords: no word of given length found"<<endl;
	}
	return ret;
}

/*the smartest implementation i could think of... quite happy with it =) */
//USE THIS ONE TO DEBUG PERMUTATIONS
void Dictionary::show_permutations_withoutrepetitions(string str ,int last_position,int charIndex,int how_many_done,int filled)
{
	//stop when str is filled
	if(filled==seqLenght)//could also go to last charInex without using an extra var... should be faster this way i suppose? not sure tho
	{
		cout<<str<<endl;//debug
		return;
	}

	if (how_many_done==ocurrences[charIndex])
		{
		show_permutations_withoutrepetitions(str, 0, charIndex+1,0, filled);
		return;
		}

	//for(int i=last_position+1; i<seqLenght + how_many_done-ocurrences[charIndex]+1; ++i) if (str[i]==' ')
	for(int i = seqLenght + how_many_done-ocurrences[charIndex]+1; i>=last_position;  --i) if (str[i]==' ')//less intuitive but faster
	{
		//cout<<i<<endl;//debug
		string newStr=str; newStr[i]=(char) ( (int) 'a' +charIndex);
		show_permutations_withoutrepetitions(newStr, i, charIndex,how_many_done+1,filled+1);
	}

}

bool Dictionary::check_permutations_withoutrepetitions(string str ,int last_position,int charIndex,int how_many_done,int filled)
{
	//stop when str is filled
	if(filled==seqLenght)//could also go to last charInex without using an extra var... should be faster this way i suppose? not sure tho
		return hasAnyWords(str);

	if (how_many_done==ocurrences[charIndex])
		return check_permutations_withoutrepetitions(str, 0, charIndex+1,0, filled);


	//for(int i=last_position+1; i<seqLenght + how_many_done-ocurrences[charIndex]+1; ++i) if (str[i]==' ')
	for(int i = seqLenght + how_many_done-ocurrences[charIndex]+1; i>=last_position;  --i) if (str[i]==' ')//less intuitive but faster
	{
		//cout<<i<<endl;//debug
		string newStr=str; newStr[i]=(char) ( (int) 'a' +charIndex);
		if (check_permutations_withoutrepetitions(newStr, i, charIndex,how_many_done+1,filled+1) ) return true;
	}
	return false;
}

void Dictionary::debug_charset_has_possible_words(std::string seq)
{
	seqLenght = seq.length();
	for(int i = 0;i<26;++i) ocurrences[i] = 0;
	string base;
	for(int i=seqLenght-1;i>=0;--i ) {base+=" "; ocurrences[ (unsigned int) seq[i]- (unsigned int) 'a' ]++;   }
	//cout<<"..."<<ocurrences[0]<<endl;//debug
	//cout<<base.length() <<"|"<<seqLenght<<endl;//debug
	show_permutations_withoutrepetitions(base,0,0,0,0);
}

bool Dictionary::charset_has_possible_words(std::string seq)
{
	seqLenght = seq.length();
	for(int i = 0;i<26;++i) ocurrences[i] = 0;
	string base;
	for(int i=seqLenght-1;i>=0;--i ) {base+=" "; ocurrences[ (unsigned int) seq[i]- (unsigned int) 'a' ]++;   }
	return check_permutations_withoutrepetitions(base,0,0,0,0);
}


void Dictionary::freeHeap()
{
	free(dfa);
}

