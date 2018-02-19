
/*********************************************
1. adjD is the answer: adjacency list containing
selected edges, the max-weight of which you need to output

2. On the way down of recursion
adjD has the same number of vertices as orig graph, but
adjacency lists are empty

3. On the way up of recursion,
adjD grows: we add original edges from the Smallest-half
edges (not always, only in those recursive calls where
graph over smallest-half edges was not connected)

4. Initially, in adjA's vector is indexed by vertices of
original graph, and for each edge (u, v),
adjA[u] has v
adjA[v] has u

5. Initially, adjD's vector has the same size as
the number of vertices in the original graph
(and this does not change through the algorithm)
***********************************************/

#include<algorithm>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<list>
#include <queue>
using namespace std;
class edge{
public:
	int vert;
	int from_vert;
	int to_vert;
	int weight_to;
	int weight;
	int from;
	int to;
	int edge;
};
class vertex{
public:
	int distance;
	int v;
	bool visited;
	int index;
};

class component{
public:
	int v;
	int cc;
};

int select(vector<int> &v, int start, int fin, int k){

    int vsize = fin - start + 1;

    if(start == fin)
        return v[start];
    else if(start > fin)
        return -1;

	if(vsize <= 5){
		sort(v.begin() + start, v.begin() + fin + 1);

		return v[k];
	}

	int msize = ceil((double)vsize/5);

    vector<int> medians(msize, 0);
    int med_ind = 0;
    for(int i = start; i <= fin; i = i + 5){
        vector<int> temp(5, 0);
        int j = 0;
        for(; j < 5 && (i + j)<= fin; j++){
            temp[j] = v[i+j];
        }//for j
        if(j < 5)
            temp.resize(j);
        sort(temp.begin(), temp.end());
        if(j == 5)
            medians[med_ind++] = temp[2];
        else{
            int jmid = j >> 1;//divide by 2
            if(j % 2 == 0)
                jmid--;
            medians[med_ind++] = temp[jmid];

            }
    }//for i
    //so far we selected medians of n/5 groups of 5 elem
    int mid = msize >> 1; //divide by 2
    if((msize % 2) == 0)
        mid--;
    int x = select(medians, 0, msize - 1, mid);
    //partition v's elements around x
    //find x
    int indx = -1;
    for(int i = start; i <= fin; i++){
        if(v[i] == x){
            indx = i;
            break;
            }
    }//for i
    if(indx == -1)
        return -2;
    int t = v[start];
    v[start] = x;
    v[indx] = t;
    int i = start + 1, j = fin;
    while(i < j){
        if(v[i] > x && v[j] <= x){
            t = v[j];
            v[j] = v[i];
            v[i] = t;
            i++;
            j--;
        }//if
        else if(v[i] <= x){
            i++;
            if(i > fin){
                i--;
                break;
            }
            }
        else{
            j--;
            if(j == 0){
                j++;
                break;
            }
            }
    }//while partition
    int last = i;
    if(v[i] > x)
        last--;//last index that has less than or equal elemenents than x
//count how many elements are equal to x
    int count_equal = 0;
    for(int u = start; u <= last; u++){
        if(v[u] == x)
            count_equal++;
    }//for u

    if(k > (last - count_equal) && k <= last)
        return x;
    else if(last < k)
        return select(v, last + 1, fin, k);
    else
        return select(v, start, last, k);
}//select

void addEdge(vector<list<edge> > &adjA,int from,int to,int weight,int f,int t){
	edge aedge_from;
	aedge_from.vert=to;
	aedge_from.weight_to=weight;
	aedge_from.weight=weight;
	aedge_from.from=f;
	aedge_from.to=t;
	aedge_from.from_vert=from;
	aedge_from.to_vert=to;
	adjA[from].push_back(aedge_from);
	edge aedge_to;
	aedge_to.vert=from;
	aedge_to.weight_to=-1;
	aedge_to.weight=weight;
	aedge_to.from=t;
	aedge_to.to=f;
	aedge_to.from_vert=to;
	aedge_to.to_vert=from;
	adjA[to].push_back(aedge_to);

}

void collect_weights(vector<list<edge> > &adjA, vector<int> & weights){
	int index=0;
	for(int i=0;i<adjA.size();i++){
		for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it){
			if(it->weight_to!=-1){
				weights[index]=it->weight;
				index++;
			}
		}
	}
}

void select_smallest(vector<list<edge> > &adjA,vector<list<edge> > &adjB,
	int median_weight){
		vector<int> avert;
		bool temp = false;
		adjB.resize(adjA.size());
		for(int i=0;i<adjA.size();i++){
			for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it){
				if(it->weight_to!=-1){
					if(it->weight<=median_weight){
						addEdge(adjB,i,it->to_vert,it->weight,it->from,it->to);
						temp=true;
					}
				}
			}
			if(temp){
				avert.push_back(i);
				temp=false;
			}
		}
	}

	void select_gratest(vector<list<edge> > &adjA,vector<list<edge> > &adjB,
		int median_weight,vector<int> & cc,vector<int> & w){
			for(int i=0;i<adjA.size();i++){
				for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it){
					if(it->weight_to!=-1){
						if(it->weight>median_weight){
							if(cc[i]!=cc[it->vert]){
								addEdge(adjB,cc[i],cc[it->vert],it->weight,it->from,it->to);
							}
						}
					}
				}
			}
		}

void BFS(vector<list<edge> > &adjB,int s,int size,vector<int> & vert_arr){
	int vert_size= vert_arr.size();
	int source = s;
	queue<int> pq;
	vert_arr[s]=0;
	pq.push(source);
	vector<bool> vertex_visited(vert_size,false);
	int vert= pq.front();
	while(!pq.empty()){
		vert= pq.front();
		std::list<edge>::iterator 	it=adjB[vert].begin();
		for ( it=adjB[vert].begin(); it != adjB[vert].end(); ++it){
			if(!vertex_visited[it->to_vert] && vert_arr[it->to_vert]==-1){
				vert_arr[it->to_vert]=vert_arr[vert]+1;
				vertex_visited[it->to_vert]=true;
				pq.push(it->to_vert);
			}
		}
		vertex_visited[vert]=true;
		pq.pop();
	}
}
void init(vector<list<edge> > &adjB, vector<int> &distance_array,int size){
	std::list<edge>::iterator it;
	for(int i=0;i<size;i++){
		distance_array[i]=-1;
	}
}
int connected(vector<list<edge> > &adjB, vector<int> &cc){
	int size = adjB.size();
	int total_cc=1;
	vector<int> distance_array(size);
	for(int i=0;i<cc.size();i++){
		cc[i]=-1;
	}
	int source=0;
	int cc_count=0;
	std::vector<int> v;
	int i=0;
	while(i!=cc.size()){
		init(adjB,distance_array,size);
		BFS(adjB,source,size,distance_array);
		for(int j=0;j<distance_array.size();j++){
			if(distance_array[j]!=-1){
				if(cc[j]==-1){
					cc[j]=cc_count;
				}
			}
		}
		for( i=source;i<cc.size();i++){
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
void MBST( vector<list<edge> > &adjA,
	vector<list<edge> > &adjD){
		//Count the number of edges in adjA
		int m = 0;
		int size = adjA.size();
		for(int i = 0; i < size; i++){
			m += adjA[i].size();
		}
		m = m >> 1;//divide by 2, each edge occurs twice in Adj
		//BASE case, if number of edges is 1, return
		//after adding the first edge to adjD
		//cout << " m half " << m << endl;
		if(m == 1){
			//Here you need to add edge to adjD
			//from adjA (add original name of the edge)
			//.................................
			for(int i=0;i<2;i++){
				for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it){
					if(it->weight_to!=-1){
					addEdge(adjD,it->from,it->to,it->weight,it->from,it->to);
				 }
				}

			}
			return;
		}
		/***********   Collect weights of edges **********/
		vector<int> weights(m);
		//You need to write this function:
		collect_weights(adjA, weights);
		/*******   Find the median of weights *********/
		int k = m >> 1;//divide by 2
		if(m % 2 == 0)
		k--;
		int median_weight = select(weights, 0, m-1,k);
		//Function "select" is provided
		/*****  Collect edges with weights <= median_weight
		from adjA into adjB
		Erase an edge from adjA:
		it takes O(1) to erase (use erase) from
		a list
		*************************************************/
		vector< list<edge> > adjB(adjA.size());//smallest edges
		//You need to write this function:
		select_smallest(adjA, adjB, median_weight);
		/******* Find connected components in adjB
		in linear time
		***************************************/
		vector<int > cc(adjB.size());
		int total_cc = connected(adjB, cc);//number of comp
		/**********     If connected (only one component)
		we don't need edges of A anymore
		just call recursively MBST and return
		after the recursive call returns
		i.e. do nothing after recursive call returns
		****************************************/

		if(total_cc == 1){
			MBST(adjB, adjD);
     //return;
		}else{
			/******     If not connected,
			contract connected components
			construct adjC from adjA and
			super vertices (each represents a
			connected component)

			Rename edges according to the names
			of new supervertices (0, 1,.., total_cc-1)
			call recursively MBST on adjC:

			MBST(adjC, adjD);

			When call returns,
			Add edges of adjB (use original names)
			into adjD
			*****************************************/
			vector<list<edge> > adjC(total_cc);
			std::vector<int> w;
			select_gratest(adjA,adjC,median_weight,cc,w);
			MBST(adjC, adjD);
		//	cout << " size: " << adjB.size() << endl;
				for(int i=0;i<adjB.size();i++){
					for (std::list<edge>::iterator it=adjB[i].begin(); it != adjB[i].end(); ++it){
						if(it->weight_to!=-1){
						addEdge(adjD,it->from,it->to,it->weight,it->from,it->to);
					 }
					}
				}
			//return;
		}//else not connected
	}//MBST recursive


int main(){
	int vertices,size,from,to,weight;
	cin >> vertices >> size;
	vector<list<edge> > adjA(vertices);
	vector<list<edge> > adjD(vertices);
	for(int i=0;i<size;i++){
		cin>> from>> to >> weight;
		addEdge(adjA,from,to,weight,from,to);
	}
	MBST(adjA,adjD);
	int max_weight=0;
	for(int i=0;i<adjD.size();i++){
		for (std::list<edge>::iterator it=adjD[i].begin(); it != adjD[i].end(); ++it){
			if(it->weight_to!=-1){
				if(it->weight>max_weight){
					max_weight=it->weight;
				}
			}
		}
	}
 cout << max_weight << endl;
	return 0;
}
