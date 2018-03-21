#include <iostream>
#include <vector>
using namespace std;
class vertex{
public:
	int from;
	int to;
	int weight;
};
void addEdge(vector<list<int> > & alist , int from,int to,int w){

}
int main(){

  int red_nova_stations;
	vector< list<int> > red_nova_list(red_nova_stations);
	cin>>red_nova_stations;
	for(int i=0;i<red_nova_stations;i++){
		cin>> from>> to >> weight;
    addEdge(red_nova_list,from,to,weight);
	}
	int star_trace_stations;
	vector< list<int> > star_trace_list(star_trace_stations);
	cin>>star_trace_stations;
	for(int i=0;i<star_trace_stations;i++){
		cin>> from>> to >> weight;
    addEdge(star_trace_list,from,to,weight);
	}
	return 0;
}
