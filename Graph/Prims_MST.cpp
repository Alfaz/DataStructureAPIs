/*
A prototype implementation of Prims Minimum Spanning Tree algorithm, using adjacency list representation of graph, as presented in Graph_api.cpp.
compile: g++ Prims_MST.cpp
Author: Alfaz Ahmed
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Edge{
    public:
        int wt;
        int v;
        int w;
        Edge(int V, int W, int weight){
            this->wt = weight;
            this->v = V;
            this->w = W;
        }
        int compareTo(Edge& that){
            if(this->wt > that.wt){
                return 1;
            }else if(this->wt == that.wt){
                return 0;
            }else{
                return -1;
            }
        }
        int either(){
            return this->v;
        }
        int other(int V){
            if(V == this->v){
                return this->w;
            }else{
                return this->v;
            }
        }
    
};
class Graph{
    public:
        int vertices; //number of vertices
        int edges;    //number of edges
        vector<vector<Edge> > *adj;
    	Graph(int v){
    	    adj = new vector<vector<Edge> >(v);
    	}
    	void addEdge(Edge& e){
        	int v = e.either();
        	int w = e.other(v);
        	adj->at(v).push_back(e);
        	adj->at(w).push_back(e);
    	}
    	vector<Edge>::iterator adjacent_start(int v){
       		return adj->at(v).begin();
    	}
    	vector<Edge>::iterator adjacent_end(int v){
        	return adj->at(v).end();
    	}
};
void visit(Graph& G, int source);
struct compare  
{  
  bool operator()(const Edge& l, const Edge& r)  
  {  
      return l.wt > r.wt;  
  }  
};

vector<Edge> mst;
bool *visited;
priority_queue<Edge, vector<Edge>,compare> *pq;

int mst_cost(Graph& G, int source){
    //vector<Edge> mst;
    int ret =0;
    visited = new bool[G.vertices];
    pq = new priority_queue<Edge, vector<Edge>,compare>();
    visit(G,source);
    while(!pq->empty() && mst.size() < G.vertices-1){
        Edge e = pq->top();
        pq->pop();
        int v = e.either();
        int w = e.other(v);
        if(visited[v] && visited[w]){
            continue;
        }
        mst.push_back(e);
        if(!visited[v]){
            visit(G,v);
        }
        if(!visited[w]){
            visit(G, w);
        }
    }
    for(vector<Edge>::iterator it = mst.begin();it!=mst.end();it++){
        ret += it->wt;
    }
    return ret;
}

void visit(Graph& G, int source){
    visited[source] = true;
    for(vector<Edge>::iterator it = G.adjacent_start(source); it != G.adjacent_end(source);it++){
        if(!visited[it->other(source)]){
            pq->push(*it);
        }
    }
}

int main() {
    	int t=0,n,e,v,w,cost,source;
	cout << "Number of nodes: ";
	cin >> n;
	cout<<endl;
	cout << "Number of edges:";
	cin >> e;
	cout<<endl;
	Graph *G = new Graph(n);
	cout << "Enter the "<< e<<" edges as v w cost, v bein the start node, w end node and cost is edge weight"<<endl;
	while(--e){
		cin >> v;
		cin >> w;
		cin >> cost;
		G->addEdge(*(new Edge(v-1,w-1,cost)));
	}
    	cin >> source;
	cout << "Cost of MST = "<<mst_cost(*G,source)<<endl;
	delete G;
    return 0;
}





