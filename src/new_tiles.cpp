#include <iostream>
#include <vector>

using namespace std;

void solve(){
  
  int h, w;
  std::cin >> h >> w;
  
  if(h < 4 || w < 4){
    for(int i=0; i<h; ++i){
      for(int j=0; j<w; ++j){
        int q;
        cin >> q;
     }
    }
    cout << 0 << endl;
    return;
  }
  
  w -= 2;
  
  vector<vector<int>> adj(h, vector<int>(w, 0));
  
  for(int i=0; i<h; ++i){
    for(int j=0; j<w+2; ++j){
      int q;
      cin >> q;
      if(j==0 || j==w+1){
        continue;
      }
      adj[i][j-1] = q;
    }
  }
  
  
  
  int ww = (1<<w)-1;
  vector<vector<int>> dp(h, vector<int>(ww+1, 0));

  for(int i=2; i<h-1; ++i){
    for (int s = 0; s <= ww; ++s) { 
      
      int opt = 0;
      bool prev = false;
      bool even = true; 
      for (int j = 0; j < w; ++j) {
        if (s & 1<<j) {
          even = !even;
          if(adj[i][j]== 1 && adj[i-1][j] == 1) {
            if (prev){
              opt++;
              prev = false;
            } else {
              prev = true;
            }
          } else {
            prev = false;
          }
        } else {
          if(!even){
            break;
          }
          prev = false;
        }
      }
      
      opt += dp[i-1][ww&(~s)];
      
      for (int j = 0; j < w; ++j) {
        if (s & 1<<j) {
          int val = dp[i][(~(1<<j))&s];
          if (val > opt){
            opt = val;
          }
        }
      }
      
      dp[i][s] = opt;
      
    }
  }
  
  int res = 0;
  for (int s = 0; s <= ww; ++s) {
    if(dp[h-2][s] > res){
      res = dp[h-2][s];
    }
  }
  
  cout << res << endl;
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
