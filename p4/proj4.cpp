#include <iostream>
#include <string>
#include <vector>
using namespace std;

void count(int arr[], int str_length, string cat, vector<int> & new_intername,
vector<int> & occurances, vector<int> & smaller_characters, vector<int> & end_bucket){
  occurances.push_back(1);
	end_bucket.push_back(0);
	smaller_characters.push_back(0);
	for(int i=0;i<str_length;i++){
		int a = cat[i];
		arr[a]++;
	}
	for(int i=0;i<256;i++){
			if(arr[i]>0){
				occurances.push_back(arr[i]);
		    //cout << a << " " << 	count_c[i] <<" ";
		}
	}
	int count = 0;
	int count_end = 0;
  for(int i= 1;i<occurances.size();i++){
		//count = occurances[i-1];
		 count = occurances[i-1] + smaller_characters[i-1];
		 smaller_characters.push_back(count);
		//cout << occurances[i-1] <<" " << smaller_characters[i-1]  << " ";
    //  cout << "res: " <<smaller_characters[i-1]  << " + " <<  occurances[i-1] << " = " << smaller_characters[i] << " *  " <<endl;
		 count_end=  end_bucket[i-1] + occurances[i];
		 end_bucket.push_back(count_end);
		 //cout << "----------" <<endl;
	//	 cout << "res: " <<end_bucket[i-1]  << " + " <<  occurances[i] << " = " << end_bucket[i] << " *  " <<endl;


	}
	cout <<endl;
	//cout <<endl;
	/*
	int rename_index=1;
  for(int i=0;i<256;i++){
		if(occurances[i]>0){
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
*/
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
  int arr[256]={0};
	vector<int> newinteger(256,0);
	vector<int> lms(256,0);
	vector<int> occurances;
	vector<int> smaller_characters;
	vector<int> end_bucket;
	int str_length= cat.length();
	count(arr,str_length,cat,newinteger,occurances,smaller_characters
	,end_bucket);



	return 0;
}
