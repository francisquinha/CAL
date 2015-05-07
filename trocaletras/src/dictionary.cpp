#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>
//#include <stdlib.h>

using namespace std;

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


