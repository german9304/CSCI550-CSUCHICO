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
	/*
	cout << "list running inside BFS" <<endl;
	for(int i=0;i<alist.size();i++){
		for(auto iter=alist[i].begin();iter!=alist[i].end();iter++){
		       cout << i << " " << iter->to << " " << iter->weight << " "<<endl;
	}
}
*/
	//cout <<endl;
	int current_sum=0;
  int vert_size= parent_array.size();
  queue<int> pq;
  distance_array[source]=0;
  pq.push(source);
  vector<bool> vertex_visited(vert_size,false);
	/*
	  for(unsigned int i=0;i<vertex_visited.size();i++){
        cout << vertex_visited[i] << " ";
		}
		*/
		/*
		cout << "distance_array inside the BFS " <<endl;
		 for(unsigned int i=0;i<distance_array.size();i++){
         cout << distance_array[i] << " ";
 		}
		*/
	//cout <<endl;
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

		    distance_array[it->to]=distance_array[vert]+1;
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
		/*
		cout << "distance_array before BFS" <<endl;
		for(unsigned int i=0;i<distance_array.size();i++){
			cout <<  distance_array[i] <<" ";
		}
		*/
		//cout <<endl;
		BFS(adjA,source,parent_array,distance_array);
/*
		cout << "distance_array BFS" <<endl;
		for(unsigned int i=0;i<distance_array.size();i++){
			cout <<  distance_array[i] <<" ";
		}
		*/
		//cout <<endl;

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
   //	cout << "removed max weight " << max_w << endl;
for(unsigned int index=0;index<weights.size();index++){
	//int temp = index;
 		for(unsigned int i=0;i<red_nova_list.size();i++){
			int a =i;
 			for(auto iter=red_nova_list[i].begin();iter!=red_nova_list[i].end();iter++){
 				unsigned int to = iter->to;
 				if(i< to){
					//if(i==1157&& iter->to==1699&& iter->weight ==940){
					//cout << "from " << weights[index].from << " " << weights[index].to<< " " << weights[index].weight <<" " <<endl;
 				 if(a!= weights[index].from || iter->to!= weights[index].to || iter->weight!=weights[index].weight){
 						//cout << "inside from " << i << " " << iter->to << " " << iter->weight <<" " <<endl;
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
		vector<int> cc_2(star_trace_list.size(),res);
/*
		cout <<endl;
		cout << "conected components 1 " << cc_1.size() <<endl;
		for(unsigned int i=0;i<cc_1.size();i++){
			//cout <<cc_1[i] <<" ";
		}
		cout <<endl;
		cout << "conected components 2 "  << cc_2.size() <<endl;
		for(unsigned int i=0;i<cc_2.size();i++){
			//cout <<cc_2[i] <<" ";
		}
   cout <<endl;
	 */
    vector<list<edge> > adjC(res+1);
		//cout << " size: " << adjC.size() <<endl;
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


	//cout << "paths red star " <<endl;
	for(unsigned int i=0;i<paths_star_red.size();i++){
		for(auto iter=paths_star_red[i].begin();iter!=paths_star_red[i].end();iter++){
			addEdgeC(adjC,cc_1[iter->from],cc_2[iter->to],iter->from,iter->to,iter->weight,iter->cost);
		//	cout  << iter->from << " " << iter->to <<
			//"  " << iter->weight << endl;
		}
	}
	/*
	for(unsigned int i=0;i<adjC.size();i++){
		for(auto iter=adjC[i].begin();iter!=adjC[i].end();iter++){
			//addEdgeC(adjC,cc_2[iter->from],cc_1[iter->to],iter->from,iter->to,iter->weight,iter->cost);
			cout  << iter->v_from << " " << iter->v_to <<
			"  " << iter->weight << endl;
		}
	}
*/

	vector<int> parent_array(adjC.size());
	vector<int> distance_array(adjC.size(),-1);
	BFS(adjC,0,parent_array,distance_array);
	  std::vector<int>::iterator it;
  it = find (distance_array.begin(), distance_array.end(), -1);
  if (it != distance_array.end()){
		/*
    std::cout << "Element found in myvector: " << *it << '\n';
		cout << "from " << weights[index].from << " to: " <<  weights[index].to << " weight: " <<
		weights[index].weight <<endl;
		*/
  }else{
    //std::cout << "Element not found in myvector\n";
		//cout << "from " << weights[index].from << " to: " <<  weights[index].to << " weight: " <<
		//weights[index].weight <<endl;
		//index=weights.size();
			weights[index].k=1;
		return index;
	}
adjC.clear();
cc_1.clear();
cc_2.clear();
 parent_array.clear();
 distance_array.clear();
 //new_list.clear();
 //cout <<endl;
 /*
 cout << "sizes: " <<endl;
 cout << adjC.size() << " " << cc_1.size() << " " << cc_2.size() << " " << parent_array.size()
 << " " << distance_array.size() << " " << new_list.size() <<endl;
 */
 new_list.clear();
 new_list.resize(red_nova_list.size());
 /*
	cout << "distance_array in components s"<<endl;
	for(unsigned int i=0;i<distance_array.size();i++){
		cout << distance_array[i] << " ";
   }
	 */
}
//cout <<endl;
    //cout << "res: " << res <<endl;
		return 0;
}
int cost_networks_star_trace(vector<list<edge> > & new_list,vector<list<edge> > &
    star_trace,vector<list<edge> > &red_nova_list, vector<edge> weights,vector<list<edge> > paths_star_red){
  // 	cout << "removed max weight " << max_w << endl;
for(unsigned int index=0;index<weights.size();index++){
	//int temp=index;
	//cout << "star trace checking" <<endl;
	//cout << "from " << weights[index].from << " " << weights[index].to<< " " << weights[index].weight <<" " <<endl;
 		for(unsigned int i=0;i<star_trace.size();i++){
			int a = i;
 			for(auto iter=star_trace[i].begin();iter!=star_trace[i].end();iter++){
 				unsigned int to = iter->to;
 				if(i< to){
					//1157 1699
					//162 617
					//582 1995
					//772 1386
					//1651 1892
					// 1130 to: 1566
					//cout << "from " << weights[index].from << " " << weights[index].to<< " " << weights[index].weight <<" " <<endl;
				 if(a!= weights[index].from || iter->to!= weights[index].to || iter->weight!=weights[index].weight){
				//if(i!=1130|| iter->to!=1566 || iter->weight !=1019){
 				 //if(iter->weight!=max_w){
 						//cout <<"inside: " <<  "from " << a<< " " << iter->to << " " << iter->weight <<" " <<endl;
 						addEdge(new_list,i,iter->to,iter->weight);
 						//max_w_red_nova
 				//addEdge()
			    }

 			  }
 			}
 			//cout <<endl;
 		}
  //  cout <<"new list startrace "<< new_list.size() << endl;

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
/*
cout <<"--------------"<<endl;
			for(unsigned int i=0;i<new_list.size();i++){
				for(auto iter=new_list[i].begin();iter!=new_list[i].end();iter++){
					unsigned int to = iter->to;
					if(i< to){
						cout << i << " " << iter->to << " " << iter->weight <<" "<<endl;
					}
				}
			}
			cout <<"--------------"<<endl;
			*/
		vector<int> cc_1(new_list.size(),-1);
		//cout <<" cc_1 " << endl;
		//for(unsigned int i=0;i<cc_1.size();i++){
       //cout << cc_1[i] <<" ";
	//	}
		//cout <<endl;
		//int index=list_new_red_nova.size();
		//cout << "size: " << adjA.size() <<endl;

		int res = connectd(new_list,cc_1);
		//cout << "result connected " << res <<endl;
		vector<int> cc_2(red_nova_list.size(),res);

		//cout <<endl;
		//cout << "conected components 1 " << cc_1.size() <<endl;
		/*
		for(unsigned int i=0;i<cc_1.size();i++){
		cout <<cc_1[i] <<" ";
		}
		*/
		//cout <<endl;
		//cout << "conected components 2 "  << cc_2.size() <<endl;
		/*
		for(unsigned int i=0;i<cc_2.size();i++){
			cout <<cc_2[i] <<" ";
		}
		*/
   //cout <<endl;
    vector<list<edge> > adjC(res+1);
		//cout << " size: " << adjC.size() <<endl;
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

//cout << "paths red star " <<endl;
for(unsigned int i=0;i<paths_star_red.size();i++){
	for(auto iter=paths_star_red[i].begin();iter!=paths_star_red[i].end();iter++){
		addEdgeC(adjC,cc_2[iter->from],cc_1[iter->to],iter->from,iter->to,iter->weight,iter->cost);
		//cout  << iter->from << " " << iter->to <<
		//"  " << iter->weight << endl;
	}
}
/*
	cout << "ADJ C " <<adjC.size() <<endl;
for(unsigned int i=0;i<adjC.size();i++){
	for(auto iter=adjC[i].begin();iter!=adjC[i].end();iter++){
		int t = iter->to;
		int f = iter->from;
     if(f< t){
		 cout  << iter->from << " " << iter->to <<
		  "  " << iter->weight << endl;
		}
		//addEdgeC(adjC,cc_2[iter->from],cc_1[iter->to],iter->from,iter->to,iter->weight,iter->cost);
	  // cout  << iter->v_from << " " << iter->v_to <<
		 // "  " << iter->weight << endl;
	}
}

*/

	vector<int> parent_array(adjC.size());
	vector<int> distance_array(adjC.size(),-1);
	/*
	cout <<"distance_array star_trace" <<endl;
	for(unsigned int i=0;i<distance_array.size();i++){
		cout << distance_array[i] << " ";
	}
	cout <<endl;
	*/
	BFS(adjC,0,parent_array,distance_array);
	std::vector<int>::iterator it;
  it = find (distance_array.begin(), distance_array.end(), -1);
  if (it != distance_array.end()){
    //std::cout << "Element found in myvector: " << *it << '\n';
		//cout << "from " << weights[index].from << " to: " <<  weights[index].to << " weight: " <<
		//weights[index].weight <<endl;
  }else{
    //std::cout << "Element not found in myvector\n";
	  //cout << "from " << weights[index].from << " to: " <<  weights[index].to << " weight: " <<
		//weights[index].weight <<endl;
		//index=weights.size();
		weights[index].k=2;
		return index;
			//index=weights.size();
	}
	/*
	cout << "distance_array in components s"<<endl;
	for(unsigned int i=0;i<distance_array.size();i++){
	 cout << distance_array[i] << " ";
	}
	*/
	adjC.clear();
	cc_1.clear();
	cc_2.clear();
	 parent_array.clear();
	 distance_array.clear();
	 //new_list.clear();
	 /*
	 cout <<endl;
	 cout << "sizes: " <<endl;
	 cout << adjC.size() << " " << cc_1.size() << " " << cc_2.size() << " " << parent_array.size()
	 << " " << distance_array.size() << " " << new_list.size() <<endl;
	 */
	 new_list.clear();
	 new_list.resize(star_trace.size());
	 /*
	  cout <<" new list after " <<endl;
	 cout <<"--------------"<<endl;
	 			for(unsigned int i=0;i<new_list.size();i++){
	 				for(auto iter=new_list[i].begin();iter!=new_list[i].end();iter++){
	 					unsigned int to = iter->to;
	 					if(i< to){
	 						cout << i << " " << iter->to << " " << iter->weight <<" "<<endl;
	 					}
	 				}
	 			}
	 cout <<"--------------"<<endl;
	 */
}
//cout <<endl;
    //cout << "res: " << res <<endl;
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
	/*
	cout << "weights red nova "<<endl;
  std::cout << "myvector contains: "<< red_nova.size() << endl;
 for(unsigned int i=0;i<red_nova.size();i++){
  	cout <<red_nova[i].from << " " << red_nova[i].to << " " <<  red_nova[i].weight << endl;
 }
*/
	//cout << "weights star trace "<<endl;
	  //std::cout << "myvector contains: "<< star_trace.size() << endl;
 //for(unsigned int i=0;i<star_trace.size();i++){
    // cout <<star_trace[i].from << " " << star_trace[i].to << " " <<  star_trace[i].weight << endl;
 //}

}


int main(){

  int red_nova_stations;
	int sum_red_nova_weights=0;
	//int red_nova_w=0;
	//cout << "red_nova_list"<<endl;
	cin>>red_nova_stations;
	vector< list<edge> > red_nova_list(red_nova_stations);
	int from,to,weight;
	for(int i=0;i<red_nova_stations-1;i++){
		cin>> from>> to >> weight;
		sum_red_nova_weights+=weight;
		//cout << from << " " << to << " " << weight << " "<<endl;
    addEdge(red_nova_list,from,to,weight);
	}
	int star_trace_stations;
	int sum_star_trace_weights=0;
	//int sum_star_trace_w=0;
	//cout << "star_trace_list"<<endl;
	cin>>star_trace_stations;

	vector< list<edge> > star_trace_list(star_trace_stations);
	for(int i=0;i<star_trace_stations-1;i++){
		cin>> from>> to >> weight;
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
		//cout << from_path<< " " <<to_path  << " " << weight_path<< " "<< cost_path <<endl;
    addCostEdge(paths_star_red,from_path,to_path,weight_path,cost_path,i+1);
	}
	//cout << "Sum Red Nova ";
	//cout << sum_red_nova_weights *10<<endl;
	//cout << "Sum Star Trace ";
	//cout << sum_star_trace_weights*10<<endl;



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
		//cout << "red_nova_stations: " << red_nova_stations <<endl;
		int max_w_red_nova=0;
		backtrack_parentarray(red_nova_list,red_nova_stations-1,red_nova_parent_array,vertex_visited
		,max_w_red_nova);

		//cout <<"max_weight red nova"<<" ";
		//cout << max_w_red_nova <<endl;
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
		//cout << "star_trace_stations: " << star_trace_stations <<endl;
		int current_sum_star_trace=0;
		current_sum_star_trace = BFS(star_trace_list,0,star_trace_parent_array,star_trace_distance_array);
		int max_w_star_trace=0;
		vector<bool> vertex_visited_star(star_trace_list.size(),false);
		backtrack_parentarray(star_trace_list,star_trace_stations-1,star_trace_parent_array,vertex_visited_star,
		max_w_star_trace);

		//cout <<"max_weight star trace"<< " ";
		//cout << max_w_star_trace<<endl;
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
	// int total_maintain_1= (current_sum_red_nova + current_sum_star_trace);
	 //cout<< "total : " << total_maintain_1 << endl;
	 //cout<< "total: *10 " << total_maintain << endl;
	   vector<int> total_values;
		 //cout << " AD BD inserted"<<endl;
		 vector<edge> temp;
	  	for(unsigned int i=0;i<paths_star_red.size();i++){
				int total =0;
 	 		for(auto it=paths_star_red[i].begin();it!=paths_star_red[i].end();it++){
				total= total_maintain + (it->weight*10) + (it->cost);
				total_values.push_back(total);
				temp.push_back(*it);
 	      //  cout  << i << " " <<  it->from << " " << it->to <<" "<< it->weight << " " << it->cost;
 	 			 //	cout <<endl;

 	 		}
 	 	}
		//cout << "---------"<<endl;
		/*
		components
		red nova
		*/
		vector<edge> red_nova_weights;
    vector<edge> star_trace_weights;
		sort_weights(red_nova_list,star_trace_list,red_nova_weights,star_trace_weights);
    vector<list<edge> > list_new_red_nova(red_nova_list.size());
		//vector<int > cc(red_nova_stations.size());
		//vector<int> cc_rednova(0);
		//vector<int> cc_startrace(1);
		//cout << "redNova components"<<endl;
		int red_index=cost_networks_red_nova(list_new_red_nova,red_nova_list,star_trace_list,red_nova_weights,
		paths_star_red);
		red_nova_weights[red_index].k=1;
		//cout << "from " << red_nova_weights[red_index].from << " to: " <<  red_nova_weights[red_index].to << " weight: " <<
		//red_nova_weights[red_index].weight << " " << red_nova_weights[red_index].k << endl;
		//cout << "-------------"<<endl;
  //  cout << "starTracs components"<<endl;
		vector<list<edge> > list_new_star_trace(star_trace_list.size());
		 int star_index= cost_networks_star_trace(list_new_star_trace,star_trace_list,red_nova_list,star_trace_weights,
		paths_star_red);
		star_trace_weights[star_index].k=2;
		//cout << "from " << star_trace_weights[star_index].from << " to: " <<  star_trace_weights[star_index].to << " weight: " <<
		//star_trace_weights[star_index].weight << " " << star_trace_weights[star_index].k<< endl;
		//cout << "-------------"<<endl;
		  int selected_Index=red_index;
			int k = red_nova_weights[red_index].k;
		  int w_1 = red_nova_weights[red_index].weight;
			int w_2= star_trace_weights[star_index].weight;
		  if(w_2>w_1){
				k=star_trace_weights[star_index].k;
          selected_Index= star_index;
			}

      //cout << "from " << star_trace_weights[selected_Index].from << " to: " <<  star_trace_weights[selected_Index].to
			//<< " weight: " <<star_trace_weights[selected_Index].weight << " " << star_trace_weights[selected_Index].k<< endl;
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
 				//total_values.push_back(total);
  	       // cout  << i << " " <<  it->from << " " << it->to <<" "<< it->weight << " " << it->cost;
  	 			 //	cout <<endl;

  	 		}
  	 	}
			total_star_red=new_maintain + total_w + total_c;
			//cout << " new maintain " << new_maintain<< endl;
			total_values.push_back(total_star_red);
			//cout << "total_values: " <<endl;
			int min= total_values[0];
			int selected=0;
			for(unsigned int i=0;i<total_values.size();i++){
				//cout << total_values[i] <<endl;
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


	return 0;
}
