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

void addEdge(vector<list<edge> > & alist,int  from, int to,int weight){
	edge aedge_from;
	aedge_from.weight=weight;
	aedge_from.to=to;
	aedge_from.from=from;
	aedge_from.weight_to=weight;
	aedge_from.parent=from;
	alist[from].push_back(aedge_from);
	edge aedge_to;
	aedge_to.weight=weight;
	aedge_to.to=from;
	aedge_to.from=to;
	aedge_to.parent=from;
	aedge_to.weight_to=-1;
	alist[to].push_back(aedge_to);
}
int findSet(int x,vector<int> & parent_array){
    if(x!=parent_array[x]){
			parent_array[x] = findSet(parent_array[x],parent_array);
		}

		return parent_array[x];
}

void union_rank(int x, int y,vector<int> & parent_array,vector<int> & rank){
	if(rank[x]>rank[y]){
    parent_array[y]=x;
		 return;
	}else{
   parent_array[x]=y;
		return;
	}
	if(rank[x] == rank[y]){
		rank[y]=rank[y]+1;
		return;
	}
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
void MST(vector<list<edge> > & alist,vector<int> & parent_array,vector<int> & rank,vector<list<edge> > & adjT){
  Make_Set(parent_array,rank);
		//sort weights
  vector<edge> av = sort_weights(alist);
	for(int i=0;i<av.size();i++){
		if(av[i].weight_to!=-1){
		int rep_u= findSet(av[i].from,parent_array);
		int rep_v = findSet(av[i].to,parent_array);
		if(rep_u!=rep_v){
			//cout <<av[i].from << " " << av[i].to << " " <<  av[i].weight << endl;
      // cout << "i: " << i << endl;
			addEdge(adjT,av[i].from,av[i].to,av[i].weight);
			union_rank(rep_u,rep_v, parent_array,rank);
		}
	 }
  }

}

void BFS(vector<list<edge> > &adjB,int s,int size,vector<int> & vert_arr,vector<int> & p_array){
	int vert_size= vert_arr.size();
	int source = s;
	queue<int> pq;
	vert_arr[s]=0;
	pq.push(source);
	vector<bool> vertex_visited(vert_size,false);
	int vert= pq.front();
	while(!pq.empty()){
		vert= pq.front();
		auto it=adjB[vert].begin();

		for ( it=adjB[vert].begin(); it != adjB[vert].end(); ++it){
			if(!vertex_visited[it->to] && vert_arr[it->to]==-1){
      // cout << "to: " << it->to  << " w: " << it->weight << endl;
				vert_arr[it->to]=vert_arr[vert]+it->weight;
				p_array[it->to]=vert;
				vertex_visited[it->to]=true;
				pq.push(it->to);
			}
		}
		//exit(0);
		vertex_visited[vert]=true;
		pq.pop();
	}
}

void max_weight(vector<int> & p_array,vector<list<edge> > &adjB,int x,int & max){
	    if(p_array[x]!=x){
				  cout << "-------------------" << endl;
						//for(int i=0;i<adjB.size();i++){
							for( auto iter=adjB[p_array[x]].begin();iter!=adjB[p_array[x]].end();iter++){
								//if(iter->weight_to!=-1){
								//cout << "to: " << iter->to << endl;
								//if(iter->to==x){
									cout <<"x: " << x << " --- " <<  p_array[x]<< " " << iter->to << " " << iter->weight << endl;
									if(iter->weight>=max){
										max = iter->weight;
									}
								 //}
								}
							//}
						//}
						cout << "-------------------" << endl;
						max_weight(p_array,adjB,p_array[x],max);
			}
			//return;

}
int main(){
	int vertices,size,from,to,weight;
	cin>> vertices >> size;
	vector<edge> temp;
	vector<list<edge> > adjA(vertices);
	vector<list<edge> > adjT(vertices);
	vector<int> parent_array(vertices);
	vector<int> rank(vertices);
	for(int i=0;i<size;i++){
		cin>> from>> to >> weight;
		addEdge(adjA,from,to,weight);
	}
	MST(adjA,parent_array,rank,adjT);

//for(int i=0;i<6;i++){
	//cout << i << " " << parent_array[i] << endl;
//}

	//sort weights

  /*
	 std::sort (temp.begin(), temp.end(), compare_edges);
	 cout << "weights" << endl;
	 for(int i=0;i<temp.size();i++){
		 cout <<temp[i].from << " " << temp[i].to << " " <<  temp[i].weight << endl;
	 }
	 */

/*
	cout << "size: " << adjA.size() << endl;
	for(int i=0;i<adjA.size();i++){
		for(auto iter=adjA[i].begin();iter!=adjA[i].end();iter++){
			if(iter->weight_to!=-1){
				cout <<i << " " << iter->to << " " << iter->weight << endl;
			}
		}
	}
*/
/*
for(int i=0;i<parent_array.size();i++){
	cout << i << " " << parent_array[i] << endl;
}
*/

  vector<int> distance_array(adjT.size());
	vector<int> p_array(adjT.size());
	for(int i=0;i<distance_array.size();i++){
	  distance_array[i]=-1;
		p_array[i]=i;
	}
	cout << "Before weight: " << endl;
    for(int i=0;i<adjT.size();i++){
			for(auto iter=adjT[i].begin();iter!=adjT[i].end();iter++){
				if(iter->weight_to!=-1){
					//cout << " " << iter->to << " " << iter->weight << endl;
					cout <<i <<  " " << iter->to << " " << iter->weight << endl;
					//addEdge(adjTemp,i,iter->to,iter->weight);
					//max_w+=iter->weight;

				}
			}
		}

	//int i =2;
		//for(auto iter=adjT[i].begin();iter!=adjT[i].end();iter++){
			//if(iter->weight_to!=-1){
				//cout << " " << iter->to << " " << iter->weight << endl;
				//cout << " " << iter->to << " " << iter->weight << endl;
				//if(iter->to==3){

				//int n_w=2;
				//addEdge(adjT,2,3,2);
			   //}
				//max_w+=iter->weight;


		//}
		cout << "After weight: " << endl;
    for(int i=0;i<adjT.size();i++){
			for(auto iter=adjT[i].begin();iter!=adjT[i].end();iter++){
				if(iter->weight_to!=-1){
					//cout << " " << iter->to << " " << iter->weight << endl;
					cout <<i <<  " " << iter->to << " " << iter->weight << endl;
					//addEdge(adjTemp,i,iter->to,iter->weight);
					//max_w+=iter->weight;

				}
			}
		}

BFS(adjT,0,adjT.size(),distance_array,p_array);
cout << "distance_array: " << endl;
for(int i=0;i<distance_array.size();i++){
	cout << i << " " << distance_array[i] << endl;
}
cout << "parent_array: " << endl;
for(int i=0;i<p_array.size();i++){
	cout << i << " " << p_array[i] << endl;
}


cout << "-------------------" << endl;
	for(int i=0;i<adjT.size();i++){
		for(auto iter=adjT[i].begin();iter!=adjT[i].end();iter++){
			if(iter->weight_to!=-1){
				cout <<i << " " << iter->to << " " << iter->weight << endl;
			}
		}
	}
	cout << "-------------------" << endl;
int x=1;
int max=0;
cout << "max_weight: find weights" << endl;
max_weight(p_array,adjT,x,max);
cout << "max: " << max << endl;
/*
cout << "distance_array: " << endl;
for(int i=0;i<distance_array.size();i++){
	cout << i << " " << distance_array[i] << endl;
}
cout << "-------------------" << endl;
	for(int i=0;i<adjT.size();i++){
		for(auto iter=adjT[i].begin();iter!=adjT[i].end();iter++){
			//if(iter->weight_to!=-1){
				cout <<i << " " << iter->to << " " << iter->weight << endl;
			//}
		}
	}
	cout << "-------------------" << endl;
   cout << "new distance_array: " << endl;
	BFS(adjT,0,adjT.size(),distance_array);
	for(int i=0;i<distance_array.size();i++){
		cout << i << " " << distance_array[i] << endl;
	}
	//cout << "max_w: " << max_w << endl;
	*/
	return 0;
}
