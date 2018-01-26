#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class vertex{
public:
  int dist;
  int p;
};

void addEdge(vector<int> vec[],int from, int to){
	    vec[from].push_back(to);
			vec[to].push_back(from);
}
void BFS(vector<int> vec[],int source,int size){
 vector<vertex> vertex_array;
  vector<int> temp;
    for(int j=0;j<size;j++){
      vertex av;
      av.dist=200;
      av.p=-1;
      vertex_array.push_back(av);
    }
		int vert_size= vertex_array.size();
/*
  for(int i=0;i<vertex_array.size();i++){
    cout <<"vertex: " <<  i << endl;
      cout  << " dist: " <<vertex_array[i].dist << " ";
    cout << endl;
  }
  */
  queue<int> pq;
  vertex_array[source].dist=0;
  vertex_array[source].p=-1;
  pq.push(source);
  vector<bool> vertex_visited(vert_size,false);
  int vert= pq.front();
  while(!pq.empty()){
     vert= pq.front();
    for(int i=0;i<vec[vert].size();i++){
      //cout <<" vertex " << vec[vert][i] << endl;
      if(!vertex_visited[vec[vert][i]] && vertex_array[vec[vert][i]].dist==200){
        vertex_array[vec[vert][i]].dist=vertex_array[vert].dist+1;
				vertex_array[vec[vert][i]].p=vert;
        pq.push(vec[vert][i]);
        vertex_visited[vec[vert][i]]=true;
      }
    }
    vertex_visited[vert]=true;
      pq.pop();
  }
  for(int i=0;i<vertex_array.size();i++){
    cout <<"vertex: " <<  i << endl;
    cout  << " dist: " <<vertex_array[i].dist << " "
		<< " parent: " << vertex_array[i].p << " ";
    cout << endl;
  }

}
int main(int argc, const char * argv[])
{
		int size;
		int vertex;
		int edge;
		cin>>size;
		vector<int > graph[size];
		//cout << size << endl;
		for(int i=0;i<size;i++){
		cin>> vertex >> edge;
		//cout << vertex << "   " << edge << endl;
		addEdge(graph,vertex,edge);
	  }
	  BFS(graph,0,size);
/*
  cout << "----------------"  << endl;
    for(int i=0;i<size;i++){
			cout << "parent " << i << " ";
			for(int j=0;j<graph[i].size();j++){
				cout  << " edge " << graph[i][j] <<" ";
			}
			cout << endl;
		}
*/
     return 0;
}
