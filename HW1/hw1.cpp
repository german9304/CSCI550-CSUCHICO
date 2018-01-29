/*
 German Razo
 Homework 1
 CSCI550
*/
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

  /********
  @Brief
  This class represents the vertex from the graph
  it has a distance and a parent
  ********/
  class vertex{
  public:
    int dist;
    int p;
  };
   /*******
    @BRIEF
    This function adds edge to the graph
    *******/
  void addEdge(vector<int> vec[],int from, int to){
  vec[from].push_back(to);
  vec[to].push_back(from);
  }
  /*******
   @BRIEF
   This function implements Breath First Search function
   and it explores all the vertex from the graph, starting by the source
   *******/
  void BFS(vector<int> vec[],int source,int size,vector<vertex> & vert_arr){
    for(int j=0;j<size;j++){
      vertex av;
      av.dist=200;
      av.p=0;
      vert_arr.push_back(av);
    }
  int vert_size= vert_arr.size();
  queue<int> pq;
  vert_arr[source].dist=0;
  vert_arr[source].p=0;
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
/*************
@ Brief
This function returns the middle vertex that has the shortes distance from
the vertices, endpoints
***********/
int coreFacility(vector<int> graph[],vector<vertex> & vert_arr,vector<int> & vc,int size){
    int v_index=0;
    int max = vert_arr[0].dist;
    for(int i=0;i<vert_arr.size();i++){
      if(vert_arr[i].dist>max){
        max=vert_arr[i].dist;
        v_index=i;
      }
    }
      int center = max/2;
      for(int i=0;i<vert_arr.size();i++){
        if(vert_arr[i].dist==center){
          vc.push_back(i);
        }
      }
      int facility=vc[0];
      int s = vc.size();
      if(s>1){
        vert_arr.clear();
        BFS(graph,v_index,size,vert_arr);
        int min=vert_arr[vc[0]].dist;
        for(int i=0;i<vc.size();i++){
          if(vert_arr[vc[i]].dist<min){
            facility=vc[i];
          }
        }
      }
      return facility;
}
/*************
@ Brief
This function returns the maximum vertex from endpoints
***********/
int max_v(vector<vertex> & vc){
   int vertex_max=0;
   int max=vc[0].dist;
   for(int i=0;i<vc.size();i++){
         if(max<vc[i].dist){
           max=vc[i].dist;
           vertex_max=i;
         }
   }
   return vertex_max;

}
/*************
@Brief
This function recursively prints the path from the facility to all the
vertices 0-N
*************/
void print(vector<vertex> & vert_arr,int index,int vert){
        if(vert_arr[index].p==vert){
               return;
        }
        index = vert_arr[index].p;
        print(vert_arr,index,vert);
        cout << index<< " ";
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
   int min_endpoint=0;
   int vertex_max=5;
   for(int i=0;i<2;i++){
   vertex_array.clear();
   BFS(graph,vertex_max,size,vertex_array);
   vertex_max = max_v(vertex_array);
     if(vertex_max<=min_endpoint){
        min_endpoint=vertex_max;
     }
   }
  vertex_array.clear();
  BFS(graph,min_endpoint,size,vertex_array);
  int facility= coreFacility(graph,vertex_array,vc,size);
  vertex_array.clear();
  BFS(graph,facility,size,vertex_array);
  for(int i=0;i<vertex_array.size();i++){
  if(i!=facility){
  print(vertex_array,i,0);
  cout << i <<" "<< endl;
   }
  }
   return 0;
}
