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
  int rename_index=1;

	for(int i=0;i<256;i++){
		char a = i;
			if(arr[i]>0){
			//	cout  << " " <<a << " " << 	arr[i] <<" "<<endl;
			}
	}
	cout <<endl;
	for(int i=0;i<256;i++){
		char a = i;
			if(arr[i]>0){
				occurances.push_back(arr[i]);
				//arr[i]
				arr[i]=rename_index;
			//	cout  << " " <<a << " " << 	arr[i] <<" "<<endl;
				rename_index++;
		}
	}
	cout <<endl;
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
	for(int i=0;i<end_bucket.size();i++){
			cout <<  end_bucket[i]  << endl;
	}
	/*
	int rename_index=1;
  for(int i=0;i<256;i++){
		if(occurances[i]>0){
			char a = i;
			new_intername[i]=rename_index++;
			cout <<rename_index << " " << a << " " << new_intername[i] << " " <<endl;
		}
	}
	*/
	/*
  for(int i=0;i<256;i++){
		if(arr[i]>0){
			char a = i;
			cout << a << " " << arr[i] <<endl;
		//	cout <<a << " " << cc[i] << " " <<endl;
		}
	}
	*/

}
void substring_lms(string in){
	in+="$";
	cout <<"sring: " << in <<endl;
}
void type_suffix_array(int arr[],vector<char> & type_suffix,string in,
	vector<int> & suffix_array,vector<int> & end_bucket){
	int end = in.length()-1;
	//cout <<"size: " << type_suffix.size() <<endl;
	type_suffix[end]='s';
	for(int i=end-1;i>=0;i--){
		/*
		int  b = in[i+1];
		cout << "char: " << in[i] << " element: " <<arr[b] <<" "
		<< " end_bucket " <<end_bucket[arr[b]] <<endl;
		*/
		if(in[i]>in[i+1]){
			type_suffix[i]='l';
			if(in[(i)+1]=='$'){
				suffix_array[0]=14;
				end_bucket[0]=-1;
			}else{
				if(type_suffix[i+1]=='s'){
					//suffix_array[0]=14;
					int  b = in[i+1];
					int index = end_bucket[arr[b]];
					// cout << i << " " << i+1 <<endl;
					suffix_array[index]= i+1;
					end_bucket[arr[b]]--;
					// cout << i << " " << in[i] << " " << in[i+1] <<" " <<  end_bucket[arr[b]]<<endl;
				}
			}
		}else if(in[i]<in[i+1]){
			type_suffix[i]='s';
		}else{
			if(type_suffix[i+1]=='l'){
				//cout <<"equal" << in[i+1] << " " <<in[i] <<endl;
				type_suffix[i]='l';
			}else{
				type_suffix[i]='s';
			}
		}
	//	cout <<"(i) " << in[i] << " (i + 1) " << in[i+1] << "  *  ";
	}
	/*
	cout <<endl;
	for(int i=end-1;i>=0;i--){
		cout <<"(i) " << in[i] << " (i + 1) " << in[i+1] << "  *  ";
	}
	cout <<endl;
	*/

	cout << in << " "<<endl;
	for(int i=0;i<type_suffix.size();i++){
		cout <<type_suffix[i];
	}
	cout <<endl;
	cout <<"------" <<endl;
	for(int i=0;i<suffix_array.size();i++){
		cout <<suffix_array[i] << " ";
	}

	//for(int i=0;i<end_bucket.size())
	//cout <<endl;
}
int main(){
	string in;
	string cat;
	getline (cin, in);
	while(!cin.eof()){
	cat+=in;
	getline(cin, in);
  }
	int str_length= cat.length();
  int arr[256]={0};
	vector<int> newinteger;
	vector<int> occurances;
	vector<int> smaller_characters;
	vector<int> end_bucket;
	vector<char> t_array(str_length+1,'\0');
	count(arr,str_length,cat,newinteger,occurances,smaller_characters
	,end_bucket);
	string str_final = 	cat+="$";
	vector<int> suffix_array(str_final.length(),0);
  type_suffix_array(arr,t_array,str_final,suffix_array,end_bucket);


	return 0;
}
