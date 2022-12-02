#include <iostream>
#include <vector>

using namespace std;

void solve(){
  
  int n;
  cin >> n;
  
  int o=0, e=0, sum=0;
  
  for (int i=0; i<n; ++i){
    
    int x;
    cin >> x;
    if (x%2 == 0){
      e = e + 1;
      o = o;
    } else {
      x = e;
      e = o;
      o = x + 1;
    }
    sum += e;
    
  }
  
  cout << sum << endl;
  
}

int main(){
  int t;
  cin >> t;
  
  for (int i=0; i<t; ++i){
    solve();
  }
    
}










