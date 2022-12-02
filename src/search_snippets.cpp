#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

void solve(){
  
  int n, tmp;
  cin >> n;
  
  vector<int> m;
  m.reserve(n);
  
  for (int i=0; i<n; ++i){
    cin >> tmp;
    m.push_back(tmp);
  }
  
  map<int,int> col;
  
  for(int i=0; i<n; ++i){
    for(int j=0; j<m[i]; ++j){
      
      cin >> tmp;
      col.insert(pair<int,int>(tmp, i));
    }
  }
  
  vector<int> dp(n, -1);
  
  int opt = 1<<30;
  
  multiset<int> vals;
  
  for(int i=0; i<n; ++i){
    vals.insert(-1);
  }

  for(auto it = col.begin(); it != col.end(); ++it){
    
    int qmin = it->first;
    int qn = it->second;
    
    int old = dp[qn];
    dp[qn] = qmin;
    
    vals.erase(vals.lower_bound(old));
    vals.insert(qmin);
    
    int pmin = *vals.begin();
    
    if (pmin != -1){
      int val = qmin - pmin + 1;
      if (val < opt){
        opt = val;
      }
    }
    
  }
  
  cout << opt << endl;
  
}


int main(){
  
  std::ios_base::sync_with_stdio(false);
  
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
  
}
