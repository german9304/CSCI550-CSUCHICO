#include <iostream>
#include <vector>
#include<list>
#include <queue>
#include<algorithm>
using namespace std;
class edge{
public:
	int from;
	int to;
	int weight;
	int cost=0;
	int k;
	int v_from;
	int v_to;
};
void addEdge(vector<list<edge> > & alist , int from,int to,int w){
edge vertex_from;
vertex_from.from=from;
vertex_from.to=to;
vertex_from.weight=w;
alist[from].push_back(vertex_from);
edge vertex_to;
vertex_to.from=to;
vertex_to.to=from;
vertex_to.weight=w;
alist[to].push_back(vertex_to);
}
void addCostEdge(vector<list<edge> > & alist , int from,int to,int w,int cost,int k){
	edge vertex_cost;
	vertex_cost.from=from;
	vertex_cost.to=to;
	vertex_cost.weight=w;
	vertex_cost.cost=cost;
	vertex_cost.k=k;
	alist[0].push_back(vertex_cost);
}
void addEdgeC(vector<list<edge> > & alist , int from, int to, int v_from,int v_to,int w,int cost){
	edge vertex_from;
	vertex_from.from=from;
	vertex_from.to=to;
	vertex_from.v_from=v_from;
	vertex_from.v_to=v_to;
	vertex_from.weight=w;
	vertex_from.cost=cost;
	alist[from].push_back(vertex_from);
	edge vertex_to;
	vertex_to.from=to;
	vertex_to.to=from;
	vertex_to.v_from=v_to;
	vertex_to.v_to=v_from;
	vertex_to.weight=w;
	vertex_to.cost=cost;
	alist[to].push_back(vertex_to);
}
bool myfunction (int i,int j) { return (i>j); }
bool compare_edges(edge i,edge  j) { return (i.weight>j.weight); }

int BFS(vector<list<edge> > & alist,int source,vector<int> & parent_array,
	vector<int> & distance_array){
		int current_sum=0;
		int vert_size= parent_array.size();
		queue<int> pq;
		distance_array[source]=0;
		pq.push(source);
		vector<bool> vertex_visited(vert_size,false);
		int vert= pq.front();
		while(!pq.empty()){
			vert= pq.front();
			for(auto it=alist[vert].begin();it!=alist[vert].end();it++){
				if(!vertex_visited[it->to] && distance_array[it->to]==-1){
					current_sum+=it->weight;
					distance_array[it->to]=distance_array[vert]+1;
					parent_array[it->to]=vert;
					pq.push(it->to);
					vertex_visited[it->to]=true;
				}
			}
			vertex_visited[vert]=true;
			pq.pop();
		}
		return current_sum;
}


void backtrack_parentarray(vector<list<edge> > & alist,int index,vector<int> &parent_array,
vector<bool> & vertex_visited,int & max_w){
   if(index==parent_array[index]){
       return;
	 }
	 for(auto iter=alist[index].begin();iter!=alist[index].end();iter++){
        if(iter->weight>max_w){
         max_w=iter->weight;
				}
		 }
		 backtrack_parentarray(alist,index-1,parent_array,vertex_visited,max_w);
}
void init(vector<int> & distance_array,int size){
	for(int i=0;i<size;i++){
		distance_array[i]=-1;
	}
}
int connectd(vector<list<edge> > & adjA,vector<int> & cc){
	unsigned int size = adjA.size();
	int total_cc=1;
	vector<int> distance_array(size);
	vector<int> parent_array(size);
	int source=0;
	int cc_count=0;
	std::vector<int> v;
	unsigned int i=0;
	while(i!=size){
		init(distance_array,size);
		BFS(adjA,source,parent_array,distance_array);
		for(unsigned int j=0;j<distance_array.size();j++){
			if(distance_array[j]!=-1){
				if(cc[j]==-1){
					cc[j]=cc_count;
				}
			}
		}
		for( i=source;i<size;i++){
			if(cc[i]==-1){
				source=i;
				cc_count++;
				total_cc++;
				break;
			}
		}
	}
	if(total_cc==0){
		total_cc++;
	}
	distance_array.clear();
	parent_array.clear();
	return total_cc;
}

int cost_networks_red_nova(vector<list<edge> > & new_list,vector<list<edge> > &
	red_nova_list,vector<list<edge> > &star_trace_list, vector<edge> weights,vector<list<edge> > paths_star_red){
		for(unsigned int index=0;index<weights.size();index++){
			for(unsigned int i=0;i<red_nova_list.size();i++){
				int a =i;
				for(auto iter=red_nova_list[i].begin();iter!=red_nova_list[i].end();iter++){
					unsigned int to = iter->to;
					if(i< to){
						if(a!= weights[index].from || iter->to!= weights[index].to || iter->weight!=weights[index].weight){
							addEdge(new_list,i,iter->to,iter->weight);
						}
					}
				}
			}
			vector<int> cc_1(new_list.size(),-1);
			int res = connectd(new_list,cc_1);
			vector<int> cc_2(star_trace_list.size(),res);
			vector<list<edge> > adjC(res+1);
			for(unsigned int i=0;i<paths_star_red.size();i++){
				for(auto iter=paths_star_red[i].begin();iter!=paths_star_red[i].end();iter++){
					addEdgeC(adjC,cc_1[iter->from],cc_2[iter->to],iter->from,iter->to,iter->weight,iter->cost);
				}
			}
			vector<int> parent_array(adjC.size());
			vector<int> distance_array(adjC.size(),-1);
			BFS(adjC,0,parent_array,distance_array);
			std::vector<int>::iterator it;
			it = find (distance_array.begin(), distance_array.end(), -1);
			if (it == distance_array.end()){
				weights[index].k=1;
				return index;
			}
			adjC.clear();
			cc_1.clear();
			cc_2.clear();
			parent_array.clear();
			distance_array.clear();
			new_list.clear();
			new_list.resize(red_nova_list.size());
		}
	return 0;
}
int cost_networks_star_trace(vector<list<edge> > & new_list,vector<list<edge> > &
	star_trace,vector<list<edge> > &red_nova_list, vector<edge> weights,vector<list<edge> > paths_star_red){
		for(unsigned int index=0;index<weights.size();index++){
			for(unsigned int i=0;i<star_trace.size();i++){
				int a = i;
				for(auto iter=star_trace[i].begin();iter!=star_trace[i].end();iter++){
					unsigned int to = iter->to;
					if(i< to){
						if(a!= weights[index].from || iter->to!= weights[index].to || iter->weight!=weights[index].weight){
							addEdge(new_list,i,iter->to,iter->weight);
						}
					}
				}
			}
			vector<int> cc_1(new_list.size(),-1);
			int res = connectd(new_list,cc_1);
			vector<int> cc_2(red_nova_list.size(),res);
			vector<list<edge> > adjC(res+1);
			for(unsigned int i=0;i<paths_star_red.size();i++){
				for(auto iter=paths_star_red[i].begin();iter!=paths_star_red[i].end();iter++){
					addEdgeC(adjC,cc_2[iter->from],cc_1[iter->to],iter->from,iter->to,iter->weight,iter->cost);
				}
			}
			vector<int> parent_array(adjC.size());
			vector<int> distance_array(adjC.size(),-1);
			BFS(adjC,0,parent_array,distance_array);
			std::vector<int>::iterator it;
			it = find (distance_array.begin(), distance_array.end(), -1);
			if (it == distance_array.end()){
				weights[index].k=2;
				return index;
			}
			adjC.clear();
			cc_1.clear();
			cc_2.clear();
			parent_array.clear();
			distance_array.clear();
			new_list.clear();
			new_list.resize(star_trace.size());
 }
		return 0;
}
void sort_weights(vector<list<edge> >& red_nova_list,vector<list<edge>> &
	star_trace_list,vector<edge> & red_nova,vector<edge> & star_trace){
	for(unsigned int i=0;i<red_nova_list.size();i++){
		for(auto iter=red_nova_list[i].begin();iter!=red_nova_list[i].end();iter++){
			unsigned int to = iter->to;
			  if(i<to){
        red_nova.push_back(*iter);
			}
		}
	}
	for(unsigned int i=0;i<star_trace_list.size();i++){
		for(auto iter=star_trace_list[i].begin();iter!=star_trace_list[i].end();iter++){
				unsigned int to = iter->to;
				  if(i<to){
	        star_trace.push_back(*iter);
				}
		}
	}
	std::sort (red_nova.begin(), red_nova.end(), compare_edges);
  std::sort (star_trace.begin(), star_trace.end(), compare_edges);
}

int total_star_red_maintain(int star_index,int red_index,int & k,vector<edge> & red_nova_weights,
	vector<edge> & star_trace_weights,int total_maintain,vector<list<edge> > & paths_star_red){
   int selected_Index=red_index;
	  k = red_nova_weights[red_index].k;
	 int w_1 = red_nova_weights[red_index].weight;
	 int w_2= star_trace_weights[star_index].weight;
	 if(w_2>w_1){
		 k=star_trace_weights[star_index].k;
			 selected_Index= star_index;
	 }
	 int total_star_red =0;
	 int total_w=0;
	 int total_c=0;
	 int new_maintain = 0;
	 if(k==1){
		 new_maintain = total_maintain-red_nova_weights[selected_Index].weight*10;
	 }else{
		 new_maintain = total_maintain-star_trace_weights[selected_Index].weight*10;
	 }
	 for(unsigned int i=0;i<paths_star_red.size();i++){
		 for(auto it=paths_star_red[i].begin();it!=paths_star_red[i].end();it++){
		 total_w+= (it->weight*10);
		 total_c+= (it->cost);
		 }
	 }
	 total_star_red=new_maintain + total_w + total_c;
	 return total_star_red;
}
void print_networks(vector<edge> temp,int k,int red_index,int star_index,
	vector<edge> red_nova_weights,vector<edge> star_trace_weights,vector<int> total_values){
	int min= total_values[0];
	int selected=0;
	for(unsigned int i=0;i<total_values.size();i++){
		if(total_values[i]<min){
			min=total_values[i];
			selected=i;
		}
	}
	if(selected==0){
		cout << temp[0].from << " " << temp[0].to << " " <<min <<endl;
	}else if(selected==1){
		cout << temp[1].from << " " << temp[1].to << " " <<min<<endl;
	}else{
		if(k==1){
			cout <<  red_nova_weights[red_index].from  << " " <<  red_nova_weights[red_index].to
			<< " " << red_nova_weights[red_index].k<<" " <<  min<<  endl;
		}else{
			cout <<  star_trace_weights[star_index].from  << " " <<  star_trace_weights[star_index].to
			<< " " << star_trace_weights[star_index].k<<" " <<  min <<  endl;
		}
	}
}
int main(){
	int red_nova_stations;
	int sum_red_nova_weights=0;
	cin>>red_nova_stations;
	vector< list<edge> > red_nova_list(red_nova_stations);
	int from,to,weight;
	for(int i=0;i<red_nova_stations-1;i++){
		cin>> from>> to >> weight;
		sum_red_nova_weights+=weight;
		addEdge(red_nova_list,from,to,weight);
	}
	int star_trace_stations;
	int sum_star_trace_weights=0;
	cin>>star_trace_stations;
	vector< list<edge> > star_trace_list(star_trace_stations);
	for(int i=0;i<star_trace_stations-1;i++){
		cin>> from>> to >> weight;
		sum_star_trace_weights+=weight;
		addEdge(star_trace_list,from,to,weight);
	}
	vector<list<edge> > paths_star_red(20);
	int from_path,to_path,cost_path,weight_path;
	for(int i=0;i<2;i++){
		cin>> from_path>> to_path >> weight_path>> cost_path;
		addCostEdge(paths_star_red,from_path,to_path,weight_path,cost_path,i+1);
	}
	vector<int>  red_nova_parent_array(red_nova_stations,0);
	vector<int>  red_nova_distance_array(red_nova_stations,-1);
	int current_sum_red_nova=0;
	current_sum_red_nova= BFS(red_nova_list,0,red_nova_parent_array,red_nova_distance_array);
	vector<bool> vertex_visited(red_nova_list.size(),false);
	int max_w_red_nova=0;
	backtrack_parentarray(red_nova_list,red_nova_stations-1,red_nova_parent_array,vertex_visited
	,max_w_red_nova);
	vector<int>  star_trace_parent_array(star_trace_stations,0);
	vector<int>  star_trace_distance_array(star_trace_stations,-1);
	int current_sum_star_trace=0;
	current_sum_star_trace = BFS(star_trace_list,0,star_trace_parent_array,star_trace_distance_array);
	int max_w_star_trace=0;
	vector<bool> vertex_visited_star(star_trace_list.size(),false);
	backtrack_parentarray(star_trace_list,star_trace_stations-1,star_trace_parent_array,vertex_visited_star,
	max_w_star_trace);
	int total_maintain= (current_sum_red_nova + current_sum_star_trace)*10;
	vector<int> total_values;
	vector<edge> temp;
	for(unsigned int i=0;i<paths_star_red.size();i++){
		int total =0;
		for(auto it=paths_star_red[i].begin();it!=paths_star_red[i].end();it++){
			total= total_maintain + (it->weight*10) + (it->cost);
			total_values.push_back(total);
			temp.push_back(*it);
		}
	}
	vector<edge> red_nova_weights;
	vector<edge> star_trace_weights;
	int k=0;
	sort_weights(red_nova_list,star_trace_list,red_nova_weights,star_trace_weights);
	vector<list<edge> > list_new_red_nova(red_nova_list.size());
  int red_index=cost_networks_red_nova(list_new_red_nova,red_nova_list,star_trace_list,red_nova_weights,
	paths_star_red);
	red_nova_weights[red_index].k=1;
	vector<list<edge> > list_new_star_trace(star_trace_list.size());
	int star_index= cost_networks_star_trace(list_new_star_trace,star_trace_list,red_nova_list,star_trace_weights,
	paths_star_red);
  star_trace_weights[star_index].k=2;
  int total_star_red= total_star_red_maintain(star_index,red_index,k,
	red_nova_weights,star_trace_weights,total_maintain,paths_star_red);
  total_values.push_back(total_star_red);
	print_networks(temp,k,red_index,star_index,
		red_nova_weights,star_trace_weights,total_values);

	return 0;
}
