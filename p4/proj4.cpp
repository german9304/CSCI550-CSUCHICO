#include <iostream>
#include <string>
using namespace std;

int main(){
	string in;
	string cat;
	getline (cin, in);
	while(!cin.eof()){
	cat+=in;
	getline(cin, in);
  }
	int count[256]={0};
	for(int i=0;i<cat.length();i++){
		int a = cat[i];
		count[a]++;
	}
  for(int i=0;i<256;i++){
		if(count[i]>0){
	    char a = i;
			cout <<a << " " << count[i] << " " <<endl;
		}
	}


	return 0;
}
