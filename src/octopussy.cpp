#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int rec(int i, int n, vector<bool> &D){
  if (i >= n || D[i]){
    return 0;
  } 
  
  D[i] = true;
  
  return 1 + rec(2*i+1, n, D) + rec(2*i+2, n, D);
}

void solve(){
  int n, tmp;
  cin >> n;
  
  vector<pair<int,int>> T;
  T.reserve(n);
  
  vector<bool> D(n, false);
  
  for(int i=0; i<n; ++i){
    cin >> tmp;
    T.push_back(pair<int,int>(tmp, i));
  }
  
  bool res = true;
  
  sort(T.begin(), T.end());
  
  int t=0;
  
  for(int i=0; i<n; ++i){
    int val = T[i].first;
    int pos = T[i].second;
    
    t += rec(pos, n, D);
    if (t > val){
      res = false;
      break;
    }
  }
  
  cout << (res ? "yes" : "no") << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
