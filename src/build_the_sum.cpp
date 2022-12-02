#include <iostream>

using namespace std;

void solve(){
  
  int n, tmp, sum=0;
  cin >> n;
  
  for (int i=0; i<n; ++i){
    cin >> tmp;
    sum += tmp;
  }
  
  cout << sum << endl;
}

int main(){
  int t;
  cin >> t;
  
  for (int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
