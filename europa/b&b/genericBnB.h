/*
 * genericBnB.h
 *
 *  Created on: 06/04/2015
 *      Author: Bruno
 */

#ifndef GENERICBNB_H_
#define GENERICBNB_H_

//===============================================================================================================
// BRANCH&BOUND DE/ACTIVATE DEBUG (see debug funcs implementation at the end of the header)
//===============================================================================================================
#define DEBUG_BNB

#ifdef DEBUG_BNB
#include <iostream>

template <class T>
class BnB_UP;

template <class T>
void check_order(BnB_UP<T> *bnb);

void BNBdebugger(std::string label, void (*debugCode)(void*),void *debugCodeArgs )
{
	if (debugCode==NULL) {std::cout << "\nnBNBdebugger(error):"<< label <<" --due to NULL FUNC POINTER--\n"; return;}
	try{
	std::cout << "\nBNBdebugger(start):" << label <<"\n";
	(*debugCode)(debugCodeArgs);
	std::cout << "\nBNBdebugger(end):" << label <<"\n";
	}catch(...)
	{ std::cout << "\nnBNBdebugger(error):"<< label <<"\n"; }
}
#else
void BNBdebugger(){return;};
#endif /*DEBUG_BNB*/

//===============================================================================================================
// GENERIC BRANCH&BOUND IMPLEMENTATION
//===============================================================================================================
#include <vector>
#include <algorithm>
using namespace std;

/*
 * saves an element data needed to use BnB solution
 * */
struct BnB_elementDATA
{
	double cost;
	double value;
	double value_cost_ratio;
};

/*
 * creates alias for a type that
 * saves the element data and a pointer to the element
 * inside the BnB class
 * */
template<typename T>
struct BnB_pair {
  typedef pair<BnB_elementDATA,T*> typeT;
};

class BnB_node{
	double cost;
	double value;
	double bound;
};


//upperbound bnb
template <class T>
class BnB_UP{

/*
 * saves info for each element (cost,value,value/cost ratio)
 * and a pointer for the respective element
 * ordered by higher value/cost ratio
 * */
//typename BnB_pair<T>::typeT ordered_elements;
	vector< typename BnB_pair<T>::typeT > ordered_elements;

double maxCost;

public:
friend void check_order<T>(BnB_UP<T> *bnb);
static bool compareElems(typename BnB_pair<T>::typeT a,typename BnB_pair<T>::typeT b)
{
	return a.first.value_cost_ratio>b.first.value_cost_ratio;
}
BnB_UP(vector<T> &elements, double maxCost,double (T::*getCost)(void),double (T::*getValue)(void)  )
{
	this->maxCost=maxCost;
	//copy elements
	for(typename vector<T>::iterator it=elements.begin(); it!=elements.end();it++)
	{
		BnB_elementDATA elem_data = {
		((*it).*getCost)(),  // cost
		((*it).*getValue)(),  // value
		0//ratio
		};
		elem_data.value_cost_ratio = elem_data.value/elem_data.cost;
		ordered_elements.push_back( pair<BnB_elementDATA,T*>(
				elem_data
				, &(*it)  ) );
	}
	//sort
	sort(ordered_elements.begin(),ordered_elements.end(),compareElems);
	BNBdebugger("VERIFY ORDER",(void(*)(void*)) &check_order<T>,this);
}
BnB_UP(vector<T*> &elements, double maxCost,void (T::*getCost)(void),void (T::*getValue)(void)  )
{
	this->maxCost=maxCost;
	//copy elements
	for(typename vector<T*>::iterator it=elements.begin(); it!=elements.end();it++)
	{
		BnB_elementDATA elem_data = {
		((**it).*getCost)(),  // cost
		((**it).*getValue)(),  // value
		0//ratio
		};
		elem_data.value_cost_ratio = elem_data.value/elem_data.cost;
		ordered_elements.push_back( new typename BnB_pair<T>::typeT(
				elem_data
				, (*it)  ) );
	}
	//sort
	sort(ordered_elements.begin(),ordered_elements.end(),compareElems);
	BNBdebugger("VERIFY ORDER",(void(*)(void*)) &check_order<T>,this);
}

vector<T*> findSolution();

};


//===============================================================================================================
// BRANCH&BOUND DEBUG FUNCS
//===============================================================================================================
#ifdef DEBUG_BNB

template <class T>
void check_order(BnB_UP<T> *bnb)
{
	typename vector< typename BnB_pair<T>::typeT >::iterator  it;
	for(it=bnb->ordered_elements.begin(); it!=bnb->ordered_elements.end();it++)
	cout<< "ratio=" << it->first.value_cost_ratio << "\n";
}

#endif /*DEBUG_BNB*/



#endif /* GENERICBNB_H_ */
