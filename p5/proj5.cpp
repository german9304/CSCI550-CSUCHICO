/*****
German Razo Rodriguez
CSCI550
Proj5 ,
suffix_array
*****/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void rename_string_int(int arr[], string in,vector<int> & T,
  int & alphsize){

  for(unsigned int i = 0;  i < in.length(); i++){
    int a = in[i];
    arr[a]++;
  }
  int rename_index=1;
  for(int i = 0; i < 256; i++){
    if(arr[i]>0){
      arr[i] = rename_index;
      rename_index++;
      alphsize++;
    }
  }
  alphsize++;
  for(unsigned int i = 0; i < in.length(); i++){
    char a = in[i];
    int b = a;
    T[i] = arr[b];
  }
  int m_last = T.size()-1;
  T[m_last]=0;
}
void arrays_A_C_B(vector<int> & T, vector<int> & A, vector<int> & B,
   vector<int> & C)
{
	 for(unsigned int i = 0; i < T.size(); i++){
		 int index = T[i];
		 A[index]++;
	 }
	 for(unsigned int i = 1; i < A.size(); i++){
		 C[i] = C[i-1] + A[i-1];
	 }
	 for(unsigned int i = 1; i < B.size(); i++){
		 B[i] = B[i-1] + A[i];
	 }
}
void array_t_calc(vector<int> & T, vector<int> & t, vector<int> & SA,
	vector<int> & B, vector<int> & lms){
  vector<int> c_b = B;
  int end = T.size()-1;
  t[end]=1;
  // L type is 0
  // S type is 1
  /*
  If T[i+1] >  T[i]
  t[i] is L type
  */
  for(int i = end-1;i >= 0; i--){
    if(T[i] > T[i+1]){
      t[i] = 0;
      if(T[i+1] == 0 && i+1 == end){
        SA[0] = i + 1;
        lms[end]=1;
      }else if(t[i+1] == 1){
        SA[c_b[T[i+1]]] = i + 1;
        lms[i+1]=1;
        if(c_b[T[i+1]]!=0){
          c_b[T[i+1]]--;
        }
      }
      /*
      If T[i+1] <  T[i]
      t[i] is S type
      */
    }else if(T[i] < T[i+1]){
      t[i] = 1;
    }else{
      if(T[i] == T[i + 1]){
        /*
        If T[i+1] == T[i]
        If T[i+1] its L type
        then t[i] is also L type
        else
        t[i] is S type
        */
        if(t[i+1] == 0){
          t[i] = 0;
        }else{
          t[i] = 1;
        }
      }
    }
  }
}
void induce_sort_suffixes(vector<int> & SA, vector<int> & B,
    vector<int> & t, vector<int> & T, vector<int> & end_c){
  /*
  Left-Right SA scanning
  */
  for(unsigned int i = 0; i < SA.size(); i++){
    int p = SA[i];
    if(p!=-1){
      if(p==0){
      }else{
        if(!t[p-1]){
          SA[B[T[p-1]]]= p-1;
          B[T[p-1]]++;
        }
      }
    }
  }
  /*
  Right-Left SA scanning
  */
  int end = SA.size()-1;
  for(int i = end;i>=0; i--){
    int p = SA[i];
    if(p > 0){
      if(t[p-1]){
        SA[end_c[T[p-1]]]= p-1;
        end_c[T[p-1]]--;
      }
    }
  }
}
void bit_bool_array(vector<int> & lms, vector<int> & l, vector<int> & SA){
  for(unsigned int i = 0; i < SA.size(); i++){
    if(SA[i] != -1){
    if(lms[SA[i]] == 1){
      l[i] = 1;
    }
   }
  }
}
bool cmpr_sbstrs(vector<int> & T, vector<int> & t, int prev, int next,vector<int> & lms){
  vector<int> str1;
  vector<int> str2;
  unsigned int prv = prev;
  for(unsigned int i = prev; i < t.size(); i++){
    str1.push_back(T[i]);
    if(lms[i] && i!=prv){
      break;
    }
  }
  unsigned int nxt = next;
  for(unsigned int i = next; i < t.size(); i++){
    str2.push_back(T[i]);
    if(lms[i] && i!=nxt){
      break;
    }
  }
  if(str1.size() != str2.size()){
    str2.clear();
    str1.clear();
    return false;
  }else {
    for(int i = 0; i < (int) str1.size(); i++){
      if(str1[i] != str2[i]){
        str2.clear();
        str1.clear();
        return false;
      }
    }

  }
  str2.clear();
  str1.clear();
  return true;
}
void n_array_calc(vector<int> & N, vector<int> & SA, vector<int> & l,
 vector<int> & T,  vector<int> & t, vector<int> & t1, vector<int> & lms,
 int & largest){
   int prev = SA[0];
   N[prev] = 0;
   for(int i = 1; i < (int) SA.size(); i++){
     if(l[i]){
       bool str_s = cmpr_sbstrs(T,t,prev,SA[i],lms);
       if(str_s){
         N[SA[i]] = N[prev];
       }else{
         N[SA[i]] = N[prev]+1;
       }
       prev = SA[i];
     }
     }
   for(unsigned int i = 0; i < N.size(); i++){
     if(N[i]!=-1){
       if(largest < N[i]){
         largest = N[i];
       }
       t1.push_back(N[i]);
     }
   }
}

void SAIS(vector<int> & T, vector<int> & SA, int alphabetSize,int iter)
{
  int size = T.size();
  if(size == alphabetSize){
  	 for(unsigned int i = 0; i < T.size(); i++){
         SA[T[i]]=i;
       }
    return ;
  }
	vector<int> A(alphabetSize, 0); // Occurrances of characters
	vector<int> C(alphabetSize, 0); // characters smaller than c, head bucket
	vector<int> B(alphabetSize, 0); // End of bucket
  vector<int> lms(size, 0);
  vector<int> l(size, 0);
	vector<int> t(size, 0);
  arrays_A_C_B(T, A, B, C);
  array_t_calc(T, t, SA, B, lms);
	vector<int> head_c = C;
  vector<int> copy_head_b = C;
  vector<int> end_c = B;
  vector<int> copy_end_b = B;
  induce_sort_suffixes(SA, head_c, t, T, end_c);
  bit_bool_array(lms,l,SA); //bool array substrings
  vector<int> N(T.size(), -1);
  vector<int> T1;
  int largest = 0;
  n_array_calc(N,SA,l,T,t,T1,lms,largest);
  vector<int> SA1(T1.size(), -1);
  SAIS(T1, SA1, largest + 1, iter+1);
  T1.clear();
  for(unsigned int i = 0; i < lms.size(); i++){
    if(lms[i]){
      T1.push_back(i);
    }
  }
  vector<int> copy2_endb = copy_end_b;
  vector<int> SA_c(SA.size(),-1);
  vector<bool> new_lms(T.size());
  int end = SA1.size()-1;
  for(int i=end ; i>=0 ;i--){
    int p = SA1[i];
    SA_c[copy_end_b[T[T1[p]]]] = T1[p];
    new_lms[copy_end_b[T[T1[p]]]]=1;
    copy_end_b[T[T1[p]]]--;
  }
  /***
   Right Left
  ***/
  for(unsigned int i = 0; i < SA_c.size(); i++){
    int p = SA_c[i];
    if(p!=-1){
      if(p == 0){
      }else if(!t[p-1]){
        SA_c[copy_head_b[T[p-1]]] = p-1;
        copy_head_b[T[p-1]]++;
      }
    }
  }
  /***
   Left To Right
  ***/
  int end_i = SA_c.size()-1;
  for(int i = end_i ;i>=0; i--){
    int p = SA_c[i];
    if(t[p-1]){
      SA_c[copy2_endb[T[p-1]]]= p-1;
        copy2_endb[T[p-1]]--;
    }
  }
  SA = SA_c;
}

int main(){
	string in;
	string cat;
	getline (cin, in);
	while(!cin.eof()){
	cat += in;
	getline(cin, in);
  }
	int str_length= cat.length();
  int arr[256];
  for(int i = 0; i < 256; i++){
    arr[i] = 0;
  }
	vector<int> T(str_length+1, -1);
	vector<int> SA(str_length+1, -1);
	int alphsize = 0;
	int iter = 1;
  rename_string_int(arr, cat, T,alphsize);
	SAIS(T, SA, alphsize, iter);
  for(int i = 0; i < (int) SA.size(); i++){
    if(SA[i]!=0){
    cout <<cat[SA[i]-1];
   }
  }
  cout <<endl;
	return 0;
}
