/*
 * bruteForce.h
 *
 *  Created on: 22/04/2015
 *      Author: Bruno
 */

#ifndef BRUTEFORCE_H_
#define BRUTEFORCE_H_


//===============================================================================================================
// DEBUG
//===============================================================================================================

//#define DEBUG1//jagged edges creation
#ifdef DEBUG1
#define DEBUG_CODE1(A) A
#else
#define DEBUG_CODE1(A){}
#endif
//#define DEBUG2//solution creation
#ifdef DEBUG2
#define DEBUG_CODE2(A) A
#else
#define DEBUG_CODE2(A){}
#endif
//#define DEBUG3//nodes opening
#ifdef DEBUG3
#define DEBUG_CODE3(A) A
#else
#define DEBUG_CODE3(A){}
#endif
//#define DEBUG4//others
#ifdef DEBUG4
#define DEBUG_CODE4(A) A
#else
#define DEBUG_CODE4(A){}
#endif
//===============================================================================================================
// generic BRUTE FORCE (with some optimizations) IMPLEMENTATION
//===============================================================================================================
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

//did not use epsilon this time around, could be easy implemented later
//to avoid limit case problems, but i don't find it very relevant at the moment
//#define EPSILON 0.001f // 1/1000

//===================================
/**@brief Stores BruteForce node information
 * */
class BruteForce_node{
public:

	double cost;///<sum of the edges and vertices cost accumulated
	double value;///<sum of the edges and vertices values accumulated
	int index;///<index of the un/checked item.
	BruteForce_node* parent;///<the parent node. should be NULL if is first node.

	BruteForce_node(double cost,double value, int index,BruteForce_node* parent):cost(cost),value(value),index(index),parent(parent){}
};
/**@brief stores each element information
 * */
struct BF_elementDATA
{
	double cost;
	double value;
};
//===================================
/**
 * @brief creates alias for a type that
 * saves the element data and a pointer to the element
 * inside the BF class (not really a needed struct, only used to "simplify" notation)
 * */
template<typename T>
struct BF_pair {
	typedef pair<BF_elementDATA,T*> typeT;
};
//===================================

/**
 * to be used in a greedy approach
 * */
static double CompareElemsmaxValue;///<used by CompareNodes, avoid changing instance values
static double CompareElemsmaxCost;///<used by CompareNodes, avoid changing instance values
/**
 * @brief struct with comparison for nodes. Used in greedySolve().
 * could help speedup search. not sure though...
 * */
struct CompareNodes{
public:
	bool operator()(BruteForce_node *a,BruteForce_node *b)
	{
	//best criteria i imagined to speedup the process, not sure about it's efficiency
	//the one with min ratio is prioritized l>r
	return (CompareElemsmaxValue-a->value)/(CompareElemsmaxCost-a->cost)>
	(CompareElemsmaxValue-b->value)/(CompareElemsmaxCost-b->cost);
	}
};

/**@brief Branch n Bound implementation, done with max bounds (usually it's done in reverse)
 * */
template <class T, class R>
class BruteForce{

	vector<BruteForce_node*> usedNodes;///<stores nodes. if program is not going to end, memory can be freed if needed

public:

	/**
	 * saves info for each element (cost,value) and pointer to the original element
	 * (could be ordered by ratio (value/cost) but then would need to reajust edges indexes)
	 * */
	vector< typename BF_pair<T>::typeT > vertices;
	/**
	 * saves edges cost in a jagged array style to avoid duplicating data.
	 * indexed with 2 indexes, the outer vector must use the lesser of the indexes
	 * */
	std::vector<std::vector<double> > edges;

	double maxCost;///<problem limit, max cost allowed
	double MinCost; ///<min vertex + min edge, used to discard certain combinations preemptively
	double maxValue;///<sum of all the values

	int startIndex;///<index of the starting node in the original vector (given to constructor as argument)

	//bool optime;//set true if want to find the best value with lesser cost


	/**@brief gets the cost of the edge that connects elements at given indexes
	 * @return edge cost
	 * */
	double getEdgeCost(int vertIndex1, int vertIndex2)
	{
		if (vertIndex1>vertIndex2)
		{
			//swap
			 vertIndex1 ^= vertIndex2;
			 vertIndex2 ^= vertIndex1;
			 vertIndex1 ^= vertIndex2;
		}

		vertIndex2-=(vertIndex1+1);

		return edges[vertIndex1][vertIndex2];
	}


	/* getEdgeValue may not use all received it's params, the indexes of getEdgeValue represent the indexes of the cities in the given vertices vector param
	 * in this initializer suppose "self" cost is on the vertex and not on the edges (should make another later if enough time)
	 * */
	BruteForce(double maxCost,vector<T> &vertices,int startIndex,R *edges,double (T::*getValue)(void),double (T::*getCost)(void),double (*getEdgeValue)(T*,T*,int,int,R*) )
	{
		double minVertexCost;
		double minEdgeCost;
		//this->optime=optime;
		this->maxCost=maxCost;
		this->startIndex=startIndex;
		this->maxValue=0;

				//copy elements
				for(typename vector<T>::iterator it=vertices.begin(); it!=vertices.end();it++)
				{
					BF_elementDATA elem_data = {
							((*it).*getCost)(),  // cost
							((*it).*getValue)(),  // value
					};
					this->maxValue+=elem_data.value;
					if (elem_data.cost<minVertexCost||it==vertices.begin()) minVertexCost = elem_data.cost;

					this->vertices.push_back( pair<BF_elementDATA,T*>(
							elem_data
							, &(*it)  ) );
				}
				//sort
				//sort(this->vertices.begin(),this->vertices.end(),compareElems);

				for(int i = 0; i < vertices.size()-1 ; i++)
				{

					this->edges.push_back( std::vector<double>() );
					for(int j = i+1; j<vertices.size(); j++)
					{
						//no need for this,gonna keep it simple 4 now... int l,k //...get old index
						double costaux = getEdgeValue(&vertices[i],&vertices[j],i,j,edges);
						if (costaux<minEdgeCost||(i==0&&j==1)) minEdgeCost=costaux;
						this->edges[i].push_back( costaux );
					}
				}
				MinCost = minEdgeCost + minVertexCost;
				DEBUG_CODE1(
						cout<<"\"jagged\" edges:\n";
						for(int i = 0; i < this->vertices.size() ; i++)
							for(int j = 0; j<this->vertices.size(); j++)  if(i!=j)
								cout<< "i:"<< i << "j:"<< j << "__"<< this->getEdgeCost(i,j)<<"\n";
						cout<<"===========================================\n";
						)
	}

	/*
	 * in this initializer supposer vertez 'self cost' (visit tie in problem 8) in the edges parameter
	 * */
	BruteForce(double maxCost,vector<T> &vertices,int startIndex,R *edges,double (T::*getValue)(void),double (*getEdgeValue)(T*,T*,int,int,R*) )
	{
		double minVertexCost;
		double minEdgeCost;
		//this->optime=optime;
		this->maxCost=maxCost;
		this->startIndex=startIndex;
		this->maxValue=0;

				//copy elements
				for(int i = 0; i < vertices.size() ; i++)
				{
					BF_elementDATA elem_data = {
							getEdgeValue(&vertices[i],&vertices[i],i,i,edges),  // cost
							((vertices[i]).*getValue)(),  // value
					};
					this->maxValue+=elem_data.value;
					if (elem_data.cost<minVertexCost||i==0) minVertexCost = elem_data.cost;

					this->vertices.push_back( pair<BF_elementDATA,T*>(
							elem_data
							, &(vertices[i])  ) );
				}
				//sort
				//sort(this->vertices.begin(),this->vertices.end(),compareElems);

				for(int i = 0; i < vertices.size()-1 ; i++)
				{

					this->edges.push_back( std::vector<double>() );
					for(int j = i+1; j<vertices.size(); j++)
					{
						//no need for this,gonna keep it simple 4 now... int l,k //...get old index
						double costaux = getEdgeValue(&vertices[i],&vertices[j],i,j,edges);
						if (costaux<minEdgeCost||(i==0&&j==1)) minEdgeCost=costaux;
						this->edges[i].push_back( costaux );
					}
				}
				MinCost = minEdgeCost + minVertexCost;
				DEBUG_CODE1(
						cout<<"\"jagged\" edges:\n";
						for(int i = 0; i < this->vertices.size() ; i++)
							for(int j = 0; j<this->vertices.size(); j++)  if(i!=j)
								cout<< "i:"<< i << "j:"<< j << "__"<< this->getEdgeCost(i,j)<<"\n";
						cout<<"===========================================\n";
						)
	}

	/**
	 * @brief normal brute force approach
	 * will discard some nodes when it's possible to confirm they will not give better results.
	 * @param optime in case max Value is achieved within cost limits will return immediately if "optime" is set to false
	 * otherwise will try t find a solution of equal value but with less cost
	 * @return vector with the vertices in order of the best SolutionFound
	 * */
	vector<T*> solve(bool optime)
	{
		//if node is meant to be visited or not,
		//true means yes( does not count start)
		vector< bool > nodesLeftToVisit;
		for(int i = (int) vertices.size()-2; i>=0;i-- )
			nodesLeftToVisit.push_back(true);


		BruteForce_node* best;
		BruteForce_node* node;
		queue<BruteForce_node*> toProcess;
		node = new BruteForce_node(0,0,startIndex,NULL);
		best = node;
		usedNodes.push_back(node);
		toProcess.push(node);

		while(!toProcess.empty())
		{
			//get node to process
			node = toProcess.front();
			toProcess.pop();
			DEBUG_CODE4(cout<<"ndv"<<node->value<<"---"<<best->value<<"\n";
			cout<<"ndc"<<node->cost<<"---"<<best->cost<<"\n";)

			//return "home" solution is good?
			if(    (node->value > best->value //more valuable
					|| (node->value==best->value&&node->cost<best->cost) )
					&& node->cost+getEdgeCost(startIndex,node->index) < maxCost)
				best=node;

			if(!optime&&maxValue==best->value) break;

			DEBUG_CODE4(cout<<"."<<getEdgeCost(startIndex,node->index)<<"\n";)

			if(MinCost+node->cost>maxCost) continue; //speed up the process

			//find nodes left to visit in after current node
			for (vector<bool>::iterator it=nodesLeftToVisit.begin(); it!=nodesLeftToVisit.end();it++)
				(*it)=true;//resets list

			BruteForce_node* auxNode=node;
			while (auxNode->index!=startIndex)//mark visited
			{
				if (auxNode->index>startIndex) nodesLeftToVisit[auxNode->index-1]=false ;
				else  nodesLeftToVisit[auxNode->index]=false;
				auxNode=auxNode->parent;
			}

			//add nodes to be processed if they do not exceed limit and have any potential
			DEBUG_CODE3(cout<<"node(i_"<<node->index << ",v_" << node->value << ")" <<"\n";)
			for (int i = (int) nodesLeftToVisit.size()-1 ; i>=0  ; i--)
				if(nodesLeftToVisit[i])
			{
				int index = i >= startIndex ? i + 1 : i ;

				DEBUG_CODE3(cout<<"i:"<<index ;
				if(node->index!=startIndex)cout<<"..."<< node->index <<"..."<<node->parent->index ;
						cout<<"\n";)

				if (node->cost+getEdgeCost(node->index,index)+vertices[index].first.cost<maxCost)
				{
					BruteForce_node* open = new BruteForce_node(
				node->cost+getEdgeCost(node->index,index)+vertices[index].first.cost,
				node->value+vertices[index].first.value,index,node);
					usedNodes.push_back(open);
					toProcess.push(open);
				}
			}
		}

		//get answer set from the bestFound
		vector<T*> solution;
		while(best->index!=startIndex)
		{
			solution.push_back( vertices[best->index].second );
			DEBUG_CODE2(cout<<"sol index:"<<best->index<<"__"<< ((T*) vertices[best->index].second)->name <<"\n";)
			best=best->parent;
		}
		return solution;
	}

	/**
	 * the same as solve but
	 * runs nodes in order of less ratio between-> (maxValue-node->value)/(maxVost-node->cost)
	 * to try to speedup the process. Doesn't use optime, if we are to do a heavy/complete search
	 * then having priorities is actually worse because we sould be running all (or almost all) elements anyway with "heavier" code.
	 * */
	vector<T*> greedySolve()
	{
			//if node is meant to be visited or not,
			//true means yes( does not count start)
			vector< bool > nodesLeftToVisit;
			for(int i = (int) vertices.size()-2; i>=0;i-- )
				nodesLeftToVisit.push_back(true);


			BruteForce_node* best;
			BruteForce_node* node;

			//hmmm it seems i can't use a function object... maybe i'm missing something
			//will be using global variable instead
			CompareElemsmaxCost=maxCost;
			CompareElemsmaxValue=maxValue;
			std::priority_queue<BruteForce_node, std::vector<BruteForce_node*>,CompareNodes > toProcess;
			node = new BruteForce_node(0,0,startIndex,NULL);
			best = node;
			usedNodes.push_back(node);
			toProcess.push(node);

			while(!toProcess.empty())
			{
				//get node to process
				node = toProcess.top();
				toProcess.pop();
				DEBUG_CODE4(cout<<"ndv"<<node->value<<"---"<<best->value<<"\n";
				cout<<"ndc"<<node->cost<<"---"<<best->cost<<"\n";)

				//return "home" solution is good?
				if(    (node->value > best->value //more valuable
						|| (node->value==best->value&&node->cost<best->cost) )
						&& node->cost+getEdgeCost(startIndex,node->index) < maxCost)
					best=node;

				if(maxValue==best->value) break;

				DEBUG_CODE4(cout<<"."<<getEdgeCost(startIndex,node->index)<<"\n";)

				if(MinCost+node->cost>maxCost) continue; //speed up the process

				//find nodes left to visit in after current node
				for (vector<bool>::iterator it=nodesLeftToVisit.begin(); it!=nodesLeftToVisit.end();it++)
					(*it)=true;//resets list

				BruteForce_node* auxNode=node;
				while (auxNode->index!=startIndex)//mark visited
				{
					if (auxNode->index>startIndex) nodesLeftToVisit[auxNode->index-1]=false ;
					else  nodesLeftToVisit[auxNode->index]=false;
					auxNode=auxNode->parent;
				}

				//add nodes to be processed if they do not exceed limit and have any potential
				DEBUG_CODE3(cout<<"node(i_"<<node->index << ",v_" << node->value << ")" <<"\n";)
				for (int i = (int) nodesLeftToVisit.size()-1 ; i>=0  ; i--)
					if(nodesLeftToVisit[i])
				{
					int index = i >= startIndex ? i + 1 : i ;

					DEBUG_CODE3(cout<<"i:"<<index ;
					if(node->index!=startIndex)cout<<"..."<< node->index <<"..."<<node->parent->index ;
							cout<<"\n";)

					if (node->cost+getEdgeCost(node->index,index)+vertices[index].first.cost<maxCost)
					{
						BruteForce_node* open = new BruteForce_node(
					node->cost+getEdgeCost(node->index,index)+vertices[index].first.cost,
					node->value+vertices[index].first.value,index,node);
						usedNodes.push_back(open);
						toProcess.push(open);
					}
				}
			}

			//get answer set from the bestFound
			vector<T*> solution;
			while(best->index!=startIndex)
			{
				solution.push_back( vertices[best->index].second );
				DEBUG_CODE2(cout<<"sol index:"<<best->index<<"__"<< ((T*) vertices[best->index].second)->name <<"\n";)
				best=best->parent;
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


#endif /* BRUTEFORCE_H_ */
