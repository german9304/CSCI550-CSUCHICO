#include <iostream>
#include <queue>
#include <vector>
using namespace std;


void addEdge(vector<int> vec[],int from, int to){
	    vec[from].push_back(to);
			vec[to].push_back(from);
}
void BFS(vector<int> vec[],int source){
	vector<vector<int> > dist;
	vector<vector<int> > parent;
	vector<int> temp;
	for(int i=0;i<20;i++){
		for(int j=0;j<vec[i].size();j++){
			temp.push_back(200);
		}
		dist.push_back(temp);
		temp.clear();
	}
 int source_dist=0;
 queue< vector<int> > pq;
 pq.push(vec[0]);

}
int main(int argc, const char * argv[])
{
		int size;
		int vertex;
		int edge;
		cin>>size;
		vector<int > graph[size];
		for(int i=0;i<size;i++){
		cin>> vertex >> edge;
		addEdge(graph,vertex,edge);
	  }
		BFS(graph,0);
    for(int i=0;i<20;i++){
			cout << "parent " << i << " ";
			for(int j=0;j<graph[i].size();j++){
				cout  << " edge " << graph[i][j] <<" ";
			}
			cout << endl;
		}

     return 0;
}
