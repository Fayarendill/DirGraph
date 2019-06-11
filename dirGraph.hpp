#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class dirGraph
{
private:
  int Vcnt;
  struct vertWay
  {
    int w;
    int cost;
    vertWay (int wx, int costx)
    {
      w = wx;
      cost = costx;
    } 
  };
  struct vertAdj
  {
    int v;
    vector<vertWay> adj;
  };
  vector<vertAdj> vert;	
public:
  dirGraph (int Vnum) : Vcnt(Vnum)
  {
    vert.resize(Vnum);
    for (auto i=0; i<Vcnt; i++)
      {
	vert[i].v=i;
      }
  }
  int Vnum() const
  {
    return Vcnt;
  }
  void addWay (int v, int w, int cost)
  {
    if (vert[v].adj.empty())
      {
	vert[v].adj.emplace_back(vertWay(w, cost));
      }
    else
      {
	for (auto it=vert[v].adj.begin(); it!=vert[v].adj.end(); it++)
	  {
	    if (it->w == w)
	      {
		if (it->cost > cost)
		  {
		    it->cost = cost;
		  }
		return;
	      }
	  }
	vert[v].adj.emplace_back(vertWay(w, cost));
      }
  }
		
  void delWay (int v, int w)
  {
    vert[v].adj[w].cost=-1;
    //vert[v].adj[w].w=vert[w];
  }
		
  bool isAdj (int v, int w) const
  {
    return (vert[v].adj[w].cost!=-1)? true : false;
  }
		
  void read(int Ecnt)
  {
    int v, w, cost;
    for (auto i=0; i<Ecnt; i++)
      {
	cin>>v>>w>>cost;
	addWay(v, w, cost);
      }
  }
		
  void read()
  {
    int Ecnt;
    std::ifstream ifs;
    ifs.open("input.txt", ios_base::out);
    ifs>>Ecnt;
    int v, w, cost;
    for (auto i=0; i<Ecnt; i++)
      {
	ifs>>v>>w>>cost;
	addWay(v, w, cost);
      }
    ifs.close();
  }
		
  void print()
  {
    for (auto vi=0; vi<Vcnt; vi++)
      {
	cout<<vi<<":";
	for (auto it=vert[vi].adj.begin(); it!=vert[vi].adj.end(); it++)
	  {
	    cout<<" "<<it->w<<"-"<<it->cost;
	  }
	cout<<endl;
      }
  }
  friend class Dijkstra;	
};

class Dijkstra
{
  const dirGraph &G;
  const int Source;
  bool *used;
  int *dist;
  int *prev;
public:
  dirGraph *MST;
  Dijkstra(dirGraph &G, int v) : G(G), Source(v)//, dist(G.Vnum(), -1), setQ(G.Vnum(), false)
  {
    prev = new int[G.Vnum()];
    dist = new int[G.Vnum()];
    used = new bool[G.Vnum()];
    MST = new dirGraph(G.Vnum());
    for (auto i=0; i<G.Vnum(); i++)
      {
	dist[i] = -1;
	used[i] = false;
	prev[i] = -1;
      }
    dist[v]=0;
    prev[v]=v;
  }
		
  void build (int src)
  {
    if (src!=-1)
      {
	used[src]=true;
	for (auto it=G.vert[src].adj.begin(); it!=G.vert[src].adj.end(); it++)
	  {
	    if (((dist[src] + it->cost) < dist[it->w]) || (dist[it->w]==-1))
	      {
		dist[it->w]=dist[src] + it->cost;
		prev[it->w]=src;
	      }
	  }
	build(minDist());
      }
  }
		
  int minDist ()
  {
    int res=0;
    for (auto i=0; i<G.Vnum(); i++)
      {
	if (((dist[res] > dist[i]) || used[res] || dist[res]==-1) && (!used[i]) && (dist[i]!=-1))
	  {
	    res = i;
	  }
      }
    return (used[res] || dist[res]==-1)? -1 : res;
  }
		
  int wayDist(int w)
  {
    build(Source);
    return dist[w];	
  }	
		
  void buildMST()
  {
    build(Source);
    for (auto i=0; i<G.Vnum(); ++i)
      {
	auto w = i;
	if (prev[w]!=-1)
	  {
	    while (w!=Source)
	      {
		MST->addWay(prev[w], w, dist[w] - dist[prev[w]]);
		w = prev[w];
	      }
	  }
      }
  }
		
  void putPath(int w)
  {
    build(Source);
    if (prev[w]==-1)
      {
	cout<<"NO WAY"<<endl;
      }
    else
      {
	while (w!=Source)
	  {
	    cout<<w<<"<-";
	    w = prev[w];
	  }
	cout<<Source<<endl;
      }
  }
};
