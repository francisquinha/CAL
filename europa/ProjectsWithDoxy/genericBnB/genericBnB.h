/*
 * genericBnB.h
 *
 *  Created on: 06/04/2015
 *      Author: Bruno
 */

#ifndef GENERICBNB_H_
#define GENERICBNB_H_

//===============================================================================================================
// BRANCH&BOUND DE/ACTIVATE DEBUG
//===============================================================================================================
//outside solution checks
//#define DEBUG1
#ifdef DEBUG1
#define DEBUG_CODE1(A) A
#else
#define DEBUG_CODE1(A){}
#endif
//findUpperBound checks
//#define DEBUG2
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
//check node branching
//#define DEBUG4
#ifdef DEBUG4
#define DEBUG_CODE4(A) A
#else
#define DEBUG_CODE4(A){}
#endif
//#defin
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
/**
 * @brief Saves an element's data needed to compute the BnB solution
 * */
struct BnB_elementDATA
{
	double cost;///<element evaluated cost
	double value;///<element evaluated value
	double value_cost_ratio;///<ratio = element value / element cost
};
//===================================
/**
 * @brief creates alias for a type that
 * saves the element data and a pointer to the element
 * inside the BnB class (not really a needed struct, only used to "simplify" notation)
 * */
template<typename T>
struct BnB_pair {
	typedef pair<BnB_elementDATA,T*> typeT;
};
//===================================
/**@brief Stores Branch and Bound node information
 * */
class BnB_node{
public:
	double cost;	///<sum of all the checked items (indexes in parentNodes) cost plus cost of element at index <index> if the node is checked
	double value;	///<same as cost but done with the values of the elements
	double bound;	///<the max/min bound calculated for the current node (the current implementation uses max bounds)

	int index;///<index of the un/checked item.
	BnB_node* parent;///<the parent node. should be NULL if is first node.

	BnB_node(double cost,double value, double bound, int index,BnB_node* parent):cost(cost),value(value),bound(bound),index(index),parent(parent){}

	/**@brief Checks if a node is checked or unchecked
	 * @return true if checked, false otherwise
	 * */
	virtual bool checked() = 0;

	/*friend bool operator<(const BnB_node &a,const BnB_node &b)
	{
		return a.bound<b.bound;
	}*/
};

/**@brief Subclass that indicates that the index of the node as been unchecked
 * */
class BnB_node_checked:public BnB_node
{
public:
	bool checked(){return true;}
	BnB_node_checked(double cost,double value, double bound, int index,BnB_node* parent):BnB_node(cost,value,bound,index,parent){}
};

/**@brief Subclass that indicates that the index of the node as been checked
 * Saves values related to previous calculated bound to speed up the calculation of a new bound
 * */
class BnB_node_notChecked:public BnB_node
{
public:
	int lastItemInBoundIndex;		///<index of the last item used to calculate the previous bound
	double lastItemInBoundCostUsed; ///<the part of the cost used by the element at index <index> in previous bound calculation (might be less than the actual element cost)
	bool checked(){return false;}
	BnB_node_notChecked(double cost,double value, double bound, int index,BnB_node* parent,int liibIndex,double liibCostUsed):
		BnB_node(cost,value,bound,index,parent),lastItemInBoundIndex(liibIndex),lastItemInBoundCostUsed(liibCostUsed){}
};
//- - - - - - - - - - - - - - - - - -
/**@brief Defines comparison for node pointers, to be used in queue ordering
 * */
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
/**@brief Branch n Bound implementation, done with max bounds (usually it's done in reverse)
 * */
template <class T>
class BnB_UP{
public:

	vector<BnB_node*> usedNodes;

	/**
	 * saves info for each element (cost,value,value/cost ratio)
	 * and a pointer for the respective element
	 * ordered by higher value/cost ratio
	 * */
	vector< typename BnB_pair<T>::typeT > ordered_elements;

	double maxCost;///<the limit

	double minItemCost;///<the min cost found in the items list

	const unsigned long maxIterationsAllowed=10000;///<control variable. Limits the steps used by the algorithm to avoid really heavy computations

public:

	/**
	 * @brief compare ratio of the elements. to be used in priority_queue
	 * */
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
	}

	//================================================
	/**
	 * @brief Find new upper bound. Called only when uncheking.
	 * @param node node previous to the onde being unchecked
	 * @param lastItemInBoundIndex last item's, used in bound calculation, index, to be given to the new node afterwards
	 * @param latItemInBoundCostUsed last item's, used in bound calculation, used cost found in calculation, to be given to the new node afterwards
	 * @return new upperbound calculated
	 * */
	double findUpperBound_1(BnB_node* node,int* lastItemInBoundIndex,double* latItemInBoundCostUsed)
	{
		int i = node->index+1;//current node (uncheked) item index
		double oldBound=node->bound;

		while (node->checked()) node=node->parent;

		DEBUG_CODE2(if (node==NULL) cout<<"debug02ALERT:NULL!!!!\n";)

		//last element used to calcuate bound index and cost used
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
			newBound -= ordered_elements[i].first.value;
			auxCost  -= ordered_elements[i].first.cost;
			i=prevLastIndex;
		}
		else i++;//(i==prevLastIndex)  se for o mesmo q o retirado do not count it

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

	/**@brief What do you expect? Finds a solution if there is one.
	 * @return list of pointers to the elements of the found solution. If no solution is found, will be returned an empty vector.
	 * */
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
		BnB_node* startNode = new BnB_node_notChecked(0,0,upperbound,-1,NULL,lastIndexUsed,lastIndexCostUsed);
		usedNodes.push_back(startNode);
		nodesQ.push( startNode );
		bestNode=nodesQ.top();

		DEBUG_CODE1(
				cout<<"debug04:"<< ((BnB_node_notChecked*)startNode)->lastItemInBoundCostUsed<<"\n";
		cout<<"debug05:"<< ((BnB_node_notChecked*)startNode)->lastItemInBoundIndex<<"\n";
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

			if(minItemCost+node->cost<maxCost //if the minCost always breaks the max there is no need to continue further the node
					&&(node->bound>bestNode->value||node->index==-1)//if bound leq than best value found so far no need to continue futher either
					&& node->index< (int) ordered_elements.size()-1)//no more elements un/check
			{
				DEBUG_CODE3(cout<<"BnB_debug01__minCost+nodeCost:" << (double) (minItemCost+node->cost) <<"__maxCost:"<< maxCost <<"\n";)

								int currentIndex=node->index+1;
				double newCost = node->cost+ordered_elements[currentIndex].first.cost;
				if (newCost<=maxCost+EPSILON){
					BnB_node* checked=new BnB_node_checked(newCost,node->value+ordered_elements[currentIndex].first.value,node->bound,currentIndex,node);
					nodesQ.push(checked);
					usedNodes.push_back(checked);
					DEBUG_CODE4(cout<<"(checked," << currentIndex <<")<-("
							<< (node!=NULL?node->index:-1)	<< "," << (node->checked()?"y":"n") << ")"
							<< "___vc_"<< checked->value <<"_" << checked->cost << "\n";)
				}

				DEBUG_CODE2(cout<<"1st lic 2->"<<((BnB_node_notChecked*) startNode)->lastItemInBoundCostUsed <<"\n";)

				double newUpperBound = findUpperBound_1(node,&lastIndexUsed,&lastIndexCostUsed);//calculate new upperBound

				DEBUG_CODE2(cout<<"lic->"<<lastIndexCostUsed<<"\n";)

				if(bestNode->value<newUpperBound)
				{
					BnB_node* unchecked = new BnB_node_notChecked(node->cost,node->value,newUpperBound,currentIndex,node,lastIndexUsed,lastIndexCostUsed);
					nodesQ.push(unchecked);
					usedNodes.push_back(unchecked);
					DEBUG_CODE4(cout<<"(unchecked," << currentIndex <<")<-("
							<< (node!=NULL?node->index:-1)	<< "," << (node->checked()?"y":"n") << ")"
							<< "___vc_"<< unchecked->value << "_"<<unchecked->cost <<"\n";)
				}
			}
			i++;
			if (i>maxIterationsAllowed)break;
		}

		//===============================
		//get answer set from the bestFound
		while(bestNode->index!=-1)
		{
			if(bestNode->checked()) solution.push_back(ordered_elements[bestNode->index].second);
			bestNode=bestNode->parent;
		}

		return solution;
						}

	/** @brief clear heap used to find solution.
	 *  do it only after interpreting the solution
	 * */
	void freeHeap()
	{
		for (int i = usedNodes.size()-1; i>=0;i--)
		{
			delete(usedNodes[i]);
		}
		usedNodes.clear();
	}

};


#endif /* GENERICBNB_H_ */
