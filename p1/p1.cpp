
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
using namespace std;

class edge{
public:
	int to;
	int from;
	int parent_vertex;
	int weight_to;
	int weight_from;
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

void addEdge(vector<list<edge> > &adjA,int from,int to,int weight){
	int size=adjA.size();
	edge aedge_from;
	aedge_from.to=to;
	aedge_from.from=-1;
	aedge_from.weight_from=-1;
	aedge_from.weight_to=weight;
	aedge_from.parent_vertex=from;
	adjA[from].push_back(aedge_from);
	edge aedge_to;
	aedge_to.from=from;
	aedge_to.to=-1;
	aedge_to.weight_to=-1;
	aedge_to.weight_from=weight;
	aedge_to.parent_vertex=to;
	adjA[to].push_back(aedge_to);

}

void collect_weights(vector<list<edge> > &adjA, vector<int> & weights){
	int index=0;
	for(int i=0;i<adjA.size();i++){
		for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it){
			if(it->weight_to!=-1){
				weights[index]=it->weight_to;
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
				if(it->to!=-1 || it->weight_to!=-1){
					if(it->weight_to<=median_weight){
						 temp=true;
          addEdge(adjB,i,it->to,it->weight_to);
					}
				}
				if(it->from!=-1 || it->weight_from!=-1){
					if(it->weight_from<=median_weight){
						temp=true;
					}
				}
			}
			if(temp){
				 avert.push_back(i);
				temp=false;
			}
		}
    for(int i=0;i<adjB.size();i++){
			if(adjB[i].size()==0){
				adjB.erase (adjB.begin()+i);
			}
		}

}
void connected(vector<list<edge> > &adjB, vector<short int > cc){

}

/*
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

*/

struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;


int main(){

 //vector<int> weights(m, 0);
 int vertices,size,from,to,weight;
 cin >> vertices >> size;
  vector<list<edge> > adjA(vertices);
  for(int i=0;i<size;i++){
    cin>> from>> to >> weight;
		addEdge(adjA,from,to,weight);
	}

/*
	cout <<" size " <<  adjA.size() << endl;
	for(int i=0;i<adjA.size();i++){
		cout << "-----------" << endl;
		cout << " vertex " << i << endl;
		 for (std::list<edge>::iterator it=adjA[i].begin(); it != adjA[i].end(); ++it){
			if(it->to!=-1 || it->weight_to!=-1){
			cout << "vertex to: " <<  it->to <<  " weight to: " << it->weight_to << endl;
		 }
		 if(it->from!=-1 || it->weight_from!=-1){
			 cout << "vertex from: " <<  it->from <<  " weight from: " << it->weight_from << endl;
		 }
	}
	cout << endl;
	cout << "-----------" << endl;
}
*/


  int m = 0;
	int s = adjA.size();

	for(int i = 0; i < s; i++){
					m += adjA[i].size();
	}
	m = m >> 1;
 vector<int> weights(m);
 collect_weights(adjA, weights);
 std::sort (weights.begin(), weights.end(), myobject);


   int k = m >> 1;//divide by 2
	 if(m % 2 == 0)
					 k--;
	cout << "median: ";
  int median_weight = select(weights, 0, m-1,k);

	cout << median_weight << endl;
	vector< list<edge> > adjB(adjA.size());
	select_smallest(adjA,adjB,median_weight);

  //vector< list<edge> > adjB(adjA.size());
  //select_smallest(adjA, adjB, median_weight);

	return 0;
}
