
/*A simple API for edge weighted undirected graphs. Implemented as adjacency list of edges.
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
