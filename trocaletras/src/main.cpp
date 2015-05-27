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

	dic.debug_charset_has_possible_words("aa");
	cout<<"----"<<endl;
	dic.debug_charset_has_possible_words("aba");
	cout<<"----"<<endl;
	dic.debug_charset_has_possible_words("abab");
	cout<<"----"<<endl;
	dic.debug_charset_has_possible_words("naazaz");
	cout<<"----"<<endl;
	return 0;
	dic.readDICfile("portugues.dic");

	std::cout<<"All words have been loaded"<<std::endl;

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
	dic.buildDFA();

	cout<<"dfa done"<<endl;
	vector<string> sss = dic.selectRandomWords(5,7);
	for (int i = sss.size()-1;i>=0;--i) cout <<i<<":"<< sss[i] <<endl;

	string aaaaa="ocavarla";// oca(0,2 | ca(1,2 | cava(1,4 | cavar(1,5 | va(3,4 | ar(4,5 | la(6,7
	vector<int> ee1,ee2;
	dic.allWords(aaaaa,ee1, ee2);
	for (int i = ee1.size()-1;i>=0;--i) cout <<i<<":"<< ee1[i]<<","<<ee2[i] <<endl;

	cout<<"- - - - -"<<endl;
	vector<int> xx1,xx2,ss1,ss2;
	dic.findSwapOnePossibilities(aaaaa, xx1, xx2, ss1,ss2);
	for (int i = xx1.size()-1;i>=0;--i) cout <<i<<":"<< xx1[i]<<","<<xx2[i] <<" | "<< ss1[i]  <<","<<ss2[i] <<endl;

	/*
	 * ocavarla
	 * 63:0,2 | 1,0  coa (coá)
62:0,4 | 1,0	coava
61:2,4 | 2,0	ac(ova)rla
60:2,5 | 2,0	ac(ovar)la
59:1,4 | 2,0	a(cova)rla
58:0,2 | 2,0	(aco)varla  (aço)
57:2,3 | 3,0	vc(ao)arla
56:1,3 | 3,0	v(cao)arla (cão)
55:3,4 | 3,1	ova(ca)rla (cá)
54:3,6 | 3,1	ova(carl)a nome ingles carl tb esta no dic usado
53:3,7 | 3,1	ova(carla)
52:1,2 | 3,1	o(va)carla	vá
51:1,4 | 3,1	o(vaca)rla
50:0,2 | 3,1	(ova)carla
49:2,3 | 3,2	oc(va)arla vá
48:4,7 | 4,0	acav(orla)
47:2,4 | 4,0	ac(avo)rla (avó/ô)
46:1,4 | 4,0	a(cavo)rla
45:5,7 | 5,0	rcava(ola) olá //la não aparece pk ja existia independentemente da troca!
44:4,5 | 5,0	rcav(ao)la
43:3,5 | 5,0	rca(vao)la
42:5,7 | 5,1	...
41:1,2 | 5,1
40:0,2 | 5,1
39:0,4 | 5,1
38:5,7 | 5,2
37:3,4 | 5,3
36:2,3 | 5,3
35:2,4 | 5,3
34:1,4 | 5,3
33:5,7 | 5,4
32:4,5 | 5,4
31:4,7 | 5,4
30:5,6 | 6,0
29:5,7 | 6,0
28:4,6 | 6,0
27:3,6 | 6,0
26:2,6 | 6,0
25:6,7 | 6,1
24:4,7 | 6,1
23:1,2 | 6,1
22:1,4 | 6,1
21:1,5 | 6,1
20:0,2 | 6,1
19:5,6 | 6,2
18:4,6 | 6,2
17:3,6 | 6,2
16:6,7 | 6,3
15:3,4 | 6,3
14:3,5 | 6,3
13:3,7 | 6,3
12:2,4 | 6,3
11:2,5 | 6,3
10:1,3 | 6,3
9:1,4 | 6,3
8:1,5 | 6,3
7:5,6 | 6,4
6:6,7 | 6,5
5:2,5 | 6,5
4:5,6 | 7,6
3:4,6 | 7,6
2:3,6 | 7,6
1:3,7 | 7,6
0:1,6 | 7,6
	 * */

	return 0;

	std::cout << dic.isWord("tudo") << std::endl;
	std::cout << dic.isWord("nada") << std::endl;
	std::cout << dic.isWord("rrr") << std::endl;//n
	std::cout << dic.isWord("bem") << std::endl;
	std::cout << dic.isWord("lrlm") << std::endl;//n
	std::cout << dic.isWord("carro") << std::endl;
	std::cout << dic.isWord("bola") << std::endl;
	std::cout << dic.isWord("faaa") << std::endl;//n
	std::cout << dic.isWord("par") << std::endl;
	std::cout << dic.isWord("impar") << std::endl;
	std::cout << dic.isWord("turismo") << std::endl;
	std::cout << dic.isWord("tu") << std::endl;
	std::cout << dic.isWord("i") << std::endl;//n
	std::cout<<"-------------------------"<<endl;
	 //turismo -> retorna tu e turismo (1 e 6
		 //impar -> retorna impar mas não par (4
	vector<int> a;
	vector<int> b;
	a=dic.WordsFromStart("turismo");
	b=dic.WordsFromStart("impar");
	for (int i = 0 ; i<a.size();i++) cout<< a[i] <<"|"; cout<<endl;
	for (int i = 0 ; i<b.size();i++) cout<< b[i] <<"|"; cout<<endl;

	dic.freeHeap();
	std::cout<<"\n----end";
	//while(true);



	return 0;
}
