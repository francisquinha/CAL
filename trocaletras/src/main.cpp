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


int main()
{
	Dictionary dic;
	dic.readDICfile("portugues.dic");

	std::cout<<"All words have been loaded"<<std::endl;

	bool wordE = dic.checkIfWordExists("antediz");
	bool wordNE = dic.checkIfWordExists("uwwoyfwih");
	std::cout << wordE << std::endl;
	std::cout << wordNE << std::endl;
	//while(true);

	return 0;
}
