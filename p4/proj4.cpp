#include <iostream>
#include <string>
#include <vector>
using namespace std;

void count(vector<int> & count_c,int str_length,string cat,vector<int> & new_intername){

	for(int i=0;i<str_length;i++){
		int a = cat[i];
		count_c[a]++;
	}
	int rename_index=1;
  for(int i=0;i<256;i++){
		if(count_c[i]>0){
			char a = i;
			new_intername[i]=rename_index++;
			cout <<rename_index << " " << a << " " << new_intername[i] << " " <<endl;
		}
	}
  for(int i=0;i<256;i++){
		if(count_c[i]>0){
			cout << new_intername[i] <<endl;
		//	cout <<a << " " << cc[i] << " " <<endl;
		}
	}
}
void substring_lms(string in){
	in+="$";
	cout <<"sring: " << in <<endl;
}
int main(){
	string in;
	string cat;
	getline (cin, in);
	while(!cin.eof()){
	cat+=in;
	getline(cin, in);
  }

	vector<int> cc(256,0);
	vector<int> newinteger(256,0);
	vector<int> lms(256,0);
	int str_length= cat.length();
	count(cc,str_length,cat,newinteger);



	return 0;
}
