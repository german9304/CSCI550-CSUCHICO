#include <iostream>
#include <queue>
#include <vector>
#include <stack>
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
void BFS(vector<int> vec[],int source,int size,vector<vertex> & vert_arr){
    for(int j=0;j<size;j++){
      vertex av;
      av.dist=200;
      av.p=-1;
      vert_arr.push_back(av);
    }
		int vert_size= vert_arr.size();
/*
  for(int i=0;i<vertex_array.size();i++){
    cout <<"vertex: " <<  i << endl;
      cout  << " dist: " <<vertex_array[i].dist << " ";
    cout << endl;
  }
  */
  queue<int> pq;
  vert_arr[source].dist=0;
  vert_arr[source].p=-1;
  pq.push(source);
  vector<bool> vertex_visited(vert_size,false);
  int vert= pq.front();
  while(!pq.empty()){
     vert= pq.front();
    for(int i=0;i<vec[vert].size();i++){
      //cout <<" vertex " << vec[vert][i] << endl;
      if(!vertex_visited[vec[vert][i]] && vert_arr[vec[vert][i]].dist==200){
        vert_arr[vec[vert][i]].dist=vert_arr[vert].dist+1;
				vert_arr[vec[vert][i]].p=vert;
        pq.push(vec[vert][i]);
        vertex_visited[vec[vert][i]]=true;
      }
    }
    vertex_visited[vert]=true;
      pq.pop();
  }
}

int main(int argc, const char * argv[])
{
		int size;
		int v;
		int edge;
		cin>>size;
		vector<vertex> vertex_array;
		vector<int > graph[size];
		//cout << size << endl;
		for(int i=0;i<size;i++){
		cin>> v >> edge;
		//cout << vertex << "   " << edge << endl;
		addEdge(graph,v,edge);
	  }
		int node=0;
    int max=0;
		int ver=0;
	  for(int index=0;index<2;index++){
     BFS(graph,node,size,vertex_array);
		 for(int i=0;i<vertex_array.size();i++){
      if(vertex_array[i].dist>max){
				max=vertex_array[i].dist;
				ver=i;
			  }
		  }
   cout << " v " << ver << " max  distance " << max << endl;
   cout << "----------" << endl;
				for(int i=0;i<vertex_array.size();i++){
					cout <<"vertex: " <<  i << endl;
					cout  << " dist: " <<vertex_array[i].dist << " "
					<< " parent: " << vertex_array[i].p << " ";
					cout << endl;
				}
		cout << "----------" << endl;

			node=ver;
			if(index<1){
		  vertex_array.clear();
		   }
	  }
		cout << " node " << node << endl;
/*
			for(int i=0;i<vertex_array.size();i++){
				cout <<"vertex: " <<  i << endl;
				cout  << " dist: " <<vertex_array[i].dist << " "
				<< " parent: " << vertex_array[i].p << " ";
				cout << endl;
			}
*/
		/*
    stack<int> mystack;
		for(int index=0;index<vertex_array.size();index++){
			if(index!=58){
			int i=index;
			mystack.push(i);
			while(i!=58){
				//cout << i << " ";
				i=vertex_array[i].p;
				if(i==58){
					//cout <<i<< " ";
				}
				mystack.push(i);
			}
			 while (!mystack.empty()){
				  cout <<mystack.top() << " ";
          mystack.pop();
			 }
			  cout << endl;
		  }
		}
  */
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
