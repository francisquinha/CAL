/*
 * main.cpp
 *
 *  Created on: 07/05/2015
 *      Author: Bruno
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

using namespace std;

int main()
{
/*
	string aasd="jjj";
	cout<< (aasd + (char)('a'+2)) << endl;
	return 0;
	*/

	Dictionary dic;

	/*dic.debug_charset_has_possible_words("aa");
	cout<<"----"<<endl;
	dic.debug_charset_has_possible_words("aba");
	cout<<"----"<<endl;
	dic.debug_charset_has_possible_words("abab");
	cout<<"----"<<endl;
	dic.debug_charset_has_possible_words("naazaz");
	cout<<"----"<<endl;
	return 0;*/
	//dic.readDICfile("US.dic");



	//bool wordE = dic.checkIfWordExists("tudo");
	//bool wordNE = dic.checkIfWordExists("uwwoyfwih");
	//std::cout << wordE << std::endl;
	//std::cout << wordNE << std::endl;
	//while(true);

	std::vector< char > letters;
	for (int i = 0; i<26 ; i++)	letters.push_back('a'+i);
	for (int i = 0; i<26 ; i++)	std::cout<<letters[i];
	std::cout << "\n";

	dic.freeWordsWhenBuildingDFA=true;
	//dic.buildDFA_fromWords();
	//dic.saveDFA_toBinaryFile("US.dicnodes");//portugues_dictionary_nodes.data");
	//return 0;

	dic.buildDFA_fromBinaryFile("US.dicnodes");
	std::cout<<"All nodes have been loaded"<<std::endl;
	cout<<"dfa done"<<endl;

	vector<string> sss = dic.selectRandomWords(5,7);
	for (int i = sss.size()-1;i>=0;--i) cout <<i<<":"<< sss[i] <<endl;

	string aaaaa="acarraiagecat";//
	vector<int> ee1,ee2;
	dic.allWords(aaaaa,ee1, ee2);
	for (int i = ee1.size()-1;i>=0;--i) cout <<i<<":"<< ee1[i]<<","<<ee2[i] <<endl;

	cout<<"- - - - -"<<endl;
	vector<int> xx1,xx2,ss1,ss2;
	dic.findSwapOnePossibilities(aaaaa, xx1, xx2, ss1,ss2);
	for (int i = xx1.size()-1;i>=0;--i) cout <<i<<":"<< xx1[i]<<","<<xx2[i] <<" | "<< ss1[i]  <<","<<ss2[i] <<endl;


	//return 0;
	cout<<"_______________________"<<endl;

	std::cout << dic.isWord("man") << std::endl;
	std::cout << dic.isWord("nothing") << std::endl;
	std::cout << dic.isWord("rrr") << std::endl;//n
	std::cout << dic.isWord("yes") << std::endl;
	std::cout << dic.isWord("lrlm") << std::endl;//n
	std::cout << dic.isWord("car") << std::endl;
	std::cout << dic.isWord("ball") << std::endl;
	std::cout << dic.isWord("faaa") << std::endl;//n
	std::cout << dic.isWord("famous") << std::endl;
	std::cout << dic.isWord("odd") << std::endl;
	std::cout << dic.isWord("turism") << std::endl;
	std::cout << dic.isWord("you") << std::endl;
	std::cout << dic.isWord("c") << std::endl;//n
	std::cout<<"-------------------------"<<endl;

	vector<int> a;
	vector<int> b;
	a=dic.WordsFromStart("carriage");//car,carriage 2,7
	b=dic.WordsFromStart("cabbage");//cab,cabbage 2,6 age is not found in both cause its only checking from start
	for (int i = 0 ; i<a.size();i++) cout<< a[i] <<"|"; cout<<endl;
	for (int i = 0 ; i<b.size();i++) cout<< b[i] <<"|"; cout<<endl;

	dic.freeHeap();
	std::cout<<"\n----end";
	//while(true);



	return 0;
}
