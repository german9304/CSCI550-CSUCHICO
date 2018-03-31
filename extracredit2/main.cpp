
#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

int max_revenue(vector<int> & prices,int length){
   int size = prices.size();
     vector<int> c(size+1,0);
     int max=0;
     for(unsigned  int i=0;i<prices.size();i++){
        int min =-1;
         for(unsigned  int j=0;j<i+1;j++){
           if(min < prices[j]+c[(i+1)-(j+1)]){
              min = prices[j]+c[(i+1)-(j+1)];
            }
         }
       c[i+1]=min;
       if(max<min){
         max = min;
       }
     }

   return max;

}
int main(){
  int length_square_land;
  cin>>length_square_land;
  vector<int> current_prices;
  for(int i=0;i<length_square_land;i++){
      int prices;
      cin>>prices;
      current_prices.push_back(prices);
  }
 int total = max_revenue(current_prices,length_square_land);
 cout << total <<endl;
    return 0;
}