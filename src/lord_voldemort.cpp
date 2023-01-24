#include <iostream>
#include <vector>

using namespace std;

void solve(){
  int n, m, k;
  cin >> n >> m >> k;
  
  vector<int> V;
  
  V.reserve(n);
  
  for(int i=0; i<n; ++i){
    int v;
    cin >> v;
    V.push_back(v);
  }
  
  vector<vector<int>> maxn(n, vector<int>(m+1, 0));
  
  int curr = 0;
  int start = 0;
  
  for(int i=0; i<n; ++i){
    curr += V[i]; 
    
    while(curr > k){
      curr -= V[start++];
    }
    
    if(curr == k){
      int cnt = i-start+1;
      
      for(int j=1; j<=m; ++j){
        
        if(start > 0){
          if (maxn[start-1][j-1]>0 || j==1)
            maxn[i][j] = cnt + maxn[start-1][j-1];
          if(i>0 && maxn[i-1][j]>maxn[i][j])
            maxn[i][j] = maxn[i-1][j];
        } else if(j==1){
          maxn[i][j] = cnt;
          if(i>0 && maxn[i-1][j]>maxn[i][j]){
            maxn[i][j] = maxn[i-1][j];
          }
        }
      }
    } else if (i > 1){
      for(int j=1; j<=m; ++j){
        maxn[i][j] = maxn[i-1][j];
      }
    }
  }
  
  if(maxn[n-1][m] > 0){
    cout << maxn[n-1][m] << endl;
  } else {
    cout << "fail" << endl;
  }
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
