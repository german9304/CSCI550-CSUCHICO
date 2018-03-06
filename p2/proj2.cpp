/******
Project 2
Palindrome paritioning
German Razo Rodriguez
CSCI550
*******/
#include <iostream>
#include <vector>
using namespace std;

/*******
Palindrome matrix
*******/
void create_matrix(int string_size,vector<vector<int> > & P_table,string m_s){
	int i=0;
  int j=0;
	vector<bool> visited(string_size,false);
	for(int s_length=0;s_length<string_size;s_length++){
		for( i=0;i<string_size;i++){
			if(!visited[i]){
				for( j=i+s_length;j<i+s_length+1;j++){
					if(s_length==0){
						P_table[i][j]=1;
					}else if(s_length==1){
						if(m_s[j]==m_s[i]){
							P_table[i][j]=1;
						}else{
							P_table[i][j]=0;
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
/*******
minimum cuts table
*******/
void cuts_table(vector<vector<int> > & P_table,vector<int>
	& cuts,int string_size,vector<int> & B){
	for(int i=0;i<string_size;i++){
		if(P_table[0][i]==1){
			cuts[i]=0;
			B[i]=0;
		}else{
			int m = cuts[i];
			for(int j=0;j<i;j++){
				if(P_table[j+1][i]){
					if(cuts[j]+1<m){
						m=cuts[j]+1;
						B[i]=j+1;
					}
					cuts[i]=min(cuts[j]+1,cuts[i]);
				}
			}
		}
	}
}
/*******
backtracking table
*******/
void backtracking(vector<int> & B,int index,string in){
	if(index==-1){
		return;
	}
	backtracking(B,B[index]-1,in);
	for(int a=B[index];a<index+1;a++){
		cout << in[a];
	}
	cout <<endl;
}
int main(){
  string m_s;
	cin>>m_s;
	int string_size= m_s.length();
	vector<vector<int> > P_table(string_size,vector<int>(string_size,0));
	create_matrix(string_size,P_table,m_s);
	vector<int> cuts(string_size,1000);
	vector<int> B(string_size);
  cuts_table(P_table,cuts,string_size,B);
  backtracking(B,string_size-1,m_s);
	return 0;
}
