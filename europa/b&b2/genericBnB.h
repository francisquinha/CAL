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
void BNBdebugger(){};
#endif /*DEBUG_BNB*/
//SECTION DEBBUGS
//outside solution checks
#define DEBUG1
#ifdef DEBUG1
#define DEBUG_CODE1(A) A
#else
#define DEBUG_CODE1(A){}
#endif
//findUpperBound checks
#define DEBUG2
#ifdef DEBUG2
#define DEBUG_CODE2(A) A
#else
#define DEBUG_CODE2(A){}
#endif
//inside solution cycle checks
//#define DEBUG3
#ifdef DEBUG3
#define DEBUG_CODE3(A) A
#else
#define DEBUG_CODE3(A){}
#endif
//===============================================================================================================
// GENERIC BRANCH&BOUND IMPLEMENTATION
//===============================================================================================================
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

#define EPSILON 0.001f // 1/1000

//===================================
/*
 * saves an element data needed to use BnB solution
 * */
struct BnB_elementDATA
{
	double cost;
	double value;
	double value_cost_ratio;
};
//===================================
/*
 * creates alias for a type that
 * saves the element data and a pointer to the element
 * inside the BnB class
 * */
template<typename T>
struct BnB_pair {
	typedef pair<BnB_elementDATA,T*> typeT;
};
//===================================
class BnB_node{
public:
	double cost;
	double value;
	double bound;

	int index;///<index of the un/checked item.
	BnB_node* parent;///<the parent node. should be NULL if is first node.
	/*
	 * thought of some other way but not sure...
	 * hmmm...could be faster no???
	unsigned int itemsChecked;
	 // each bit represents an item (bit 1 -> 1st item, and so on...)
	 // 1 = used/checked | 0 = not used/checked
	//could eleminate initial nodes
	 * should use long[] so if there are plenty of items it can still be processed
	unsigned long selections;
	011100110.00000(0...) -> items checked = 9
	 */

	BnB_node(double cost,double value, double bound, int index,BnB_node* parent):cost(cost),value(value),bound(bound),index(index),parent(parent){}

	virtual bool checked() = 0;

	/*friend bool operator<(const BnB_node &a,const BnB_node &b)
	{
		return a.bound<b.bound;
	}*/
};
class BnB_node_checked:public BnB_node
{
	public:
	bool checked(){return true;}
	BnB_node_checked(double cost,double value, double bound, int index,BnB_node* parent):BnB_node(cost,value,bound,index,parent){}
};
class BnB_node_notChecked:public BnB_node
{
	public:
	int lastItemInBoundIndex;
	double lastItemInBoundCostUsed;
	bool checked(){return false;}
	BnB_node_notChecked(double cost,double value, double bound, int index,BnB_node* parent,int liibIndex,double liibCostUsed):
		BnB_node(cost,value,bound,index,parent),lastItemInBoundIndex(liibIndex),lastItemInBoundCostUsed(liibCostUsed){}
};
//- - - - - - - - - - - - - - - - - -
struct compare_BnBnodePointers
{
	bool operator()(const BnB_node *a,const BnB_node *b) const
	{
		if ( a->bound<b->bound )return true;
		else if ( a->bound==b->bound ) return a->value<b->value;
		return false;
	}
};
//===================================
//upperbound bnb
template <class T>
class BnB_UP{
public:
	/*
	 * saves info for each element (cost,value,value/cost ratio)
	 * and a pointer for the respective element
	 * ordered by higher value/cost ratio
	 * */
	//typename BnB_pair<T>::typeT ordered_elements;
	vector< typename BnB_pair<T>::typeT > ordered_elements;

	double maxCost;///<the limit

	double minItemCost;///<the min cost found in the items list

	const unsigned long maxIterationsAllowed=10000;///<control variable. Limits the steps used by the algorithm to avoid really heavy computations

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
			if (it==elements.begin() || elem_data.cost<minItemCost) minItemCost = elem_data.cost;
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
			if (it==elements.begin() || elem_data.cost<minItemCost) minItemCost = elem_data.cost;
			elem_data.value_cost_ratio = elem_data.value/elem_data.cost;
			ordered_elements.push_back( new typename BnB_pair<T>::typeT(
					elem_data
					, (*it)  ) );
		}
		//sort
		sort(ordered_elements.begin(),ordered_elements.end(),compareElems);
		BNBdebugger("VERIFY ORDER",(void(*)(void*)) &check_order<T>,this);
	}

//================================================
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	double findUpperBound_1(BnB_node* node,int* lastItemInBoundIndex,double* latItemInBoundCostUsed)
	{
		int i = node->index;//current node (uncheked) item index
		double oldBound=node->bound;

		while (node->checked()) node=node->parent;

		DEBUG_CODE2(if (node==NULL) cout<<"debug02ALERT:NULL!!!!\n";)

		int prevLastIndex = ((BnB_node_notChecked*) node)->lastItemInBoundIndex;
		double prevLastCost = ((BnB_node_notChecked*) node)->lastItemInBoundCostUsed;

		DEBUG_CODE2(
		cout << "BnBdebug02A: prevLastIndex:" <<prevLastIndex <"\n";
		cout<< "__lastIndexCost:"<< ordered_elements[prevLastIndex].first.cost <<"\n";
		cout << "BnBdebug02B: oldBound:" <<oldBound<< "__value:"<< ordered_elements[prevLastIndex].first.value <<"__prevLastCost:"<<prevLastCost <<"\n";
		)

		double newBound = oldBound - prevLastCost*ordered_elements[prevLastIndex].first.value/ordered_elements[prevLastIndex].first.cost;
		DEBUG_CODE2(cout << "BnBdebug03: new bound init = "<< newBound <<"\n";)
		//return 1;
		double auxCost = maxCost-prevLastCost;

		if(i!=prevLastIndex) //remove if was not removed on last index
		{
			newBound -= ordered_elements[i+1].first.value;
			auxCost  -= ordered_elements[i+1].first.cost;
		}

		i=prevLastIndex;
		if(i==prevLastIndex) i++;//se for o mesmo q o retirado do not count it

		for(; i<ordered_elements.size();i++)
		{
			if(auxCost+ordered_elements[i].first.cost>maxCost)
			{
				if (std::fabs(maxCost-auxCost) < EPSILON) //consider that the limit has been reached
				{
					*lastItemInBoundIndex=i-1;
					*latItemInBoundCostUsed=ordered_elements[i-1].first.cost;
				}
				else //"add the item partially"
				{
					*latItemInBoundCostUsed=maxCost-auxCost;
				newBound+=ordered_elements[i].first.value*(*latItemInBoundCostUsed)/ordered_elements[i].first.cost;
				//auxcost=maxCost;
				*lastItemInBoundIndex=i;
				}
				break;
			}
			else //ainda tem espaço,"add normally"
			{
				newBound+=ordered_elements[i].first.value;
				auxCost+=ordered_elements[i].first.cost;
				if (std::fabs(auxCost-maxCost) < EPSILON)
				{
					*lastItemInBoundIndex=i;
					*latItemInBoundCostUsed=ordered_elements[i].first.cost;
					break;
				}
			}
		}
		DEBUG_CODE2(cout << "BnBdebug03: new bound return = "<< newBound <<"\n";)
		return newBound;
	}

	vector<T*> findSolution()
		{
		std::priority_queue<BnB_node, std::vector<BnB_node*>, compare_BnBnodePointers> nodesQ;
		vector<T*> solution;
		BnB_node* bestNode;//current best solution found (higher value)

		//calculate initial upperbound
		double auxcost=0;
		double upperbound=0;
		int lastIndexUsed=0;//2 be reused later when calculating bound
		double lastIndexCostUsed;//2 be reused later when calculating bound
		bool allfit=true;
		for(int i = 0; i<ordered_elements.size();i++)
		{
			if(auxcost+ordered_elements[i].first.cost>maxCost)
			{
				if (std::fabs(maxCost-auxcost) < EPSILON)
				{
					lastIndexUsed=i-1;
					lastIndexCostUsed=ordered_elements[i-1].first.cost;
				}
				else
				{
				lastIndexCostUsed=maxCost-auxcost;
				upperbound+=ordered_elements[i].first.value*lastIndexCostUsed/ordered_elements[i].first.cost;
				lastIndexUsed=i;
				allfit=false;
				}
				break;
			}
			else
			{
				upperbound+=ordered_elements[i].first.value;
				auxcost+=ordered_elements[i].first.cost;
				//residual size stuff must be ignored or there will be problems =/
				//not sure if best solution
				if ( std::fabs(auxcost-maxCost) < EPSILON)
				{
					lastIndexUsed=i;
					lastIndexCostUsed=ordered_elements[i].first.cost;
					break;
				}
			}
		}
		//if all items can be checked/selected/... return instead of doing any computation
		if (allfit)
		{
			for(int i = 0; i<ordered_elements.size() ;i++)
				solution.push_back(ordered_elements[i].second);
			return solution;
		}
		//===============================
		//COMPUTE STUFF TO FIND BEST SOLUTION
		BnB_node* startNode = new BnB_node_notChecked(0,0,upperbound,0,NULL,lastIndexUsed,lastIndexCostUsed);
		nodesQ.push( startNode );
		bestNode=nodesQ.top();

		DEBUG_CODE1(
				cout<<"debug04:"<< ((BnB_node_notChecked*)&startNode)->lastItemInBoundCostUsed<<"\n";
				   cout<<"debug05:"<< ((BnB_node_notChecked*)&startNode)->lastItemInBoundIndex<<"\n";
				   cout<<"debug06:"<< startNode->bound<<"\n";
				   cout<<"1st lic:"<< lastIndexCostUsed<<"\n";
				   )

		unsigned long i=0;//iterator p/ os items
		while(!nodesQ.empty())
		{
			BnB_node* node = nodesQ.top();

			DEBUG_CODE3(
			cout<<"debug06:"<< ((BnB_node_notChecked*)&node)->lastItemInBoundIndex<<"\n";
			)

			if (node->value>bestNode->value) bestNode=node;
			nodesQ.pop();
			/*
			 * if item is not checked then bound is reduced
			 * if item is checked keeps the same bound because items are ordered by ratio (i think)
			 * */
			//if the minCost always breaks the max there is no need to continue further the node
			if(minItemCost+node->cost<maxCost && node->index<ordered_elements.size()-1)
			{
				DEBUG_CODE3(cout<<"BnB_debug01__minCost+nodeCost:" << (double) (minItemCost+node->cost) <<"__maxCost:"<< maxCost <<"\n";)

				int currentIndex=node->index+1;
				double newCost = node->cost+ordered_elements[currentIndex].first.cost;
				if (newCost<=maxCost+EPSILON){
					BnB_node* checked=new BnB_node_checked(newCost,node->value+ordered_elements[currentIndex].first.value,node->bound,currentIndex,node);
					nodesQ.push(checked);
				}

				DEBUG_CODE2(cout<<"1st lic 2->"<<((BnB_node_notChecked*) startNode)->lastItemInBoundCostUsed <<"\n";)
				double newUpperBound = findUpperBound_1(node,&lastIndexUsed,&lastIndexCostUsed);//calculate new upperBound
				DEBUG_CODE2(cout<<"lic->"<<lastIndexCostUsed<<"\n";)
				if(bestNode->value<newUpperBound)
				{
					BnB_node* unchecked = new BnB_node_notChecked(node->cost,node->value,newUpperBound,currentIndex,node,lastIndexUsed,lastIndexCostUsed);
					nodesQ.push(unchecked);
				}
			}
			i++;
			if (i>maxIterationsAllowed)break;
		}

		//===============================
		//get answer set from the bestFound
		while(bestNode!=NULL)
		{
			if(bestNode->checked()) solution.push_back(ordered_elements[bestNode->index].second);
			bestNode=bestNode->parent;
		}

		return solution;
		}

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
