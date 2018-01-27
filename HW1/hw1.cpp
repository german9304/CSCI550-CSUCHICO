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
  queue<int> pq;
  vert_arr[source].dist=0;
  vert_arr[source].p=-1;
  pq.push(source);
  vector<bool> vertex_visited(vert_size,false);
  int vert= pq.front();
  while(!pq.empty()){
    vert= pq.front();
    for(int i=0;i<vec[vert].size();i++){
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
  vector<int> vc;
  for(int i=0;i<size;i++){
    cin>> v >> edge;
    addEdge(graph,v,edge);
  }
  int v_index=0;
  BFS(graph,0,size,vertex_array);
  int max = vertex_array[0].dist;
  for(int i=0;i<vertex_array.size();i++){
    if(vertex_array[i].dist>max){
      max=vertex_array[i].dist;
      v_index=i;
    }
  }
  int center = max/2;
  for(int i=0;i<vertex_array.size();i++){
    if(vertex_array[i].dist==center){
      vc.push_back(i);
    }
  }
  int facility=vc[0];
  int s = vc.size();
  if(s>1){
    vertex_array.clear();
    BFS(graph,v_index,size,vertex_array);
    int min=vertex_array[vc[0]].dist;
    for(int i=0;i<vc.size();i++){
      if(vertex_array[vc[i]].dist<min){
        facility=vc[i];
      }
    }
  }
  vertex_array.clear();
  BFS(graph,facility,size,vertex_array);
  stack<int> mystack;
  for(int index=0;index<vertex_array.size();index++){
    if(index!=facility){
      int i=index;
      mystack.push(i);
      while(i!=facility){
        i=vertex_array[i].p;
        mystack.push(i);
      }
      while (!mystack.empty()){
        cout <<mystack.top() << " ";
        mystack.pop();
      }
      cout << endl;
    }
  }
     return 0;
}
