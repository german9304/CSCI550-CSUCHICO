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
		char a = i;
			if(arr[i]>0){
			cout  << " " <<a << " " << 	arr[i] <<" "<<endl;
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
void type_suffix_array(int arr[],vector<int> & type_suffix,string in,
	vector<int> & suffix_array,vector<int> & end_bucket,vector<int> & lms){
  vector<int> copy_end_bucket = end_bucket;
	int end = in.length()-1;
	//cout <<"size: " << type_suffix.size() <<endl;
	type_suffix[end]=1;
  lms[end]=1;
	for(int i=end-1;i>=0;i--){
		/*
		int  b = in[i+1];
		cout << "char: " << in[i] << " element: " <<arr[b] <<" "
		<< " end_bucket " <<end_bucket[arr[b]] <<endl;
		*/
		if(in[i]>in[i+1]){
			type_suffix[i]=0;
			if(in[(i)+1]=='$'){
				suffix_array[0]=end;
			//	end_bucket[0]=-1;
			}else{
				if(type_suffix[i+1]==1){
					//suffix_array[0]=14;
					int  b = in[i+1];
					int index = copy_end_bucket[arr[b]];
					// cout << i << " " << i+1 <<endl;
					suffix_array[index]= i+1;
					copy_end_bucket[arr[b]]--;
          lms[suffix_array[index]]=1;
					// cout << i << " " << in[i] << " " << in[i+1] <<" " <<  end_bucket[arr[b]]<<endl;
				}
			}
		}else if(in[i]<in[i+1]){
			type_suffix[i]=1;
		}else{
			if(type_suffix[i+1]==0){
				//cout <<"equal" << in[i+1] << " " <<in[i] <<endl;
				type_suffix[i]=0;
			}else{
				type_suffix[i]=1;
			}
		}
	//	cout <<"(i) " << in[i] << " (i + 1) " << in[i+1] << "  *  ";
	}
  //lms = suffix_array;
/*
	cout <<endl;
	for(int i=end-1;i>=0;i--){
		cout <<"(i) " << in[i] << " (i + 1) " << in[i+1] << "  *  ";
	}
	cout <<endl;


	cout << in << " "<<endl;
	for(int i=0;i<type_suffix.size();i++){
		cout <<type_suffix[i];
	}
  */
	//cout <<endl;
  /*
	cout <<"------" <<endl;
	for(int i=0;i<suffix_array.size();i++){
		cout <<suffix_array[i] << " ";
	}
  */

  /*
  cout <<endl;
	cout <<"copy_end_bucket" <<endl;
	for(int i=0;i<copy_end_bucket.size();i++){
		cout <<copy_end_bucket[i] << " ";
	}
  */
	//for(int i=0;i<end_bucket.size())
	//cout <<endl;
}
void induce_sort(int arr[],vector<int> & suffix_array,vector<int> & t_array,
string in,vector<int> & head_bucket,vector<int> & end_bucket,
vector<bool> & bool_array,vector<int> & lms){
  vector<int> copy_end_bucket = end_bucket;
  vector<int> copy_head_bucket = head_bucket;
  //cout <<endl;
  /*
	cout << "head_bucket" <<endl;
    for(int i=0;i<head_bucket.size();i++){
      cout << head_bucket[i] <<" ";
    }
    cout <<endl;
      for(int i=0;i<t_array.size();i++){
        cout << t_array[i] <<" ";
      }
      */
	/*
  for(int i=0;i<in.length();i++){
		char a = in[i];
		int b = a;
		cout <<a << " " << b << " " << arr[b] << " head: " <<  head_bucket[arr[b]]<<endl;
	}

  cout <<endl;
  cout <<"t_array" <<endl
  */
  /*
  cout <<"t_array" <<endl;
  for(int i=0;i<t_array.size();i++){
    cout << t_array[i] <<" ";
  }
  */
  //cout <<endl;
  //cout << "chars" <<endl;
  int size = suffix_array.size();
  /*
   Left-to-Right scanning
  */
  //cout << "head end_bucket"<<endl;
	for(int i=0;i<suffix_array.size();i++){
  		int p = suffix_array[i];
      if(p!=-1){
        if(p==0){
          //cout <<"0" <<endl;
          char a = in[size-1];
        //  cout << "a " << a << " "<<endl;
          if(suffix_array[0]==-1){
              suffix_array[0]=0;
          }
          //cout << "left right" <<endl;
           //cout << in[i] <<endl;
        }else{
        if(!t_array[p-1]){

        //  cout << t_array[p-1] <<" ";

          char a = in[p-1];
        //  cout <<"char: " << a <<" " << p <<endl;
          int b = a;
          int index = arr[b];
          //cout <<p-1 << " " << i << " " << a << " " <<  index <<endl;
          //if(p==0){
          int index_head = copy_head_bucket[index];
          //cout << index_head  <<" " <<copy_head_bucket[index] <<endl;

          //cout << suffix_array[index_head] <<endl;
          if(suffix_array[index_head]==-1){
          suffix_array[index_head] = p-1;
          copy_head_bucket[index]++;
        }
          //break;
        //  cout <<a <<endl;
        //  cout << "head: " << copy_head_bucket[index] <<endl;
        }
      }
    }
  }
  /*
  cout << "----------"<<endl;
  cout <<endl;
  cout << "new suffix_array left right" <<endl;
  for(int i=0;i<suffix_array.size();i++){
    cout << suffix_array[i] <<" ";
  }
  cout <<endl;
*/
  /*
    Right-to-Left scanning
  */
  copy_end_bucket = end_bucket;
  //cout << "right to left " <<endl;
  int end = suffix_array.size();
	for(int i=end-1;i>=0;i--){
  //cout << suffix_array[i] << " ";

    int p = suffix_array[i];
    if(p==0){
      // cout << in[i] <<endl;
    }else{
     if(t_array[p-1]){
       char a = in[p-1];
       int b = a;
      // cout << a <<endl;
       int index = arr[b];
       int end_bucket_index= copy_end_bucket[index];
       //bool_array
        //suffix_array[i]
      //  cout << t_array[p-1] <<endl;
    //   cout << "end: " << copy_end_bucket[index] << " p: " << p-1 << endl;
       suffix_array[end_bucket_index]=p-1;
       copy_end_bucket[index]--;

      // break;
       }
     }
    //cout << t_array[p-1] << " ";
  }

  for(int i=0;i<bool_array.size();i++){
   if(lms[suffix_array[i]]){
     bool_array[i]=1;
   }
  }

  cout <<endl;

    cout << "new suffix_array right left" <<endl;
    for(int i=0;i<suffix_array.size();i++){
      cout << suffix_array[i] <<" ";
    }
    cout <<endl;

    cout << "bool_array" <<endl;
    for(int i=0;i<bool_array.size();i++){
      cout << bool_array[i] <<" ";
    }

  cout <<endl;

}
bool compare_substrings(string one,string two){
      if(one==two){
        return true;
      }
      return false;
}

bool myfunction (int i,int j) { return (i<j); }

void lms_named(vector<int> & suffix_array,vector<bool> & bool_array,
string str,vector<int> & n_array,vector<int> & t_array){
  int prev = suffix_array[0];
  cout << "char in lms named" <<endl;
  cout << str[prev] <<endl;
  cout <<"suffix_array" <<endl;
  for(int i=0;i<suffix_array.size();i++){
    cout << suffix_array[i] << " ";
  }
  cout <<"bool_array" <<endl;
  for(int i=0;i<suffix_array.size();i++){
    cout << bool_array[i] << " ";
  }
  cout <<endl;
  char str_prev = str[prev];
  vector<int> sorted_positions;
  vector<int> positions;
  for(int i=0;i<suffix_array.size();i++){
    if(bool_array[i]){
      positions.push_back(suffix_array[i]);
      sorted_positions.push_back(suffix_array[i]);
    // cout << "from: " <<suffix_array[i] << " " << "to: " << prev << endl;
    }
  }
  cout << "positions" <<endl;

  std::sort (sorted_positions.begin(), sorted_positions.end(), myfunction);
  vector<string> substrings(str.length(),"");
  string cat ="";
  for(int i=0;i<sorted_positions.size();i++){
  //  cout << positions[i] << " ";
    int from = sorted_positions[i];
    int to = sorted_positions[i+1];
    if(i+1==positions.size()){
      to = sorted_positions[i] +1;
    }
    for(int i=from;i<to+1;i++){
      cat+=str[i];
    }
    substrings[from]=cat;
      cat="";
  }
 /*
  cout << "substrings" <<endl;
  for(int i=0;i<substrings.size();i++){
    cout << i << " " <<substrings[i] << endl;

  }
  */


//  cout << "compare" <<endl;
  int sum=0;
  n_array[str.length()-1]=0;
  for(int i=0;i<positions.size()-1;i++){
       //cout << substrings[positions[i]] << " " << substrings[positions[i+1]] <<endl;
      if(compare_substrings(substrings[positions[i]],substrings[positions[i+1]])){
       n_array[positions[i+1]]=sum;
      }else{
        sum++;
        n_array[positions[i+1]]=sum;
      }

  }
  cout << "N array" <<endl;
  for(int i=0;i<n_array.size();i++){
    //cout << n_array[i] <<" ";
    if(n_array[i]!=-1){
      cout <<n_array[i] <<" ";
       t_array.push_back(n_array[i]);
    }
  }
  cout <<endl;

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
	vector<int> head_bucket;
	vector<int> end_bucket;
	vector<int> t_array(str_length+1,-1);
	count(arr,str_length,cat,newinteger,occurances,head_bucket
	,end_bucket);
  cout << "end_bucket" <<endl;
  for(int i=0;i<end_bucket.size();i++){
    cout << end_bucket[i] << " ";
  }
  cout <<endl;
	string str_final = 	cat+="$";
	vector<int> suffix_array(str_final.length(),-1);
  vector<bool>  bool_array(str_final.length(),0);
  vector<int> lms(str_final.length(),0);
  vector<int> n_array(str_final.length(),-1);
  vector<int> t1_array;
  vector<int> s1_array;
  type_suffix_array(arr,t_array,str_final,suffix_array,end_bucket,
  lms);
  /*
  cout << "lms"<<endl;
  for(int i=0;i<lms.size();i++){
    cout << lms[i] <<" ";
  }
  cout << "t_array"<<endl;
  for(int i=0;i<t_array.size();i++){
    cout << t_array[i] <<" ";
  }
  cout <<endl;
  */
	induce_sort(arr,suffix_array,t_array,str_final,head_bucket,end_bucket,
  bool_array,lms);
	cout <<endl;
  lms_named(suffix_array,bool_array,str_final, n_array,t1_array);
  vector<int> s1_array(t1_array.size(),-1);
  cout << "t_array" <<endl;
  for(int i=0;i<t1_array.size();i++){
    cout << t1_array[i] << endl;
  }

	return 0;
}
