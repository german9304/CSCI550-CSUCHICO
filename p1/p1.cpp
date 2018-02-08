#include<algorithm>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<list>
using namespace std;

	class edge{
	public:
		int vertex;
		int weight;
	};
void addEdge(vector<list<edge> > &adjA,int from,int to,int weight){
	edge aedge_from;
	aedge_from.vertex=to;
	aedge_from.weight=weight;
	adjA[from].push_back(aedge_from);
	edge aedge_to;
	aedge_to.vertex=from;
	aedge_to.weight=weight;
	adjA[to].push_back(aedge_to);

}
void collect_weights(vector<list<edge> > &adjA, vector<int> & weights){

}

int main(){

 //vector<int> weights(m, 0);
 int vertices,size,from,to,weight;
 cin >> vertices >> size;
  vector<list<edge> > adjA(vertices);
  for(int i=0;i<size;i++){
    cin>> from>> to >> weight;
		addEdge(adjA,from,to,weight);
	}
	/*
	cout <<" size " <<  adjA.size() << endl;
	for(int i=0;i<adjA.size();i++){
		cout << "-----------" << endl;
		cout << " vertex " << i << endl;
		 for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it){
			cout << " v: " << it->vertex<< " w: " << it->weight <<  " ";
	}
	cout << endl;
	cout << "-----------" << endl;
}
*/
 //collect_weights(adjA, weights);
	return 0;
}
