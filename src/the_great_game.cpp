#include <iostream>
#include <vector>
#include <map>

using namespace std;

int rec(int n, map<int, vector<int>> &e, vector<vector<int>> &memo, int r, int p){
  
  if (r == n-1){
    return 0;
  }
  
  if (memo[r][p] != 0){
    return memo[r][p];
  }
  
  int res = 0;
  
  if (p==0){
    res = ~(1<<31);
    for(int x : e[r]){
      int val = rec(n, e, memo, x, 1)+1;
      if (val < res){
        res = val;
      }
    }
  } else {
    for(int x : e[r]){
      int val = rec(n, e, memo, x, 0)+1;
      if (val > res){
        res = val;
      }
    }
  }
  
  memo[r][p] = res;
  return res;
  
}

void solve(){
  
  int n, m, r, b, u, v;
  
  cin >> n >> m;
  cin >> r >> b;
  
  map<int, vector<int>> e;
  
  for(int i=0; i<n; ++i){
    e[i] = vector<int>(0,0);
  }
  
  for(int i=0; i<m; ++i){
    cin >> u >> v;
    
    e[u-1].push_back(v-1);
  }
  
  vector<vector<int>> memo(n,vector<int>(2, 0));
  
  int res1 = 2*rec(n, e, memo, r-1, 0);
  int res2 = 2*rec(n, e, memo, b-1, 0);
  
  if(res1%4==2){
    res1--;
  }
  
  if (res2%4==0){
    res2--;
  }
  
  cout << (res1 <= res2 ? 0 : 1) << endl;

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
