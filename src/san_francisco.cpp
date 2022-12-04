#include <iostream>
#include <vector>

using namespace std;

long rec(vector<vector<long>> &memo, vector<vector<pair<int,int>>> &e, int p, int k){
  
  if(k==0){
    return 0L;
  }
  
  if(memo[p][k] != -1L){
    return memo[p][k];
  }
  
  long res = 0;
  
  if (e[p].size() == 0){
    res = rec(memo, e, 0, k);
  } else {
  
    for (auto x : e[p]){
      int v = x.first;
      long val = rec(memo, e, v, k-1) + x.second;
      if (val > res){
        res = val;
      }
    }
  }
  
  memo[p][k] = res;
  return res;
  
}

void solve(){
  
  int n, m, k, u, v, p;
  long x;
  
  cin >> n >> m >> x >> k;
  
  vector<vector<pair<int,int>>> e(n, vector<pair<int,int>>(0));
  
  for(int i=0; i<m; ++i){
    cin >> u >> v >> p;
    
    e[u].push_back(pair<int,int>(v,p));
  }
  
  vector<vector<long>> memo(n, vector<long>(k+1, -1L));
  
  long val = rec(memo, e, 0, k);
  
  if (val < x){
    cout << "Impossible" << endl;
  } else {
    for(int i=0; i<=k; ++i){
      if (rec(memo, e, 0, i) >= x){
        cout << i << endl;
        break;
      }
    }
  }
  
}

int main(){
  int t;
  cin >> t;
  
  for(int i=0; i<t; ++i){
    solve();
  }
  
  return 0;
}
