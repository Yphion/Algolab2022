#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void solve(){
  
  int n, l,  p;
  cin >> n;
  
  vector<pair<int,int>> V;
  V.reserve(n);
  
  for(int i=0; i<n; ++i){
    
    cin >> l >> p;
    
    V.push_back(pair<int,int>(p, l));
    
  }
  
  sort(V.begin(), V.end());
  
  int count = 0;
  int prev = -3000000;
  int cand = 3000000;
  int i=0;
  while(i <n){
    
    pair<int,int> x = V[i];
    
    int xp = x.first;
    int xl = x.second;
    
    if (cand <= xp){
      count++,
      prev = cand;
      cand = 3000000;
    } else {
      int val = xp;
      int mn = prev + xl;
      
      if(xp < prev){
        i++;
        continue;
      }
      
      if (mn > xp) {
        val = mn;
      }
      
      if (val < cand){
        cand = val;
      }
      i++;
    }
  }
  
  if (cand < 3000000){
    count ++;
  }
  
  cout << count << endl;
}

int main(){
  
  int t;
  
  cin >> t;
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
