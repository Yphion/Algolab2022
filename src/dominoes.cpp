#include <iostream>
#include <limits>


using namespace std;

void solve(){
  
  int n, tmp, res=0, mx=0;
  
  cin >> n;
  
  for (int i=0; i<n; ++i){
    cin >> tmp;
    res++;
    if (tmp == 1 && mx==i){
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      break; 
    }
    
    if (i + tmp - 1 > mx){
      mx = i + tmp - 1;
    }
    
  }
  
  
  cout << res << endl;
}

int main(){
  
  int t;
  cin >> t;
  
  for (int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
  
}
