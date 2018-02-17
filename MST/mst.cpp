#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

class edge{
public:
	int parent;
	int weight;
	int to;
	int from;
	int weight_to;
};

bool compare_edges(edge i,edge  j) { return (i.weight<j.weight); }

void addEdge(vector<list<edge> > & alist,int from, int to,int weight){
	edge aedge_from;
	aedge_from.weight=weight;
	aedge_from.to=to;
	aedge_from.from=from;
	aedge_from.weight_to=weight;
	aedge_from.parent=from;
	alist[from].push_back(aedge_from);
	edge aedge_to;
	aedge_to.weight=weight;
	aedge_from.to=from;
	aedge_to.from=to;
	aedge_to.parent=from;
	aedge_to.weight_to=-1;
	alist[to].push_back(aedge_to);
}
int findSet(){

}

void union_rank(){

}
void Make_Set(vector<int> & parent_array,vector<int> & rank){
 for(int i=0;i<parent_array.size();i++){
	 parent_array[i]=i;
 }
 for(int i=0;i<rank.size();i++){
	 rank[i]=0;
 }
}
vector<edge> sort_weights(vector<list<edge> > & alist){
	vector<edge> temp;
   	for(int i=0;i<alist.size();i++){
	 		for(auto iter=alist[i].begin();iter!=alist[i].end();iter++){
	 			if(iter->weight_to!=-1){
	 				//cout <<i << " " << iter->to << " " << iter->weight << endl;
	 				temp.push_back(*iter);
	 			}
	 		}
	 	}
		std::sort (temp.begin(), temp.end(), compare_edges);
		return temp;

}
void MST(vector<list<edge> > & alist,vector<int> & parent_array,vector<int> & rank){
     Make_Set(parent_array,rank);
		//sort weights
  vector<edge> av = sort_weights(alist);
	 for(int i=0;i<av.size();i++){
		// cout <<av[i].from << " " << av[i].to << " " <<  av[i].weight << endl;
	 }
	 /*
	 cout << "parent array" << endl;
	 for(int i=0;i<parent_array.size();i++){
		 //cout << "vertex: " << av[i].from << " parent: " << parent_array[av[i].from]<< endl;
	 }
	 */
}

int main(){
	int vertices,size,from,to,weight;
	cin>> vertices >> size;
	vector<edge> temp;
	vector<list<edge> > adjA(vertices);
	vector<int> parent_array(vertices);
	vector<int> rank(vertices);
	for(int i=0;i<size;i++){
		cin>> from>> to >> weight;
		addEdge(adjA,from,to,weight);
	}
	MST(adjA,parent_array,rank);
	//sort weights

  /*
	 std::sort (temp.begin(), temp.end(), compare_edges);
	 cout << "weights" << endl;
	 for(int i=0;i<temp.size();i++){
		 cout <<temp[i].from << " " << temp[i].to << " " <<  temp[i].weight << endl;
	 }
	 */
  /*
	cout << "parent_array " << parent_array.size() << endl;
	 for(int i=0;i<parent_array.size();i++){
		 cout << parent_array[i] << " ";
	 }
	 cout << endl;
	 cout << "rank_array " << rank.size() << endl;
	 for(int i=0;i<rank.size();i++){
		 cout << rank[i] << " ";
	 }
	 cout << endl;

	cout << "size: " << adjA.size() << endl;
	for(int i=0;i<adjA.size();i++){
		for(auto iter=adjA[i].begin();iter!=adjA[i].end();iter++){
			if(iter->weight_to!=-1){
				cout <<i << " " << iter->to << " " << iter->weight << endl;
			}
		}
	}
*/
	return 0;
}
