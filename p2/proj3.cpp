#include <iostream>
#include <vector>
using namespace std;

void create_matrix(int string_size,vector<vector<int> > & P_table,string m_s){
	int i=0;
  int j=0;
	vector<bool> visited(string_size,false);
	for(int s_length=0;s_length<string_size;s_length++){
		//cout <<"--------------"<<endl;
		for( i=0;i<string_size;i++){
			if(!visited[i]){
				for( j=i+s_length;j<i+s_length+1;j++){
					if(s_length==0){
						P_table[i][j]=1;
					}else if(s_length==1){
						if(m_s[j]==m_s[i]){
							P_table[i][j]=1;
							//cout <<m_s[i] << " "<< m_s[j] << " "<< P_table[i][j]<<endl;
						}else{
							P_table[i][j]=0;
							 //cout <<m_s[i] << " "<< m_s[j] << " "<< P_table[i][j]<<endl;
						}
					}else{
						if(P_table[i+1][j-1] && m_s[j]==m_s[i]){
							P_table[i][j]=1;
						}else{
							P_table[i][j]=0;
						}
					}
					if(j==string_size-1){
						visited[i]=true;
						j =i+s_length+1;
					}
				}
			}
		}
	}
}
int main(){
  string m_s;
	cin>>m_s;
	int string_size= m_s.length();
	cout <<"string size: " <<string_size<<endl;
	vector<vector<int> > P_table(string_size,vector<int>(string_size,0));
	create_matrix(string_size,P_table,m_s);
  /*
	for(int i=0;i<string_size;i++){
		for(int j=0;j<string_size;j++){
			cout <<P_table[i][j]<<" ";
		}
		cout <<endl;
	}
*/
	return 0;
}
