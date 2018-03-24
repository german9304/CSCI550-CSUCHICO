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
void addCostEdge(vector<list<edge> > & alist , int from,int to,int w,int cost){
	edge vertex_cost;
	vertex_cost.from=from;
	vertex_cost.to=to;
	vertex_cost.weight=w;
	vertex_cost.cost=cost;
	alist[0].push_back(vertex_cost);
}
void addEdgeC(vector<list<edge> > & alist , int v_from, int v_to, int from,int to,int w,int cost){
	edge vertex_from;
	vertex_from.v_from=v_from;
	vertex_from.v_to=v_to;
	vertex_from.from=from;
	vertex_from.to=to;
	vertex_from.weight=w;
	vertex_from.cost=cost;
	alist[v_from].push_back(vertex_from);
	edge vertex_to;
	vertex_to.v_from=v_to;
	vertex_to.v_to=v_from;
	vertex_to.from=to;
	vertex_to.to=from;
	vertex_to.weight=w;
	vertex_to.cost=cost;
	alist[v_to].push_back(vertex_to);
}
int BFS(vector<list<edge> > & alist,int source,vector<int> & parent_array,
vector<int> & distance_array){
	int current_sum=0;
  int vert_size= parent_array.size();
  queue<int> pq;
  distance_array[source]=0;
  pq.push(source);
  vector<bool> vertex_visited(vert_size,false);
  int vert= pq.front();
	//cout <<endl;
	//cout <<"BFS" <<endl;
	//cout << "vert " <<vert <<endl;
	while(!pq.empty()){
    vert= pq.front();
		//cout << "vert " <<vert <<endl;

			for(auto it=alist[vert].begin();it!=alist[vert].end();it++){
		   if(!vertex_visited[it->to] && distance_array[it->to]==-1){
				current_sum+=it->weight  ;

		    distance_array[it->to]=distance_array[vert]+it->weight;
				//cout << "to: " << it->to <<" " << " d: " <<   distance_array[it->to]<< " "
			// << " w: " << it->weight <<endl;
		    parent_array[it->to]=vert;
		    pq.push(it->to);
		    vertex_visited[it->to]=true;
		  }
		 }
		// cout <<endl;
    vertex_visited[vert]=true;
    pq.pop();
  }
	return current_sum;
	//cout << "sum weight: " <<current_sum <<endl;
}

int BFS_2(vector<list<edge> > & alist,int source,vector<int> & parent_array,
vector<int> & distance_array){
	int current_sum=0;
  int vert_size= parent_array.size();
  queue<int> pq;
  distance_array[source]=0;
  pq.push(source);
  vector<bool> vertex_visited(vert_size,false);
  int vert= pq.front();
	//cout <<endl;
	//cout <<"BFS" <<endl;
	//cout << "vert " <<vert <<endl;
	while(!pq.empty()){
    vert= pq.front();
		//cout << "vert " <<vert <<endl;

			for(auto it=alist[vert].begin();it!=alist[vert].end();it++){
		   if(!vertex_visited[it->v_to] && distance_array[it->v_to]==-1){
				current_sum+=it->weight  ;

		    distance_array[it->v_to]=distance_array[vert]+1;
				//cout << "to: " << it->to <<" " << " d: " <<   distance_array[it->to]<< " "
			// << " w: " << it->weight <<endl;
		    parent_array[it->v_to]=vert;
		    pq.push(it->v_to);
		    vertex_visited[it->v_to]=true;
		  }
		 }
		// cout <<endl;
    vertex_visited[vert]=true;
    pq.pop();
  }
	return current_sum;
	//cout << "sum weight: " <<current_sum <<endl;
}

void backtrack_parentarray(vector<list<edge> > & alist,int index,vector<int> &parent_array,
vector<bool> & vertex_visited,int & max_w){
   if(index==parent_array[index]){
       return;
	 }
	 //cout <<"index back " <<index <<endl;
	 for(auto iter=alist[index].begin();iter!=alist[index].end();iter++){

			// int to = iter->to;
 			 //if( !vertex_visited[iter->to]){
				// vertex_visited[index]=true;
        if(iter->weight>max_w){
         max_w=iter->weight;
				 //cout << "from " << index<< " to: " << " " << iter->to << " " << iter->weight << endl;
				}
      // cout << "from " << index<< " to: " << " " << iter->to << " " << iter->weight << endl;
 		//}

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
	//cout <<endl;
	vector<int> distance_array(size);
	vector<int> parent_array(size);
	int source=0;
	int cc_count=0;
	std::vector<int> v;
	unsigned int i=0;
	while(i!=size){
		init(distance_array,size);
		//cout <<endl;
		BFS(adjA,source,parent_array,distance_array);
		/*
		cout << "distance_array" <<endl;
		for(unsigned int i=0;i<distance_array.size();i++){
			cout <<  distance_array[i] <<" ";
		}
		cout <<endl;
		*/
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
	return total_cc;
}

int cost_networks(vector<list<edge> > & new_list,vector<list<edge> > &
    adjA,vector<list<edge> > &adjB, int max_w,vector<list<edge> > paths_star_red){
   	cout << "removed max weight " << max_w << endl;

 		for(unsigned int i=0;i<adjA.size();i++){
 			for(auto iter=adjA[i].begin();iter!=adjA[i].end();iter++){
 				unsigned int to = iter->to;
 				if(i< to){
					//1157 1699
					//162 617
					//582 1995
					//772 1386
					//1651 1892
					//if(i==1157&& iter->to==1699&& iter->weight ==940){
 				 if(iter->weight!=max_w){
 						//cout << "from " << i << " " << iter->to << " " << iter->weight <<" " <<endl;
 						addEdge(new_list,i,iter->to,iter->weight);
 						//max_w_red_nova
 				//addEdge()
			}
			/*else{
				addEdge(new_list,i,iter->to,iter->weight);
			}
			*/
 			  }
 			}
 			//cout <<endl;
 		}
  //  cout <<"new list"<<endl;
/*
		for(unsigned int i=0;i<list_new_red_nova.size();i++){
			for(auto iter=list_new_red_nova[i].begin();iter!=list_new_red_nova[i].end();iter++){
				unsigned int to = iter->to;
				if(i< to){
					cout << i << " " << iter->to << " " << iter->weight <<" "<<endl;
				}
			}
		}
*/
		vector<int> cc_1(new_list.size(),-1);
		//int index=list_new_red_nova.size();
		//cout << "size: " << adjA.size() <<endl;

		int res = connectd(new_list,cc_1);
		vector<int> cc_2(adjB.size(),res);

		cout <<endl;
		cout << "conected components 1 " << cc_1.size() <<endl;
		for(unsigned int i=0;i<cc_1.size();i++){
			cout <<cc_1[i] <<" ";
		}
		cout <<endl;
		cout << "conected components 2 "  << cc_2.size() <<endl;
		for(unsigned int i=0;i<cc_2.size();i++){
			cout <<cc_2[i] <<" ";
		}
   cout <<endl;
    vector<list<edge> > adjC(res+1);
		cout << " size: " << adjC.size() <<endl;
/*
 		for(unsigned int i=0;i<star_trace_list.size();i++){
 			for(auto iter=star_trace_list[i].begin();iter!=star_trace_list[i].end();iter++){
 				unsigned int to = iter->to;
  				if(i< to){
 				cout << iter->from << " " << iter->to << " " << iter->weight <<" "<<endl;
 			  }
 			}
 		}
*/
		//cout << "start trace" <<endl;
		//int index = list_new_red_nova.size()-1;
/*
		for(unsigned int i=0;i<star_trace_list.size();i++){
			for(auto iter=star_trace_list[i].begin();iter!=star_trace_list[i].end();iter++){
				unsigned int to = iter->to;
 				if(i< to){
				cout << iter->from << " " << iter->to << " " << iter->weight <<" "<<endl;
			  }
			}
		}
*/
/*
cout << "paths red star " <<endl;
for(unsigned int i=0;i<paths_star_red.size();i++){
	for(auto iter=paths_star_red[i].begin();iter!=paths_star_red[i].end();iter++){
		//addEdgeC(adjC,cc_1[iter->from],cc_2[iter->to],iter->from,iter->to,iter->weight,iter->cost);
		//cout  << iter->from << " " << iter->to <<
		//"  " << iter->weight << endl;
	}
}
for(unsigned int i=0;i<adjC.size();i++){
	for(auto iter=adjC[i].begin();iter!=adjC[i].end();iter++){
		//addEdgeC(adjC,cc_2[iter->from],cc_1[iter->to],iter->from,iter->to,iter->weight,iter->cost);
	   //cout  << iter->v_from << " " << iter->v_to <<
		 // "  " << iter->weight << endl;
	}
}
*/
/*
vector<int> parent_array(adjC.size());
vector<int> distance_array(adjC.size(),-1);
BFS_2(adjC,0,parent_array,distance_array);
cout << "distance_array in components s"<<endl;
for(unsigned int i=0;i<distance_array.size();i++){
  cout << distance_array[i] << " ";
}
*/
cout <<endl;
    cout << "res: " << res <<endl;
		return 0;
}
bool myfunction (int i,int j) { return (i>j); }

int main(){

  int red_nova_stations;
	int sum_red_nova_weights=0;
	//int red_nova_w=0;
	//cout << "red_nova_list"<<endl;
	cin>>red_nova_stations;
	vector< list<edge> > red_nova_list(red_nova_stations);
	vector<int> red_nova_weights;
	int from,to,weight;
	for(int i=0;i<red_nova_stations-1;i++){
		cin>> from>> to >> weight;
		sum_red_nova_weights+=weight;
		red_nova_weights.push_back(weight);
		//cout << from << " " << to << " " << weight << " "<<endl;
    addEdge(red_nova_list,from,to,weight);
	}
	int star_trace_stations;
	int sum_star_trace_weights=0;
	//int sum_star_trace_w=0;
	//cout << "star_trace_list"<<endl;
	cin>>star_trace_stations;
	vector<int>  star_trace_weights;
	vector< list<edge> > star_trace_list(star_trace_stations);
	for(int i=0;i<star_trace_stations-1;i++){
		cin>> from>> to >> weight;
		star_trace_weights.push_back(weight);
		//if(weight>sum_star_trace_w){
      // sum_star_trace_w=weight;
		//}
		sum_star_trace_weights+=weight;
    //cout << from << " " << to << " " << weight << " "<<endl;
    addEdge(star_trace_list,from,to,weight);
	}
	vector<list<edge> > paths_star_red(20);
	int from_path,to_path,cost_path,weight_path;
	for(int i=0;i<2;i++){
		cin>> from_path>> to_path >> weight_path>> cost_path;
		cout << from_path<< " " <<to_path  << " " << weight_path<< " "<< cost_path <<endl;
    addCostEdge(paths_star_red,from_path,to_path,weight_path,cost_path);
	}
	cout << "Sum Red Nova ";
	cout << sum_red_nova_weights *10<<endl;
	cout << "Sum Star Trace ";
	cout << sum_star_trace_weights*10<<endl;
/*
	cout << "weights red nova "<<endl;
	  std::sort (red_nova_weights.begin(), red_nova_weights.end(), myfunction);
  std::cout << "myvector contains:"<<endl;
  for (std::vector<int>::iterator it=red_nova_weights.begin(); it!=red_nova_weights.end(); ++it)
    std::cout << ' ' << *it<<endl;
  std::cout << '\n';

	cout << "weights star trace "<<endl;
	  std::sort (star_trace_weights.begin(), star_trace_weights.end(), myfunction);
  std::cout << "myvector contains:"<<endl;
  for (std::vector<int>::iterator it=star_trace_weights.begin(); it!=star_trace_weights.end(); ++it)
    std::cout << ' ' << *it<<endl;
  std::cout << '\n';
*/
	/*
	cout << "paths_star_red"<<endl;

	for(unsigned int i=0;i<paths_star_red.size();i++){
		for(auto it=paths_star_red[i].begin();it!=paths_star_red[i].end();it++){
       cout <<i << " " <<  it->from << " " << it->to <<" "<< it->weight << " " << it->cost;
			 	cout <<endl;
		}
	}
	*/
	/*
	cout << "red_nova_list"<<endl;
	for(unsigned int i=0;i<red_nova_list.size();i++){
		cout <<"from " << i << " ";
		for(auto it= red_nova_list[i].begin();it!=red_nova_list[i].end();it++){
			unsigned int to = it->to;
			 if( to> i ){
        cout << "to: " << it->to<<" " << it->weight <<endl;
			}
		}
	}

	cout << "star_trace_list"<<endl;
	for(unsigned int i=0;i<(unsigned) star_trace_list.size();i++){
		 cout <<"from " << i << " " <<endl;
		for(auto it= star_trace_list[i].begin();it!=star_trace_list[i].end();it++){
        	//unsigned int to = it->to;
					// if( to> i ){
		        cout << "to: " << it->to<<" " << it->weight <<endl;
					//}
				}
		}
*/
		vector<int>  red_nova_parent_array(red_nova_stations,0);
		vector<int>  red_nova_distance_array(red_nova_stations,-1);
		int current_sum_red_nova=0;
		current_sum_red_nova= BFS(red_nova_list,0,red_nova_parent_array,red_nova_distance_array);
		vector<bool> vertex_visited(red_nova_list.size(),false);
		cout << "red_nova_stations: " << red_nova_stations <<endl;
		int max_w_red_nova=0;
		backtrack_parentarray(red_nova_list,red_nova_stations-1,red_nova_parent_array,vertex_visited
		,max_w_red_nova);

		cout <<"max_weight red nova"<<" ";
		cout << max_w_red_nova <<endl;
/*
		cout << "----------red nova----------" <<endl;
		cout << "parent_array" <<endl;
		for(unsigned int i=0;i<red_nova_parent_array.size();i++){
       cout  << red_nova_parent_array[i] << " ";
		}
		cout <<endl;
		cout << "distance_array" <<endl;
		for(unsigned int i=0;i<red_nova_distance_array.size();i++){
         cout << red_nova_distance_array[i] << " ";
		}
   cout <<endl;
	 */
		vector<int>  star_trace_parent_array(star_trace_stations,0);
		vector<int>  star_trace_distance_array(star_trace_stations,-1);
		cout << "star_trace_stations: " << star_trace_stations <<endl;
		int current_sum_star_trace=0;
		current_sum_star_trace = BFS(star_trace_list,0,star_trace_parent_array,star_trace_distance_array);
		int max_w_red_star=0;
		vector<bool> vertex_visited_star(star_trace_list.size(),false);
		backtrack_parentarray(star_trace_list,star_trace_stations-1,star_trace_parent_array,vertex_visited_star,
		max_w_red_star);

		cout <<"max_weight star trace"<< " ";
		cout << max_w_red_star <<endl;
/*
		cout << "---------star trace---------" <<endl;
		cout << "parent_array" <<endl;
		for(unsigned int i=0;i<star_trace_parent_array.size();i++){
        cout << star_trace_parent_array[i] << " ";
		}
		cout <<endl;
		cout << "distance_array" <<endl;
		for(unsigned int i=0;i<star_trace_distance_array.size();i++){
      cout <<  star_trace_distance_array[i] << " ";
		}
   cout <<endl;
	 */
   //cout << "sum red_nova: " << current_sum_red_nova<<endl;
	 //cout << "sum star trace: " << current_sum_star_trace<<endl;
	 int total_maintain= (current_sum_red_nova + current_sum_star_trace)*10;
	 int total_maintain_1= (current_sum_red_nova + current_sum_star_trace);
	 cout<< "total : " << total_maintain_1 << endl;
	 cout<< "total: *10 " << total_maintain << endl;
	   vector<int> total_values;
	  	for(unsigned int i=0;i<paths_star_red.size();i++){
				int total =0;
 	 		for(auto it=paths_star_red[i].begin();it!=paths_star_red[i].end();it++){
				total= total_maintain + (it->weight*10) + (it->cost);
				total_values.push_back(total);
 	       // cout <<i << " " <<  it->from << " " << it->to <<" "<< it->weight << " " << it->cost;
 	 			 //	cout <<endl;

 	 		}
 	 	}
		/*
		components
		red nova
		*/

    vector<list<edge> > list_new_red_nova(red_nova_list.size());
		//vector<int > cc(red_nova_stations.size());
		//vector<int> cc_rednova(0);
		//vector<int> cc_startrace(1);
		cout << "redNova components"<<endl;
		cost_networks(list_new_red_nova,red_nova_list,star_trace_list,max_w_red_nova,
		paths_star_red);
    cout << "starTracs components"<<endl;
		vector<list<edge> > list_new_star_trace(star_trace_list.size());
		 cost_networks(list_new_star_trace,star_trace_list,red_nova_list,max_w_red_star,
		paths_star_red);

		cout << "total_values: " <<endl;
		for(unsigned int i=0;i<total_values.size();i++){
			cout << total_values[i] <<endl;
		}
	return 0;
}
