#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
//#include <vector>
#include "City.h"
#include "bruteForce.h"
#include <math.h>
#include "Greedy.h"

void exercicio1();
void exercicio2();
void exercicio3();

using namespace std;

vector<City> cities;
vector<City> cities2visit;
vector< vector<double> > edges;
vector< vector<double> > edges2Visit;


#if (1) //graph viewer stuff
GraphViewer *gv;
void loadInterface()
{
	gv = new GraphViewer(865, 708, false);
	//Nota: para configurar uma imagem de fundo deve utilizar o seguinte comando:
	//tem ser colocado antes do comando gv->createWindow(600, 600);
	gv->setBackground("europe.jpg");

	gv->createWindow(865, 708);

	//atribuir cores
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("green");
}

void initGraphCities()
{
	for(int i = 0 ; i< cities.size();i++)
		{
		gv->addNode(i,cities[i].x,cities[i].y);
		//gv->setVertexLabel(i,cities[i].name);
		}
}

void updateSelectedCities(int cityIndex,bool first)
{
	gv->setVertexColor(cityIndex, "yellow");
	if (!first)
	{
	stringstream ss;
	ss<<"[ ";
	ss << cities[cityIndex].visitTime;
	ss<<" | ";
	ss << cities[cityIndex].preference;
	ss<<" ]";
	gv->setVertexLabel(cityIndex,ss.str());
	}
	else gv->setVertexLabel(cityIndex,"X");
	gv->rearrange();
}


#endif

#if(1) //interface utilities

int readPositiveInteger(int minValue,int maxValue)
{
	std::string info;
	int value=0;
	getline( cin, info);
	value = atoi(info.c_str());
	while((info[0]!='0'&&info.size()!=1&&value==0)||value<0
			||value<minValue||value>maxValue){
		cout<< "\nErro:Falhou leitura de valor inteiro. Input invalido."<<endl;
		cout<< "Volte a inserir valor entre " << minValue <<" e " << maxValue <<"\n";
	getline( cin, info);
	 value = atoi(info.c_str());
	}
	return value;
}

typedef bool (*loopMenu)(void);//serve para identificar funcoes que retornam bool e nao recebem parametros
void MenuLooper(loopMenu menu)
{
	bool loop=true;
	while (loop) {system("cls");loop=menu();}
}

bool citySelection()
{
	cout<<"___ ___ City Selection ___ ___"<<endl;
	cout<<"Notes:\nFirst city selected will be the starting point"<<endl;
	cout<<"Best solution will be guaranteed if number of selected cities is less than 10"<<endl;
	cout<<"Cities to visit:"<<endl;
	for(int i = 0; i<cities.size();i++)
		if (cities[i].index==-1) cout<<i<<":"<<cities[i].name<<endl;
	//cout<<edges[0][3];
	//cout<<edges[0][4];
	cout<<cities.size()<<"<=:to proceed to finding a solution to the current selected cities."<<endl;
	cout<<"selection>";

	//read user choice
	int answ = readPositiveInteger(0,9999);

	//leave selection menu
	if (answ>=cities.size())return false;

	//do not select the same city again
	if(cities[answ].index!=-1) return true;

	//add city
	if(!cities2visit.empty())
	{
		cout<<"Insert visit time for "<< cities[answ].name <<":";
		int visitTime = readPositiveInteger(1,9999);
		cities[answ].visitTime=visitTime;
		edges[answ][answ] = visitTime;
		cout<<"Insert preference(1-10) for "<< cities[answ].name <<":";
		int preference = readPositiveInteger(1,10);
		cities[answ].preference=preference;
	}
	cities[answ].index=answ;
	cities2visit.push_back(cities[answ]);

	updateSelectedCities(answ,cities2visit.size()==1);

	return true;
}

#endif


void create_Cities_and_Paths()
{
float TIMEPERPIXEL = 0.023333f;

	City a0("Lisbon", "...", 0, 0, 0);
	a0.x=40; a0.y=635;
	City a1("Barcelona", "...", 0, 0, 0);
	a1.x=305; a1.y=550;
	City a2("Madrid", "...", 0, 0, 0);
	a2.x=175; a2.y=585;
	City a3("Hamburg", "...", 0, 0, 0,483,142);
	City a4("Faro", "...", 0, 0, 0,74,680);
	City a5("Sevilla","...", 0, 0, 0,120,669);
	City a6("Zaragosa","...", 0, 0, 0,234,545);
	City a7("Bordeau","...", 0, 0, 0,242,443);
	City a8("Marseille","...", 0, 0, 0,377,493);
	City a9("Paris","...", 0, 0, 0,320,323);
	City a10("London","...", 0, 0, 0,252,216);
	City a11("Geneva","...", 0, 0, 0,425,383);
	City a12("Milano","...", 0, 0, 0,463,423);
	City a13("Rome","...", 0, 0, 0,527,530);
	City a14("Berlin","...", 0, 0, 0,559,178);

	cities.push_back(a0);
	cities.push_back(a1);
	cities.push_back(a2);
	cities.push_back(a3);
	cities.push_back(a4);
	cities.push_back(a5);
	cities.push_back(a6);
	cities.push_back(a7);
	cities.push_back(a8);
	cities.push_back(a9);
	cities.push_back(a10);
	cities.push_back(a11);
	cities.push_back(a12);
	cities.push_back(a13);
	cities.push_back(a14);

	for (int i = 0; i<cities.size();i++)
	{
		vector<double> newV;
		for (int j = 0; j<cities.size();j++)
		{
			if(i==j)newV.push_back(0);
			else newV.push_back(
					//missing sqrt to get distance, but shoud give similar results
					//note that would need a database or something to get real traveling distances
			round(
		sqrt((double) ((cities[i].x -cities[j].x)*(cities[i].x -cities[j].x) + (cities[i].y -cities[j].y)*(cities[i].y -cities[j].y))

				//give some extra value
				)*TIMEPERPIXEL*10)/10
					);
		}
		edges.push_back(newV);
	}
}

void create_2Use_edges()
{
	for(unsigned int i = 0; i<cities2visit.size() ;i++)
	{
		vector<double> edgesLine;

		for(unsigned int j = 0; j<cities2visit.size() ;j++)
			edgesLine.push_back(edges[cities2visit[i].index][cities2visit[j].index]);

		edges2Visit.push_back(edgesLine);
	}
}

vector<double> cities2VisitPreferences()
{
	vector<double> res;

	for(unsigned int i = 0; i<cities2visit.size();i++)
	res.push_back(cities2visit[i].preference);

	//cout<<"--"<<res[cities2visit.size()-1];

	return res;
}

double getEdgeCost(City *c1, City *c2, int i1, int i2, vector<vector<double> > *edges) {
    //could be more complicated, like searching a list for each vertex pair
    return (*edges)[i1][i2];
}

int main() {
	//=== initialize stuff
	create_Cities_and_Paths();

	loadInterface();
	initGraphCities();

	//=== select cities
	MenuLooper(citySelection);
	if(cities2visit.size()<3)
	{
		cout<<"\nNEED TO SELECT MORE THAN 2 CITIES TO VISIT! (press enter to end)"<<endl;
		getchar();
		return 0;
	}

	cout<<"Insert travel limit time (the press enter again to find solution):"<<endl;
	int limitTime = readPositiveInteger(1,99999);
	//for some reason need to press enter again here
	//cout<<"\n"<<limitTime;
	cout<<"Started calculating better path\n";
	create_2Use_edges();
	//=== find solution
	if(cities2visit.size()<10)
	{
		BruteForce<City, vector<vector<double> > > BF ((double)limitTime, cities2visit, 0, &edges2Visit, &City::getPreference, getEdgeCost);
		vector<City*> sol = BF.solve(true);

		if (sol.empty()) cout<<"No Solution was found."<<endl;
		else
		{
			cout<<"Optimal solution was found."<<endl;
			gv->setVertexColor(cities2visit[0].index,"green");

			stringstream ss;
			ss << edges[sol[sol.size()-1]->index][cities2visit[0].index];
			gv->addEdge(sol.size(),sol[sol.size()-1]->index,cities2visit[0].index,EdgeType::UNDIRECTED);
			gv->setEdgeLabel(sol.size(),ss.str());
			ss.str("");

			ss << edges[sol[0]->index][cities2visit[0].index];
			gv->addEdge(sol.size()+1,sol[0]->index,cities2visit[0].index,EdgeType::UNDIRECTED);
			gv->setEdgeLabel(sol.size()+1,ss.str());

			for(unsigned int i = 0; i<sol.size();i++)
			{
				gv->setVertexColor(sol[i]->index,"green");
				if(i>0)
					{
					ss.str("");//stringstream ss;
					ss << edges[sol[i-1]->index][sol[i]->index];
					gv->addEdge(i-1,sol[i-1]->index,sol[i]->index,EdgeType::UNDIRECTED);
					gv->setEdgeLabel(i-1,ss.str());
					}
			}
			gv->rearrange();
		}

		BF.freeHeap();
	}
	else {
		vector<unsigned int> sol;
		//!! !! !! these vars must be initialized with 0!!!
		double vrp_gain=0;
		double vrp_cost=0;
		vector<double> in=cities2VisitPreferences();

		GreedyApproxVRP(edges2Visit,in ,((double)limitTime),sol, vrp_gain, vrp_cost);
		if (sol.size()<=1) cout<<"No Solution was found."<<endl;
		else
		{
			cout<<"A solution was found."<<endl;
			cout<<"Preference sum equal to:"<<vrp_gain<<endl;
			cout<<"Total Cost (time that will be spent):"<<vrp_cost<< endl;
			for(unsigned int i = 0; i<sol.size();i++)
			{
				gv->setVertexColor(cities2visit[sol[i]].index ,"green");
				if(i>0)
					{
					stringstream ss;
					ss << edges[cities2visit[sol[i-1]].index][cities2visit[sol[i]].index];
					gv->addEdge(i-1,cities2visit[sol[i-1]].index,cities2visit[sol[i]].index,EdgeType::UNDIRECTED);
					gv->setEdgeLabel(i-1,ss.str());
					}
			}
			stringstream ss;
			ss << edges[cities2visit[sol[0]].index][cities2visit[sol.size()-1].index];
			gv->addEdge(sol.size(),cities2visit[sol[0]].index,cities2visit[sol[sol.size()-1]].index,EdgeType::UNDIRECTED);
			gv->setEdgeLabel(sol.size(),ss.str());
			gv->rearrange();
		}

	}

	cout<<"Press Enter to quit"<<endl;
	std::string info;
	getline( cin, info);
	delete gv;
	return 0;
}
