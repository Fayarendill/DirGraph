#include <iostream>
#include "dirGraph.hpp"
using namespace std;

int main() 
{
	int nV, v;
	int c;
	cout<<"input number of vertex:"<<endl;
	cin>>nV;
	dirGraph G(nV);
	G.read();
	cout<<"your graph:"<<endl;
	G.print();
	while (true)
	{
		cout<<"roots and MST for choosen vertex - 1, quit - 0"<<endl;
		cin>>c;
		if (!c)
		{
			break;	
		}
		else if (c==1)
		{
			cout<<"input vertex:"<<endl;
			cin>>v;
			Dijkstra gD(G, v);
			for(auto wx=0; wx<nV; wx++)
			{
				cout<<gD.wayDist(wx)<<": ";
				gD.putPath(wx);
			}
			cout<<"Adjacency lists for MST:"<<endl;
			gD.buildMST();
			gD.MST->print();
		}
		else
		{
			cout<<"try again"<<endl;
		}
	}
	return 0;
}

