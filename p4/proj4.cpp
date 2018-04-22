/*****
German Razo Rodriguez
CSCI550
Proj4 ,
suffix_array
*****/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
		//char a = i;
			if(arr[i]>0){
				occurances.push_back(arr[i]);
				arr[i]=rename_index;
				rename_index++;
		}
	}
	int count = 0;
	int count_end = 0;
  for(unsigned int i= 1;i<occurances.size();i++){
		 count = occurances[i-1] + smaller_characters[i-1];
		 smaller_characters.push_back(count);
		 count_end=  end_bucket[i-1] + occurances[i];
		 end_bucket.push_back(count_end);
	}
}
/***
function to get type array LS OR MLS
***/
void type_suffix_array(int arr[],vector<int> & type_suffix,string in,
	vector<int> & suffix_array,vector<int> & end_bucket,vector<int> & lms){
  vector<int> copy_end_bucket = end_bucket;
	int end = in.length()-1;
	type_suffix[end]=1;
  lms[end]=1;
	for(int i=end-1;i>=0;i--){
		if(in[i]>in[i+1]){
			type_suffix[i]=0;
			if(in[(i)+1]=='$' && i+1==end){
        if(i+1==end){
				suffix_array[0]=end;
      }else{
        //int a = '$';
        //int index = copy_end_bucket[arr[a]];
      }
			}else{
				if(type_suffix[i+1]==1){
					int  b = in[i+1];
					int index = copy_end_bucket[arr[b]];
					suffix_array[index]= i+1;
					copy_end_bucket[arr[b]]--;
          lms[suffix_array[index]]=1;
				}
			}
		}else if(in[i]<in[i+1]){
			type_suffix[i]=1;
		}else{
			if(type_suffix[i+1]==0){
				type_suffix[i]=0;
			}else{
				type_suffix[i]=1;
			}
		}
	}
}
void induce_sort(int arr[],vector<int> & suffix_array,vector<int> & t_array,
string in,vector<int> & head_bucket,vector<int> & end_bucket,
vector<bool> & bool_array,vector<int> & lms){
  vector<int> copy_end_bucket = end_bucket;
  vector<int> copy_head_bucket = head_bucket;
  //int size = suffix_array.size();
  /*
   Left-to-Right scanning
  */
	for(unsigned int i=0;i<suffix_array.size();i++){
  		int p = suffix_array[i];
      if(p!=-1){
        if(p==0){
        //  char a = in[size-1];
          if(suffix_array[0]==-1){
              suffix_array[0]=0;
          }
        }else{
        if(!t_array[p-1]){
          char a = in[p-1];
          int b = a;
          int index = arr[b];
          int index_head = copy_head_bucket[index];
          if(suffix_array[index_head]==-1){
          suffix_array[index_head] = p-1;
          copy_head_bucket[index]++;
        }
        }
      }
    }
  }
  /*
    Right-to-Left scanning
  */
  copy_end_bucket = end_bucket;
  int end = suffix_array.size();
	for(int i=end-1;i>=0;i--){
    int p = suffix_array[i];
    if(p==0){
    }else{
     if(t_array[p-1]){
       char a = in[p-1];
       int b = a;
       int index = arr[b];
       int end_bucket_index= copy_end_bucket[index];
       suffix_array[end_bucket_index]=p-1;
       copy_end_bucket[index]--;
       }
     }
  }

  for(unsigned int i=0;i<bool_array.size();i++){
   if(lms[suffix_array[i]]){
     bool_array[i]=1;
   }
  }
}
bool compare_substrings(string one,string two){
      if(one==two){
        return true;
      }
      return false;
}

bool myfunction (int i,int j) { return (i<j); }
/***
 N -Array, subarrays strings
**/
void lms_named(vector<int> & suffix_array,vector<bool> & bool_array,
string str,vector<int> & n_array,vector<int> & t_array){
//  int prev = suffix_array[0];
  //char str_prev = str[prev];
  vector<int> sorted_positions;
  vector<int> positions;
  for(unsigned int i=0;i<suffix_array.size();i++){
    if(bool_array[i]){
      positions.push_back(suffix_array[i]);
      sorted_positions.push_back(suffix_array[i]);
    }
  }
  std::sort (sorted_positions.begin(), sorted_positions.end(), myfunction);
  vector<string> substrings(str.length(),"");
  string cat ="";
  for(unsigned int i=0;i<sorted_positions.size();i++){
    int from = sorted_positions[i];
    int to = sorted_positions[i+1];
    unsigned int pos = i+1;
    if(pos==positions.size()){
      to = sorted_positions[i] +1;
    }
    for(int i=from;i<to+1;i++){
      cat+=str[i];
    }
    substrings[from]=cat;
      cat="";
  }
  int sum=0;
  n_array[str.length()-1]=0;
  for(unsigned int i=0;i<positions.size()-1;i++){
      if(compare_substrings(substrings[positions[i]],substrings[positions[i+1]])){
       n_array[positions[i+1]]=sum;
      }else{
        sum++;
        n_array[positions[i+1]]=sum;
      }

  }
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
	vector<int> head_bucket;
	vector<int> end_bucket;
	vector<int> t_array(str_length+1,-1);
	count(arr,str_length,cat,newinteger,occurances,head_bucket
	,end_bucket);
	string str_final = 	cat+="$";
	vector<int> suffix_array(str_final.length(),-1);
  vector<bool>  bool_array(str_final.length(),0);
  vector<int> lms(str_final.length(),0);
  vector<int> n_array(str_final.length(),-1);
  vector<int> t1_array;
  type_suffix_array(arr,t_array,str_final,suffix_array,end_bucket,
  lms);
	induce_sort(arr,suffix_array,t_array,str_final,head_bucket,end_bucket,
  bool_array,lms);
  lms_named(suffix_array,bool_array,str_final, n_array,t1_array);
  vector<int> s1_array(t1_array.size(),-1);
   for(unsigned int i=0;i<suffix_array.size();i++){
     cout << suffix_array[i] << " ";
   }
   cout <<endl;
	return 0;
}
