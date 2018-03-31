
#include <iostream> 
#include <vector> 
using namespace std;

int main(){
  int length_square_land;
  cin>>length_square_land;
  vector<int> current_prices;
  for(int i=0;i<length_square_land;i++){
      int prices;
      cin>>prices;
      current_prices.push_back(prices);
  }

    return 0;
}