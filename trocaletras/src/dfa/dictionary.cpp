#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>
//#include <stdlib.h>

using namespace std;


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
			if(temp.length()<6) //(LIMIT STUFF) avoid long words (should be optional
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

void Dictionary::addNodes(Node *node,int letterIndex)
{
	if (letterIndex>5) return; //(LIMIT STUFF)long word, cant use more recursive calls
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
	for(int i = 0; i<26;i++) if (node->possibleDestinations[i]!=NULL) addNodes(node->possibleDestinations[i],letterIndex+1);
}



void Dictionary::buildDFA()
{
	for(int i = 0; i<26;i++) dfa.possibleDestinations[i]=NULL;
	addNodes(&dfa,0);
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

